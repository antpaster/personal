/*
 * Copyright 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.example.apasternak.mobistreamertitan;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.app.Fragment;
import android.content.Context;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.RectF;
import android.graphics.SurfaceTexture;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.media.MediaCodec;
import android.media.MediaMuxer;
import android.media.MediaRecorder;
import android.opengl.GLES10;
import android.opengl.GLES11Ext;
import android.opengl.GLES20;
import android.opengl.GLES30;
import android.opengl.GLUtils;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.SystemClock;
import android.support.annotation.NonNull;
import android.support.annotation.RequiresApi;
import android.support.v4.app.ActivityCompat;
import android.util.Log;
import android.util.Size;
import android.util.SparseIntArray;
import android.view.LayoutInflater;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Chronometer;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

import javax.microedition.khronos.opengles.GL10;

@RequiresApi(api = Build.VERSION_CODES.N)
public class Camera2VideoFragment extends Fragment
        implements View.OnClickListener, FragmentCompat.OnRequestPermissionsResultCallback,
        MobiServiceable {

    private static final int SENSOR_ORIENTATION_DEFAULT_DEGREES = 90;
    private static final int SENSOR_ORIENTATION_INVERSE_DEGREES = 270;
    private static final SparseIntArray DEFAULT_ORIENTATIONS = new SparseIntArray();
    private static final SparseIntArray INVERSE_ORIENTATIONS = new SparseIntArray();

    private static final String TAG = "Camera2VideoFragment";
    private static final int REQUEST_VIDEO_PERMISSIONS = 1;
    private static final String FRAGMENT_DIALOG = "dialog";

    private static final String[] VIDEO_PERMISSIONS = {
            Manifest.permission.CAMERA,
            Manifest.permission.RECORD_AUDIO,
    };

    static {
        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_0, 90);
        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_90, 0);
        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_180, 270);
        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_270, 180);
    }

    static {
        INVERSE_ORIENTATIONS.append(Surface.ROTATION_0, 270);
        INVERSE_ORIENTATIONS.append(Surface.ROTATION_90, 180);
        INVERSE_ORIENTATIONS.append(Surface.ROTATION_180, 90);
        INVERSE_ORIENTATIONS.append(Surface.ROTATION_270, 0);
    }

    private CameraRecordingStream mCameraRecordingStream = new CameraRecordingStream();

    /**
     * An {@link AutoFitTextureView} for camera preview.
     */
    private AutoFitTextureView mTextureView;

    /**
     * Button to record video
     */
    private Button mButtonVideo;

    /**
     * A reference to the opened {@link CameraDevice}.
     */
    private CameraDevice mCameraDevice;

    /**
     * A reference to the current {@link CameraCaptureSession} for
     * preview.
     */
    private CameraCaptureSession mPreviewSession;

    /**
     * {@link TextureView.SurfaceTextureListener} handles several lifecycle events on a
     * {@link TextureView}.
     */
    private TextureView.SurfaceTextureListener mSurfaceTextureListener
            = new TextureView.SurfaceTextureListener() {

        @Override
        public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture,
                                              int width, int height) {
            openCamera(width, height);
        }

        @Override
        public void onSurfaceTextureSizeChanged(SurfaceTexture surfaceTexture,
                                                int width, int height) {
            configureTransform(width, height);
        }

        @Override
        public boolean onSurfaceTextureDestroyed(SurfaceTexture surfaceTexture) {
            return true;
        }

        @Override
        public void onSurfaceTextureUpdated(SurfaceTexture surfaceTexture) {
        }

    };

    /**
     * The {@link Size} of camera preview.
     */
    private Size mPreviewSize;

    /**
     * The {@link Size} of video recording.
     */
    private Size mVideoSize;

    /**
     * MediaRecorder
     */
    private MediaRecorder mMediaRecorder;

    /**
     * Whether the app is recording video now
     */
    private boolean mIsRecordingVideo;

    /**
     * An additional thread for running tasks that shouldn't block the UI.
     */
    private HandlerThread mBackgroundThread;

    /**
     * A {@link Handler} for running tasks in the background.
     */
    private Handler mBackgroundHandler;

    /**
     * A {@link Semaphore} to prevent the app from exiting before closing the camera.
     */
    private Semaphore mCameraOpenCloseLock = new Semaphore(1);

    public void setCameraManager(CameraManager cameraManager) {
        mCameraManager = cameraManager;
    }

    CameraManager mCameraManager;

    String mCameraId;

    ImageButton mToggleFlashButton;

    public void setTorchFlag(boolean torchFlag) {
        mTorchFlag = torchFlag;
    }

    boolean mTorchFlag = false;

    boolean mTorchOnFlag = false;

    Chronometer mChronometer;

    /**
     * Initializing the connection between the device and the host
     *
     * @param hostPort The address of the host port
     * @param streamNumber The number of the available stream
     */
    @Override
    public void initVideoServiceWithHost(String hostPort, int streamNumber) {

    }

    @Override
    public void configureCamera() {
        final Activity activity = getActivity();
        if (null == activity) {
            return;
        }
//        mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
//        mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.SURFACE);
//        mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
        if (mNextVideoAbsolutePath == null || mNextVideoAbsolutePath.isEmpty()) {
            mNextVideoAbsolutePath = getVideoFilePath(getActivity());
        }
//        mMediaRecorder.setOutputFile(mNextVideoAbsolutePath);
//        mMediaRecorder.setVideoEncodingBitRate(10000000);
//        mMediaRecorder.setVideoFrameRate(30);
//        mMediaRecorder.setVideoSize(mVideoSize.getWidth(), mVideoSize.getHeight());
//        mMediaRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.H264);
//        mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AAC);
        int rotation = activity.getWindowManager().getDefaultDisplay().getRotation();
        switch (mSensorOrientation) {
            case SENSOR_ORIENTATION_DEFAULT_DEGREES:
                mMediaRecorder.setOrientationHint(DEFAULT_ORIENTATIONS.get(rotation));
                break;
            case SENSOR_ORIENTATION_INVERSE_DEGREES:
                mMediaRecorder.setOrientationHint(INVERSE_ORIENTATIONS.get(rotation));
                break;
        }

//        try {
//            mMediaRecorder.prepare();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
    }

    GLES10 mGles10 = new GLES10();
    GLES20 mGles20 = new GLES20();
    GLES30 mGles30 = new GLES30();
    int[] mTextures = new int[10];
    float[] mTexMatrix = new float[16];

    private void setGlTexture(Bitmap sourceBm) {
        // Generate one texture pointer...
        mGles20.glGenTextures(1, mTextures, 0);
        // ...and bind it to our array
        mGles20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, mTextures[0]);

        // Create Nearest Filtered Texture
        mGles20.glTexParameterf(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_NEAREST);
        mGles20.glTexParameterf(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);

        // Different possible texture parameters, e.g. GL10.GL_CLAMP_TO_EDGE
        mGles20.glTexParameterf(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GL10.GL_TEXTURE_WRAP_S, GL10.GL_REPEAT);
        mGles20.glTexParameterf(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GL10.GL_TEXTURE_WRAP_T, GL10.GL_REPEAT);

        // Use the Android GLUtils to specify a two-dimensional texture image from our bitmap
        GLUtils.texImage2D(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, 0, sourceBm, 0);
//        GLES11Ext.GL_TEXTURE_EXTERNAL_OES
    }

    private Bitmap rotateAndScaleBitmap(Bitmap sourceBm) {
        int width = sourceBm.getWidth();
        int height = sourceBm.getHeight();

        float aspectRatio = (float) width / (float) height;
        int newHeight = width;
        int newWidth = (int) (width * aspectRatio);

        // calculate the scale
        float scaleWidth = ((float) newWidth) / width;
        float scaleHeight = ((float) newHeight) / height;

        // create a matrix for the manipulation
        Matrix matrix = new Matrix();
        // resize the bit map
        matrix.postScale(scaleWidth, scaleHeight);
        // rotate the Bitmap
        matrix.postRotate(90);

        // recreate the new Bitmap
        Bitmap resultBm = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        resultBm.eraseColor(Color.BLACK);

        Canvas canvas = new Canvas(resultBm);

        Bitmap foregroundBm = Bitmap.createBitmap(sourceBm, 0, 0, width, height, matrix, true);
        canvas.drawBitmap(foregroundBm, 0, (height - newWidth) / 2, null);

        matrix.reset();
        scaleWidth = scaleHeight = (float) 1.0;
        matrix.postScale(scaleWidth, scaleHeight);
        matrix.postRotate(270);

        resultBm = Bitmap.createBitmap(resultBm, 0, 0, width, height, matrix, true);

        setGlTexture(resultBm);

        return resultBm;
    }

    private Bitmap writeTextOnBitmap(Bitmap source, String captionString) {
        Bitmap newBitmap;

        Bitmap.Config config = source.getConfig();
        if (config == null) {
            config = Bitmap.Config.ARGB_8888;
        }

        newBitmap = Bitmap.createBitmap(source.getWidth(), source.getHeight(), config);

        // Prepare the Canvas
        Canvas canvas = new Canvas(newBitmap);
        newBitmap.eraseColor(Color.GREEN);

        // Draw the background from the source Bitmap
        Drawable background = new BitmapDrawable(getResources(), source);
        background.setBounds(0, 0, source.getWidth(), source.getHeight());
        background.draw(canvas); // draw the background to our bitmap

        // Draw the text
        Paint textPaint = new Paint();
        float textSizePx = 100;
        textPaint.setTextSize(textSizePx);
        textPaint.setStyle(Paint.Style.FILL);
        textPaint.setAntiAlias(true);
        textPaint.setColor(Color.RED);
//        textPaint.setARGB(0xff, 0x00, 0x00, 0x00);

        // Draw the text at the upper left corner
        canvas.drawText(captionString, 0,textSizePx, textPaint);

        setGlTexture(newBitmap);

        return newBitmap;
    }

    EglCore mEglCore;
    WindowSurface mDisplaySurface;
    WindowSurface mEncoderSurface;
    FullFrameRect mFullFrameBlit;
    CircularEncoder mCircEncoder;
    final float[] mTmpMatrix = new float[16];
    int mFrameNum = 0;
    boolean mFileSaveInProgress = false;

    /**
     * Draws a frame onto the SurfaceView and the encoder surface.
     * <p>
     * This will be called whenever we get a new preview frame from the camera.  This runs
     * on the UI thread, which ordinarily isn't a great idea -- you really want heavy work
     * to be on a different thread -- but we're really just throwing a few things at the GPU.
     * The upside is that we don't have to worry about managing state changes between threads.
     * <p>
     * If there was a pending frame available notification when we shut down, we might get
     * here after onPause().
     */
    private void drawFrame(final View view, SurfaceTexture cameraTexture) {
        //Log.d(TAG, "drawFrame");
        if (mEglCore == null) {
            Log.d(TAG, "Skipping drawFrame after shutdown");
            return;
        }

        // Latch the next frame from the camera.
        mDisplaySurface.makeCurrent();
        cameraTexture.updateTexImage();
        cameraTexture.getTransformMatrix(mTmpMatrix);

        mGles20.glGenTextures(1, mTextures, 0);

        try {
            MediaCodec encoder = MediaCodec.createEncoderByType("video/avc");
            ByteBuffer outputBuffer = encoder.getOutputBuffer(0);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Fill the SurfaceView with it.
        SurfaceView sv = view.findViewById(R.id.texture);
        int viewWidth = sv.getWidth();
        int viewHeight = sv.getHeight();
        GLES20.glViewport(0, 0, viewWidth, viewHeight);
        mFullFrameBlit.drawFrame(mTextures[0], mTmpMatrix);

        drawExtra(mFrameNum, viewWidth, viewHeight);

        mDisplaySurface.swapBuffers();

        // Send it to the video encoder.
        if (!mFileSaveInProgress) {
            mEncoderSurface.makeCurrent();
            GLES20.glViewport(0, 0, mPreviewSize.getWidth(), mPreviewSize.getHeight());
            mFullFrameBlit.drawFrame(mTextures[0], mTmpMatrix);

            drawExtra(mFrameNum, mPreviewSize.getWidth(), mPreviewSize.getHeight());

            mCircEncoder.frameAvailableSoon();
            mEncoderSurface.setPresentationTime(cameraTexture.getTimestamp());
            mEncoderSurface.swapBuffers();
        }

        mFrameNum++;
    }

    /**
     * Adds a bit of extra stuff to the display just to give it flavor.
     */
    private static void drawExtra(int frameNum, int width, int height) {
        // We "draw" with the scissor rect and clear calls.  Note this uses window coordinates.
        int val = frameNum % 3;
        switch (val) {
            case 0:  GLES20.glClearColor(1.0f, 0.0f, 0.0f, 1.0f);   break;
            case 1:  GLES20.glClearColor(0.0f, 1.0f, 0.0f, 1.0f);   break;
            case 2:  GLES20.glClearColor(0.0f, 0.0f, 1.0f, 1.0f);   break;
        }

        int xpos = (int) (width * ((frameNum % 100) / 100.0f));
        GLES20.glEnable(GLES20.GL_SCISSOR_TEST);
        GLES20.glScissor(xpos, 0, width / 32, height / 32);
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        GLES20.glDisable(GLES20.GL_SCISSOR_TEST);
    }

//    @Override   // SurfaceHolder.Callback
//    public void surfaceCreated(SurfaceHolder holder) {
//        Log.d(TAG, "surfaceCreated holder=" + holder);
//
//        // Set up everything that requires an EGL context.
//        //
//        // We had to wait until we had a surface because you can't make an EGL context current
//        // without one, and creating a temporary 1x1 pbuffer is a waste of time.
//        //
//        // The display surface that we use for the SurfaceView, and the encoder surface we
//        // use for video, use the same EGL context.
//        mEglCore = new EglCore(null, EglCore.FLAG_RECORDABLE);
//        mDisplaySurface = new WindowSurface(mEglCore, holder.getSurface(), false);
//        mDisplaySurface.makeCurrent();
//
//        mFullFrameBlit = new FullFrameRect(
//                new Texture2dProgram(Texture2dProgram.ProgramType.TEXTURE_EXT));
//        mTextureId = mFullFrameBlit.createTextureObject();
//        mCameraTexture = new SurfaceTexture(mTextureId);
//        mCameraTexture.setOnFrameAvailableListener(this);
//
//        Log.d(TAG, "starting camera preview");
//        try {
//            mCamera.setPreviewTexture(mCameraTexture);
//        } catch (IOException ioe) {
//            throw new RuntimeException(ioe);
//        }
//        mCamera.startPreview();
//
//        // TODO: adjust bit rate based on frame rate?
//        // TODO: adjust video width/height based on what we're getting from the camera preview?
//        //       (can we guarantee that camera preview size is compatible with AVC video encoder?)
//        try {
//            mCircEncoder = new CircularEncoder(VIDEO_WIDTH, VIDEO_HEIGHT, 6000000,
//                    mCameraPreviewThousandFps / 1000, 7, mHandler);
//        } catch (IOException ioe) {
//            throw new RuntimeException(ioe);
//        }
//        mEncoderSurface = new WindowSurface(mEglCore, mCircEncoder.getInputSurface(), true);
//
//        updateControls();
//    }

    @Override
    public void startCamera() {
        if (null == mCameraDevice || !mTextureView.isAvailable() || null == mPreviewSize) {
            return;
        }
        try {
            closePreviewSession();
            configureCamera(); // Dealing with output video file and rotations for now. todo refactor

            mCameraRecordingStream.configure(getContext(), mVideoSize, true, 10000000);

            SurfaceTexture texture = mTextureView.getSurfaceTexture();
            assert texture != null;
            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
            mPreviewBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_RECORD);
            List<Surface> surfaces = new ArrayList<>();

            // Set up Surface for the camera preview
            Surface previewSurface = new Surface(texture);
            surfaces.add(previewSurface);
//            mPreviewBuilder.addTarget(previewSurface);

            // Set up Surface for the MediaRecorder
            Surface recorderSurface;
            if (null != mCameraRecordingStream.getCurrentFrameSurface()) {
//                recorderSurface = mMediaRecorder.getSurface();
//                recorderSurface = mCameraRecordingStream.getCurrentFrameSurface();
                recorderSurface = mCameraRecordingStream.getEncoder().createInputSurface();
                surfaces.add(recorderSurface);
            }
//            mPreviewBuilder.addTarget(recorderSurface);

            mCameraRecordingStream.onConfiguringOutputs(surfaces, false);
            mCameraRecordingStream.onConfiguringRequest(mPreviewBuilder, false);

            // Start a capture session
            // Once the session starts, we can update the UI and start recording
            mCameraDevice.createCaptureSession(surfaces, new CameraCaptureSession.StateCallback() {

                @RequiresApi(api = Build.VERSION_CODES.O)
                @Override
                public void onConfigured(@NonNull CameraCaptureSession cameraCaptureSession) {
                    mPreviewSession = cameraCaptureSession;
                    updateFrame();

                    final SurfaceTexture surface = new SurfaceTexture(true);

                    getActivity().runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            // UI
                            mButtonVideo.setText(R.string.stop);
                            mIsRecordingVideo = true;

                            surface.setOnFrameAvailableListener(new
                                    SurfaceTexture.OnFrameAvailableListener() {
                                @Override
                                public void onFrameAvailable(SurfaceTexture surfaceTexture) {

                                    drawFrame(mView, surfaceTexture);

//                                    // todo paste the image transform here!
//                                    Parcel parcel = Parcel.obtain();
//                                    recorderSurface.writeToParcel(parcel, 0);
//                                    byte[] surfaceInBytes = parcel.createByteArray();
//
//                                    // Getting the Bitmap object from byte array and writing test on it
//                                    Bitmap bm = BitmapFactory.decodeByteArray(surfaceInBytes, 0, surfaceInBytes.length);
//
//                                    Activity activity = getActivity();
//                                    int rotation = activity.getWindowManager().getDefaultDisplay().getRotation();
//                                    if(Surface.ROTATION_0 == rotation || Surface.ROTATION_180 == rotation) {
//                                        bm = rotateAndScaleBitmap(bm);
//                                    }
//
//                                    // The date and time of capturing
//                                    DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
//                                    Date nowDate = Calendar.getInstance().getTime();
//                                    String nowDateString = dateFormat.format(nowDate);
//
//                                    bm = writeTextOnBitmap(bm, nowDateString);
//
//                                    // Making the byte array back from the processed Bitmap object
//                                    ByteArrayOutputStream stream = new ByteArrayOutputStream();
//                                    bm.compress(Bitmap.CompressFormat.JPEG, 100, stream);
//                                    byte[] outBytes = stream.toByteArray();
//
//                                    parcel.unmarshall(outBytes, 0, outBytes.length);
//
//                                    recorderSurface.readFromParcel(parcel);
                                }
                            });

                            // Start recording
//                            mMediaRecorder.start();

                            mCameraRecordingStream.start();

                            drawFrame(mView, surface);

                            // Setting the recording time counter
                            mChronometer.setBase(SystemClock.elapsedRealtime());
                            mChronometer.setVisibility(View.VISIBLE);
                            mChronometer.start();
                        }
                    });
                }

                @Override
                public void onConfigureFailed(@NonNull CameraCaptureSession cameraCaptureSession) {
                    Activity activity = getActivity();
                    if (null != activity) {
                        Toast.makeText(activity, "Failed", Toast.LENGTH_SHORT).show();
                    }
                }
            }, mBackgroundHandler);
        } catch (CameraAccessException/* | IOException*/ e) {
            e.printStackTrace();
        }
    }

    @Override
    public void stopCamera() {
        // UI
        mIsRecordingVideo = false;
        mButtonVideo.setText(R.string.record);
        // Stop recording
//        mMediaRecorder.stop();
//        mMediaRecorder.reset();

        mCameraRecordingStream.stop();

        Activity activity = getActivity();
        if (null != activity) {
            Toast.makeText(activity, "Video saved: " + mNextVideoAbsolutePath,
                    Toast.LENGTH_SHORT).show();
            Log.d(TAG, "Video saved: " + mNextVideoAbsolutePath);
        }
        mNextVideoAbsolutePath = null;
        startPreview();
    }

    @Override
    public void switchCamera() {

    }

    /**
    * Update the camera preview. {@link #startPreview()} needs to be called in advance.
    */
    @Override
    public void updateFrame() {
        if (null == mCameraDevice) {
            return;
        }
        try {
            setUpCaptureRequestBuilder(mPreviewBuilder);
            HandlerThread thread = new HandlerThread("CameraPreview");
            thread.start();
            mPreviewSession.setRepeatingRequest(mPreviewBuilder.build(), null, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    /**
     * Checks whether the device has a torch
     *
     * @return The sign of the torch presence
     */
    @Override
    public boolean hasTorch() {
        return mTorchFlag;
    }

    /**
     * Toggles the torch in case of its existing
     */
    @Override
    public void toggleTorch() {
        mTorchOnFlag = !mTorchOnFlag;
    }

    @Override
    public void onStateEvent(StateEvent stateEvent) {

    }

    @Override
    public void onSignalStateEvent(SignalStateEvent signalStateEvent) {

    }

    @Override
    public void onTestEvent(TestEvent testEvent) {

    }

    /**
     * {@link CameraDevice.StateCallback} is called when {@link CameraDevice} changes its status.
     */
    private CameraDevice.StateCallback mStateCallback = new CameraDevice.StateCallback() {

        @Override
        public void onOpened(@NonNull CameraDevice cameraDevice) {
            mCameraDevice = cameraDevice;
            startPreview();
            mCameraOpenCloseLock.release();
            if (null != mTextureView) {
                configureTransform(mTextureView.getWidth(), mTextureView.getHeight());
            }
        }

        @Override
        public void onDisconnected(@NonNull CameraDevice cameraDevice) {
            mCameraOpenCloseLock.release();
            cameraDevice.close();
            mCameraDevice = null;
        }

        @Override
        public void onError(@NonNull CameraDevice cameraDevice, int error) {
            mCameraOpenCloseLock.release();
            cameraDevice.close();
            mCameraDevice = null;
            Activity activity = getActivity();
            if (null != activity) {
                activity.finish();
            }
        }

    };
    private Integer mSensorOrientation;
    private String mNextVideoAbsolutePath;
    private CaptureRequest.Builder mPreviewBuilder;

    public Camera2VideoFragment() {

    }

//    public static Camera2VideoFragment newInstance() {
//        return new Camera2VideoFragment();
//    }

    /**
     * In this sample, we choose a video size with 3x4 aspect ratio. Also, we don't use sizes
     * larger than 1080p, since MediaRecorder cannot handle such a high-resolution video.
     *
     * @param choices The list of available sizes
     * @return The video size
     */
    private static Size chooseVideoSize(Size[] choices) {
        for (Size size : choices) {
            if (size.getWidth() == size.getHeight() * 4 / 3 && size.getWidth() <= 1080) {
                return size;
            }
        }
        Log.e(TAG, "Couldn't find any suitable video size");
        return choices[choices.length - 1];
    }

    /**
     * Given {@code choices} of {@code Size}s supported by a camera, chooses the smallest one whose
     * width and height are at least as large as the respective requested values, and whose aspect
     * ratio matches with the specified value.
     *
     * @param choices     The list of sizes that the camera supports for the intended output class
     * @param width       The minimum desired width
     * @param height      The minimum desired height
     * @param aspectRatio The aspect ratio
     * @return The optimal {@code Size}, or an arbitrary one if none were big enough
     */
    private static Size chooseOptimalSize(Size[] choices, int width, int height, Size aspectRatio) {
        // Collect the supported resolutions that are at least as big as the preview Surface
        List<Size> bigEnough = new ArrayList<>();
        int w = aspectRatio.getWidth();
        int h = aspectRatio.getHeight();
        for (Size option : choices) {
            if (option.getHeight() == option.getWidth() * h / w &&
                    option.getWidth() >= width && option.getHeight() >= height) {
                bigEnough.add(option);
            }
        }

        // Pick the smallest of those, assuming we found any
        if (bigEnough.size() > 0) {
            return Collections.min(bigEnough, new CompareSizesByArea());
        } else {
            Log.e(TAG, "Couldn't find any suitable preview size");
            return choices[0];
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_camera2_video, container, false);
    }

    View mView;

    @Override
    public void onViewCreated(final View view, Bundle savedInstanceState) {
        mView = view;

        mTextureView = view.findViewById(R.id.texture);
        mButtonVideo = view.findViewById(R.id.video);
        mButtonVideo.setOnClickListener(this);
        view.findViewById(R.id.info).setOnClickListener(this);

        mToggleFlashButton = view.findViewById(R.id.flash);
        mToggleFlashButton.setOnClickListener(this);

        mChronometer = view.findViewById(R.id.chronometer);
    }

    @Override
    public void onResume() {
        super.onResume();
        startBackgroundThread();
        if (mTextureView.isAvailable()) {
            openCamera(mTextureView.getWidth(), mTextureView.getHeight());
        } else {
            mTextureView.setSurfaceTextureListener(mSurfaceTextureListener);
        }
    }

    @Override
    public void onPause() {
        closeCamera();
        stopBackgroundThread();
        super.onPause();
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.video: {
                if (mIsRecordingVideo) {
                    mChronometer.stop();
                    mChronometer.setVisibility(View.INVISIBLE);

                    stopCamera();
                } else {
                    startCamera();
                }
                break;
            }

            case R.id.info: {
                Activity activity = getActivity();
                if (null != activity) {
                    new AlertDialog.Builder(activity)
                            .setMessage(R.string.intro_message)
                            .setPositiveButton(android.R.string.ok, null)
                            .show();
                }
                break;
            }

            case R.id.flash: {
                try {
                    mCameraId = mCameraManager.getCameraIdList()[0];

                    if (mTorchOnFlag) {
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                            mCameraManager.setTorchMode(mCameraId, false);
                            mToggleFlashButton.setImageResource(R.mipmap.flash_off);
                        }
                        mTorchOnFlag = false;
                    } else {
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                            mCameraManager.setTorchMode(mCameraId, true);
                            mToggleFlashButton.setImageResource(R.mipmap.flash_on);
                        }
                        mTorchOnFlag = true;
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }

    /**
     * Starts a background thread and its {@link Handler}.
     */
    private void startBackgroundThread() {
        mBackgroundThread = new HandlerThread("CameraBackground");
        mBackgroundThread.start();
        mBackgroundHandler = new Handler(mBackgroundThread.getLooper());
    }

    /**
     * Stops the background thread and its {@link Handler}.
     */
    private void stopBackgroundThread() {
        mBackgroundThread.quitSafely();
        try {
            mBackgroundThread.join();
            mBackgroundThread = null;
            mBackgroundHandler = null;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    /**
     * Gets whether you should show UI with rationale for requesting permissions.
     *
     * @param permissions The permissions your app wants to request.
     * @return Whether you can show permission rationale UI.
     */
    private boolean shouldShowRequestPermissionRationale(String[] permissions) {
        for (String permission : permissions) {
            if (FragmentCompat.shouldShowRequestPermissionRationale(this, permission)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Requests permissions needed for recording video.
     */
    private void requestVideoPermissions() {
        if (shouldShowRequestPermissionRationale(VIDEO_PERMISSIONS)) {
            new ConfirmationDialog().show(getChildFragmentManager(), FRAGMENT_DIALOG);
        } else {
            FragmentCompat.requestPermissions(this, VIDEO_PERMISSIONS, REQUEST_VIDEO_PERMISSIONS);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {
        Log.d(TAG, "onRequestPermissionsResult");
        if (requestCode == REQUEST_VIDEO_PERMISSIONS) {
            if (grantResults.length == VIDEO_PERMISSIONS.length) {
                for (int result : grantResults) {
                    if (result != PackageManager.PERMISSION_GRANTED) {
                        ErrorDialog.newInstance(getString(R.string.permission_request))
                                .show(getChildFragmentManager(), FRAGMENT_DIALOG);
                        break;
                    }
                }
            } else {
                ErrorDialog.newInstance(getString(R.string.permission_request))
                        .show(getChildFragmentManager(), FRAGMENT_DIALOG);
            }
        } else {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
    }

    private boolean hasPermissionsGranted(String[] permissions) {
        for (String permission : permissions) {
            if (ActivityCompat.checkSelfPermission(getActivity(), permission)
                    != PackageManager.PERMISSION_GRANTED) {
                return false;
            }
        }
        return true;
    }

    /**
     * Tries to open a {@link CameraDevice}. The result is listened by `mStateCallback`.
     */
    @SuppressWarnings("MissingPermission")
    private void openCamera(int width, int height) {
        if (!hasPermissionsGranted(VIDEO_PERMISSIONS)) {
            requestVideoPermissions();
            return;
        }
        final Activity activity = getActivity();
        if (null == activity || activity.isFinishing()) {
            return;
        }
        CameraManager manager = (CameraManager) activity.getSystemService(Context.CAMERA_SERVICE);
        try {
            Log.d(TAG, "tryAcquire");
            if (!mCameraOpenCloseLock.tryAcquire(2500, TimeUnit.MILLISECONDS)) {
                throw new RuntimeException("Time out waiting to lock camera opening.");
            }
            String cameraId = manager.getCameraIdList()[0];

            // Choose the sizes for camera preview and video recording
            CameraCharacteristics characteristics = manager.getCameraCharacteristics(cameraId);
            StreamConfigurationMap map = characteristics
                    .get(CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP);
            mSensorOrientation = characteristics.get(CameraCharacteristics.SENSOR_ORIENTATION);
            if (map == null) {
                throw new RuntimeException("Cannot get available preview/video sizes");
            }
            mVideoSize = chooseVideoSize(map.getOutputSizes(MediaRecorder.class));
            mPreviewSize = chooseOptimalSize(map.getOutputSizes(SurfaceTexture.class),
                    width, height, mVideoSize);

            int orientation = getResources().getConfiguration().orientation;
            if (orientation == Configuration.ORIENTATION_LANDSCAPE) {
                mTextureView.setAspectRatio(mPreviewSize.getWidth(), mPreviewSize.getHeight());
            } else {
                mTextureView.setAspectRatio(mPreviewSize.getHeight(), mPreviewSize.getWidth());
            }
            configureTransform(width, height);
            mMediaRecorder = new MediaRecorder();
            manager.openCamera(cameraId, mStateCallback, null);
        } catch (CameraAccessException e) {
            Toast.makeText(activity, "Cannot access the camera.", Toast.LENGTH_SHORT).show();
            activity.finish();
        } catch (NullPointerException e) {
            // Currently an NPE is thrown when the Camera2API is used but not supported on the
            // device this code runs.
            ErrorDialog.newInstance(getString(R.string.camera_error))
                    .show(getChildFragmentManager(), FRAGMENT_DIALOG);
        } catch (InterruptedException e) {
            throw new RuntimeException("Interrupted while trying to lock camera opening.");
        }
    }

    private void closeCamera() {
        try {
            mCameraOpenCloseLock.acquire();
            closePreviewSession();
            if (null != mCameraDevice) {
                mCameraDevice.close();
                mCameraDevice = null;
            }
            if (null != mMediaRecorder) {
                mMediaRecorder.release();
                mMediaRecorder = null;
            }
        } catch (InterruptedException e) {
            throw new RuntimeException("Interrupted while trying to lock camera closing.");
        } finally {
            mCameraOpenCloseLock.release();
        }
    }

    /**
     * Start the camera preview.
     */
    private void startPreview() {
        if (null == mCameraDevice || !mTextureView.isAvailable() || null == mPreviewSize) {
            return;
        }
        try {
            closePreviewSession();
            SurfaceTexture texture = mTextureView.getSurfaceTexture();
            assert texture != null;
            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
            mPreviewBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);

            Surface previewSurface = new Surface(texture);
            mPreviewBuilder.addTarget(previewSurface);

            mCameraDevice.createCaptureSession(Collections.singletonList(previewSurface),
                    new CameraCaptureSession.StateCallback() {

                        @Override
                        public void onConfigured(@NonNull CameraCaptureSession session) {
                            mPreviewSession = session;
                            updateFrame();
                        }

                        @Override
                        public void onConfigureFailed(@NonNull CameraCaptureSession session) {
                            Activity activity = getActivity();
                            if (null != activity) {
                                Toast.makeText(activity, "Failed", Toast.LENGTH_SHORT).show();
                            }
                        }
                    }, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    private void setUpCaptureRequestBuilder(CaptureRequest.Builder builder) {
        builder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);
    }

    /**
     * Configures the necessary {@link Matrix} transformation to `mTextureView`.
     * This method should not to be called until the camera preview size is determined in
     * openCamera, or until the size of `mTextureView` is fixed.
     *
     * @param viewWidth  The width of `mTextureView`
     * @param viewHeight The height of `mTextureView`
     */
    private void configureTransform(int viewWidth, int viewHeight) {
        Activity activity = getActivity();
        if (null == mTextureView || null == mPreviewSize || null == activity) {
            return;
        }
        int rotation = activity.getWindowManager().getDefaultDisplay().getRotation();
        Matrix matrix = new Matrix();
        RectF viewRect = new RectF(0, 0, viewWidth, viewHeight);
        RectF bufferRect = new RectF(0, 0, mPreviewSize.getHeight(), mPreviewSize.getWidth());
        float centerX = viewRect.centerX();
        float centerY = viewRect.centerY();
        if (Surface.ROTATION_90 == rotation || Surface.ROTATION_270 == rotation) {
            bufferRect.offset(centerX - bufferRect.centerX(), centerY - bufferRect.centerY());
            matrix.setRectToRect(viewRect, bufferRect, Matrix.ScaleToFit.FILL);
            float scale = Math.max(
                    (float) viewHeight / mPreviewSize.getHeight(),
                    (float) viewWidth / mPreviewSize.getWidth());
            matrix.postScale(scale, scale, centerX, centerY);
            matrix.postRotate(90 * (rotation - 2), centerX, centerY); // todo deal with it
        }
        mTextureView.setTransform(matrix);
    }

    private String getVideoFilePath(Context context) {
        final File dir = context.getExternalFilesDir(null);
        return (dir == null ? "" : (dir.getAbsolutePath() + "/"))
                + System.currentTimeMillis() + ".mp4";
    }

    private void closePreviewSession() {
        if (mPreviewSession != null) {
            mPreviewSession.close();
            mPreviewSession = null;
        }
    }

    /**
     * Compares two {@code Size}s based on their areas.
     */
    static class CompareSizesByArea implements Comparator<Size> {

        @Override
        public int compare(Size lhs, Size rhs) {
            // We cast here to ensure the multiplications won't overflow
            return Long.signum((long) lhs.getWidth() * lhs.getHeight() -
                    (long) rhs.getWidth() * rhs.getHeight());
        }
    }

    public static class ErrorDialog extends DialogFragment {

        private static final String ARG_MESSAGE = "message";

        public static ErrorDialog newInstance(String message) {
            ErrorDialog dialog = new ErrorDialog();
            Bundle args = new Bundle();
            args.putString(ARG_MESSAGE, message);
            dialog.setArguments(args);
            return dialog;
        }

        @Override
        public Dialog onCreateDialog(Bundle savedInstanceState) {
            final Activity activity = getActivity();
            return new AlertDialog.Builder(activity)
                    .setMessage(getArguments().getString(ARG_MESSAGE))
                    .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialogInterface, int i) {
                            activity.finish();
                        }
                    })
                    .create();
        }

    }

    public static class ConfirmationDialog extends DialogFragment {

        @Override
        public Dialog onCreateDialog(Bundle savedInstanceState) {
            final Fragment parent = getParentFragment();
            return new AlertDialog.Builder(getActivity())
                    .setMessage(R.string.permission_request)
                    .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            FragmentCompat.requestPermissions(parent, VIDEO_PERMISSIONS,
                                    REQUEST_VIDEO_PERMISSIONS);
                        }
                    })
                    .setNegativeButton(android.R.string.cancel,
                            new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    parent.getActivity().finish();
                                }
                            })
                    .create();
        }

    }

}
