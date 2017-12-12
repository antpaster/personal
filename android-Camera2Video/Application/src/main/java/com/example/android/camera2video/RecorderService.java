package com.example.android.camera2video;

import android.Manifest;
import android.app.Activity;
import android.app.Fragment;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageFormat;
import android.graphics.Matrix;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.SurfaceTexture;
import android.graphics.YuvImage;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.hardware.camera2.TotalCaptureResult;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.media.Image;
import android.media.ImageReader;
import android.media.MediaRecorder;
import android.opengl.GLES20;
import android.os.Build;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;
import android.os.SystemClock;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.annotation.RequiresApi;
import android.support.v13.app.FragmentCompat;
import android.support.v4.app.ActivityCompat;
import android.util.Log;
import android.util.Size;
import android.util.SparseIntArray;
import android.view.Surface;
import android.view.View;
import android.widget.Button;
import android.widget.Chronometer;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Date;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

import static android.graphics.ImageFormat.NV21;
import static android.opengl.GLES11Ext.GL_TEXTURE_EXTERNAL_OES;

/**
 * Created by apasternak on 11.12.17.
 */

@RequiresApi(api = Build.VERSION_CODES.M)
public class RecorderService extends Service {
    private static final String TAG = "RecorderService";
    private static final String[] VIDEO_PERMISSIONS = {
            Manifest.permission.CAMERA,
            Manifest.permission.RECORD_AUDIO,
    };
    private static final String FRAGMENT_DIALOG = "dialog";
    private static final int REQUEST_VIDEO_PERMISSIONS = 1;
    private static final int SENSOR_ORIENTATION_DEFAULT_DEGREES = 90;
    private static final int SENSOR_ORIENTATION_INVERSE_DEGREES = 270;
    private static final SparseIntArray DEFAULT_ORIENTATIONS = new SparseIntArray();
    private static final SparseIntArray INVERSE_ORIENTATIONS = new SparseIntArray();

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

    private Fragment mFragment = new Fragment();

    /**
     * A {@link Semaphore} to prevent the app from exiting before closing the camera.
     */
    private Semaphore mCameraOpenCloseLock = new Semaphore(1);

    /**
     * The {@link Size} of video recording.
     */
    private Size mVideoSize;

    /**
     * The {@link Size} of camera preview.
     */
    private Size mPreviewSize;

    private Integer mSensorOrientation;

    /**
     * MediaRecorder
     */
    private MediaRecorder mMediaRecorder;

    /**
     * A reference to the opened {@link CameraDevice}.
     */
    private CameraDevice mCameraDevice;

    private CaptureRequest.Builder mPreviewBuilder;

    /**
     * A reference to the current {@link CameraCaptureSession} for
     * preview.
     */
    private CameraCaptureSession mPreviewSession;

    /**
     * Whether the app is recording video now
     */
    private boolean mIsRecordingVideo;

    public GLES20 getGles20() {
        return mGles20;
    }
    GLES20 mGles20 = new GLES20();

    public int[] getTextures() {
        return mTextures;
    }
    int[] mTextures = new int[10];

    /**
     * An additional thread for running tasks that shouldn't block the UI.
     */
    private HandlerThread mBackgroundThread;

    /**
     * A {@link Handler} for running tasks in the background.
     */
    private Handler mBackgroundHandler;

    private String mVideoFolderPath;

    public String getNextVideoAbsolutePath() {
        return mNextVideoAbsolutePath;
    }

    private String mNextVideoAbsolutePath;
    private String mRecordedVideoFileName;

    public void setTextureView(AutoFitTextureView textureView) {
        mTextureView = textureView;
    }

    /**
     * An {@link AutoFitTextureView} for camera preview.
     */
    private AutoFitTextureView mTextureView;

    public void setButtonVideo(Button buttonVideo) {
        mButtonVideo = buttonVideo;
    }

    /**
     * Button to record video
     */
    private Button mButtonVideo;

    public void setDeleteFileButton(ImageButton deleteFileButton) {
        mDeleteFileButton = deleteFileButton;
    }

    private ImageButton mDeleteFileButton;

    public void setChronometer(Chronometer chronometer) {
        mChronometer = chronometer;
    }

    private Chronometer mChronometer;

    public void setContext(Context context) {
        mContext = context;
    }

    private Context mContext;

    public void setActivity(Activity activity) {
        mActivity = activity;
    }

    private Activity mActivity;

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
            if (null != mActivity) {
                mActivity.finish();
            }
        }
    };

    @Override
    public void onCreate() {
        openCamera(mVideoSize.getWidth(), mVideoSize.getHeight());
//            startCamera();

        super.onCreate();
    }

//        @Override
//        public ComponentName startService(Intent service) {
//            return super.startService(service);
//        }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
//            openCamera(mVideoSize.getWidth(), mVideoSize.getHeight());
        startCamera();

        Toast.makeText(this, "Recording service started!",
                Toast.LENGTH_SHORT).show();

        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        closeCamera();

        Toast.makeText(this, "Recording service destroyed!",
                Toast.LENGTH_SHORT).show();

        super.onDestroy();
    }

    @Override
    public boolean stopService(Intent name) {
        stopCamera();

        return super.stopService(name);
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    public boolean hasPermissionsGranted(String[] permissions) {
        for (String permission : permissions) {
            if (ActivityCompat.checkSelfPermission(mActivity, permission)
                    != PackageManager.PERMISSION_GRANTED) {
                return false;
            }
        }
        return true;
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
    public boolean shouldShowRequestPermissionRationale(String[] permissions) {
        for (String permission : permissions) {
            if (FragmentCompat.shouldShowRequestPermissionRationale(mFragment, permission)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Requests permissions needed for recording video.
     */
    public void requestVideoPermissions() {
        if (shouldShowRequestPermissionRationale(VIDEO_PERMISSIONS)) {
            new Camera2VideoFragment.ConfirmationDialog().show(mFragment.getChildFragmentManager(),
                    FRAGMENT_DIALOG);
        } else {
            FragmentCompat.requestPermissions(mFragment, VIDEO_PERMISSIONS,
                    REQUEST_VIDEO_PERMISSIONS);
        }
    }

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
            return Collections.min(bigEnough, new Camera2VideoFragment.CompareSizesByArea());
        } else {
            Log.e(TAG, "Couldn't find any suitable preview size");
            return choices[0];
        }
    }

    /**
     * Configures the necessary {@link Matrix} transformation to `mTextureView`.
     * This method should not to be called until the camera preview size is determined in
     * openCamera, or until the size of `mTextureView` is fixed.
     *
     * @param viewWidth  The width of `mTextureView`
     * @param viewHeight The height of `mTextureView`
     */
    public void configureTransform(int viewWidth, int viewHeight) {
        if (null == mTextureView || null == mPreviewSize || null == mActivity) {
            return;
        }
        int rotation = mActivity.getWindowManager().getDefaultDisplay().getRotation();
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
            matrix.postRotate(90 * (rotation - 2), centerX, centerY);
        }
        mTextureView.setTransform(matrix);
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

//            mImageReader = ImageReader.newInstance(mPreviewSize.getWidth(),
//                    mPreviewSize.getHeight(), ImageFormat.YUV_420_888, 1);
////                    mPreviewSize.getHeight(), ImageFormat.JPEG, 1);


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
                            if (null != mActivity) {
                                Toast.makeText(mActivity, "Failed", Toast.LENGTH_SHORT).show();
                            }
                        }
                    }, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    private void closePreviewSession() {
        if (mPreviewSession != null) {
            mPreviewSession.close();
            mPreviewSession = null;
        }
    }

    /**
     * Update the camera preview. {@link #startPreview()} needs to be called in advance.
     */
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

    private void setUpCaptureRequestBuilder(CaptureRequest.Builder builder) {
        builder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);
    }

    private String getVideoFilePath(Context context) {
        mVideoFolderPath = mContext.getExternalFilesDir(null).getAbsolutePath();
        mRecordedVideoFileName = System.currentTimeMillis() + ".mp4";
        final File dir = context.getExternalFilesDir(null);
        return (dir == null ? "" : (mVideoFolderPath + "/"))
                + mRecordedVideoFileName;
    }

    public void configureCamera() {
        if (null == mActivity) {
            return;
        }
        mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
        mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.SURFACE);
        mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
        if (mNextVideoAbsolutePath == null || mNextVideoAbsolutePath.isEmpty()) {
            mNextVideoAbsolutePath = getVideoFilePath(mActivity);
            mDeleteFileButton.setVisibility(View.INVISIBLE);
        }
        mMediaRecorder.setOutputFile(mNextVideoAbsolutePath);
        mMediaRecorder.setVideoEncodingBitRate(10000000);
        mMediaRecorder.setVideoFrameRate(30);
        mMediaRecorder.setVideoSize(mVideoSize.getWidth(), mVideoSize.getHeight());
        mMediaRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.H264);
        mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AAC);
        int rotation = mActivity.getWindowManager().getDefaultDisplay().getRotation();
        switch (mSensorOrientation) {
            case SENSOR_ORIENTATION_DEFAULT_DEGREES:
                mMediaRecorder.setOrientationHint(DEFAULT_ORIENTATIONS.get(rotation));
                break;
            case SENSOR_ORIENTATION_INVERSE_DEGREES:
                mMediaRecorder.setOrientationHint(INVERSE_ORIENTATIONS.get(rotation));
                break;
        }

        try {
            mMediaRecorder.prepare();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Tries to open a {@link CameraDevice}. The result is listened by `mStateCallback`.
     */
    @SuppressWarnings("MissingPermission")
    public void openCamera(int width, int height) {
        if (!hasPermissionsGranted(VIDEO_PERMISSIONS)) {
            requestVideoPermissions();
            return;
        }

        if (null == mActivity || mActivity.isFinishing()) {
            return;
        }

        CameraManager manager = (CameraManager) mActivity.getSystemService(Context.CAMERA_SERVICE);
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
            Toast.makeText(mActivity, "Cannot access the camera.", Toast.LENGTH_SHORT).show();
            mActivity.finish();
        } catch (NullPointerException e) {
            // Currently an NPE is thrown when the Camera2API is used but not supported on the
            // device this code runs.
//            Camera2VideoFragment.ErrorDialog.newInstance(getString(R.string.camera_error))
//                    .show(getChildFragmentManager(), FRAGMENT_DIALOG);
        } catch (InterruptedException e) {
            throw new RuntimeException("Interrupted while trying to lock camera opening.");
        }
    }

    public void closeCamera() {
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

//            if (null != mImageReader) {
//                mImageReader.close();
//                mImageReader = null;
//            }
        } catch (InterruptedException e) {
            throw new RuntimeException("Interrupted while trying to lock camera closing.");
        } finally {
            mCameraOpenCloseLock.release();
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    public void startCamera() {
        if (null == mCameraDevice || !mTextureView.isAvailable() || null == mPreviewSize) {
            return;
        }
        try {
            closePreviewSession();
            configureCamera();
            SurfaceTexture texture = mTextureView.getSurfaceTexture();
            assert texture != null;
            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
            mPreviewBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_RECORD);
            final List<Surface> surfaces = new ArrayList<>();

            // Set up Surface for the camera preview
            Surface previewSurface = new Surface(texture);
            surfaces.add(previewSurface);
            mPreviewBuilder.addTarget(previewSurface);

            // Set up Surface for the MediaRecorder
            Surface recorderSurface = mMediaRecorder.getSurface();

            surfaces.add(recorderSurface);
            mPreviewBuilder.addTarget(recorderSurface);

//            surfaces.add(mImageReader.getSurface());

            final CaptureRequest.Builder captureBuilder
                    = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_STILL_CAPTURE);
//            captureBuilder.addTarget(mImageReader.getSurface());
            captureBuilder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);

//            // The date and time of capturing
//            DateFormat dateFormat = new SimpleDateFormat("ddMMyyyy_HHmmss");
//            Date nowDate = Calendar.getInstance().getTime();
//            String nowDateString = dateFormat.format(nowDate);
//
//            mCapturedImagePath = mVideoFolderPath + "/IMG_" + nowDateString + ".jpg";
//            final File file = new File(mCapturedImagePath);
//
//            ImageReader.OnImageAvailableListener readerListener
//                    = new ImageReader.OnImageAvailableListener() {
//
//                @Override
//                public void onImageAvailable(ImageReader reader) {
//                    Image image = null;
//                    try {
//                        image = reader.acquireLatestImage();
//
//                        ByteBuffer imageBuffer = convertYUV420ToN21(image, false);
////                        byte[] imageBytes = new byte[imageBuffer.limit()];
////                        imageBuffer.get(imageBytes);
//                        byte[] imageBytes = imageBuffer.array();
//
//                        YuvImage yuvImage = new YuvImage(imageBytes, NV21, reader.getWidth(),
//                                reader.getHeight(), null);
//                        ByteArrayOutputStream baos = new ByteArrayOutputStream();
//                        yuvImage.compressToJpeg(new Rect(0, 0, yuvImage.getWidth(),
//                                yuvImage.getHeight()), 80, baos);
//
//                        byte[] bytes = baos.toByteArray();
//
////                        ByteBuffer[] buffers = new ByteBuffer[3];
////                        for (int i = 0; i < 3; i++) {
////                            buffers[i] = image.getPlanes()[i].getBuffer();
////                        }
////
////                        int[] rgbData = new int[buffers[1].limit()];
////                        decodeYUV420SP(rgbData, buffers[0], buffers[1], buffers[2],
////                                reader.getWidth(), reader.getHeight());
////
////                        ByteBuffer byteBuffer = ByteBuffer.allocate(rgbData.length * 4);
////                        IntBuffer intBuffer = byteBuffer.asIntBuffer();
////                        intBuffer.put(rgbData);
////
////                        byte[] bytes = new byte[intBuffer.limit()];
//////                        bytes = byteBuffer.array();
////                        intBuffer.;
//
//                        // Getting the Bitmap object from byte array and writing test on it
//                        Bitmap bm = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
//
//                        int rotation = mActivity.getWindowManager().getDefaultDisplay()
//                                .getRotation();
//                        if(Surface.ROTATION_0 == rotation || Surface.ROTATION_180 == rotation) {
//                            bm = rotateAndScaleBitmap(bm);
//                        }
//
//                        // The date and time of capturing
//                        DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
//                        Date nowDate = Calendar.getInstance().getTime();
//                        String nowDateString = dateFormat.format(nowDate);
//
//                        bm = writeTextOnBitmap(bm, nowDateString);
//
//                        // Making the byte array back from the processed Bitmap object
//                        ByteArrayOutputStream stream = new ByteArrayOutputStream();
//                        bm.compress(Bitmap.CompressFormat.PNG, 100, stream);
//                        byte[] outBytes = stream.toByteArray();
//
////                        mCurrentFrame =
//
////                        save(outBytes);
////                    } catch (FileNotFoundException e) {
////                        e.printStackTrace();
////                    } catch (IOException e) {
////                        e.printStackTrace();
//                    } finally {
//                        if (image != null) {
//                            image.close();
//                        }
//                    }
//                }
//
////                private void save(byte[] bytes) throws IOException {
////                    OutputStream output = null;
////                    try {
////                        output = new FileOutputStream(file);
////
////                        output.write(bytes);
////                    } finally {
////                        if (null != output) {
////                            output.close();
////                        }
////                    }
////                }
//            };
//
//            mImageReader.setOnImageAvailableListener(readerListener, mBackgroundHandler);

            final CameraCaptureSession.CaptureCallback captureListener
                    = new CameraCaptureSession.CaptureCallback() {

                @RequiresApi(api = Build.VERSION_CODES.M)
                @Override
                public void onCaptureCompleted(CameraCaptureSession session, CaptureRequest request,
                                               TotalCaptureResult result) {

                    super.onCaptureCompleted(session, request, result);

//                    Toast.makeText(getContext(), "Saved:" + file,
//                            Toast.LENGTH_SHORT).show();
//                    startPreview();
                }
            };

            // Start a capture session
            // Once the session starts, we can update the UI and start recording
            mCameraDevice.createCaptureSession(surfaces, new CameraCaptureSession.StateCallback() {

                @RequiresApi(api = Build.VERSION_CODES.O)
                @Override
                public void onConfigured(@NonNull CameraCaptureSession cameraCaptureSession) {
                    mPreviewSession = cameraCaptureSession;
                    updateFrame();

                    try {
                        cameraCaptureSession.capture(captureBuilder.build(), captureListener,
                                mBackgroundHandler);
                    } catch (CameraAccessException e) {
                        e.printStackTrace();
                    }

                    mActivity.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            // UI
                            mButtonVideo.setText(R.string.stop);
                            mIsRecordingVideo = true;

//                            mGles20.glBindTexture(GL_TEXTURE_EXTERNAL_OES, mTextures[0]);
////                    checkGlError("glBindTexture mTextureID");
//
//                            mGles20.glTexParameterf(GL_TEXTURE_EXTERNAL_OES,
//                                    GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
//                            mGles20.glTexParameterf(GL_TEXTURE_EXTERNAL_OES,
//                                    GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
//
//                            SurfaceTexture.OnFrameAvailableListener onFrameAvailableListener = new
//                                    SurfaceTexture.OnFrameAvailableListener() {
//                                        @Override
//                                        public void onFrameAvailable(
//                                                SurfaceTexture surfaceTexture) {
//
////                                            SurfaceTexture auxSf = new SurfaceTexture(mTextures[0]);
////                                            surfaceTexture = auxSf;
//
//                                            surfaceTexture.attachToGLContext(mTextures[0]);
//
//                                            saveImage(savePixels(mVideoSize.getWidth(),
//                                                    mVideoSize.getHeight()));
//
////                                    // todo paste the image transform here!
////                                    Parcel parcel = Parcel.obtain();
////                                    recorderSurface.writeToParcel(parcel, 0);
////                                    byte[] surfaceInBytes = parcel.createByteArray();
////
////                                    // Getting the Bitmap object from byte array and writing test on it
////                                    Bitmap bm = BitmapFactory.decodeByteArray(surfaceInBytes, 0, surfaceInBytes.length);
////
////                                    Activity mActivity = getActivity();
////                                    int rotation = mActivity.getWindowManager().getDefaultDisplay().getRotation();
////                                    if(Surface.ROTATION_0 == rotation || Surface.ROTATION_180 == rotation) {
////                                        bm = rotateAndScaleBitmap(bm);
////                                    }
////
////                                    // The date and time of capturing
////                                    DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
////                                    Date nowDate = Calendar.getInstance().getTime();
////                                    String nowDateString = dateFormat.format(nowDate);
////
////                                    bm = writeTextOnBitmap(bm, nowDateString);
////
////                                    // Making the byte array back from the processed Bitmap object
////                                    ByteArrayOutputStream stream = new ByteArrayOutputStream();
////                                    bm.compress(Bitmap.CompressFormat.JPEG, 100, stream);
////                                    byte[] outBytes = stream.toByteArray();
////
////                                    parcel.unmarshall(outBytes, 0, outBytes.length);
////
////                                    recorderSurface.readFromParcel(parcel);
//                                        }
//                                    };

                   /*
* Create the SurfaceTexture that will feed this textureID,
* and pass it to the MediaPlayer
*/
//                            final SurfaceTexture surfaceTexture = new SurfaceTexture(mTextures[0]);
//                            surfaceTexture.setOnFrameAvailableListener(onFrameAvailableListener);
//
//                            Surface surface = new Surface(surfaceTexture);
//                            surface.release();

                            // Start recording
                            mMediaRecorder.start();

                            // Setting the recording time counter
                            mChronometer.setBase(SystemClock.elapsedRealtime());
                            mChronometer.setVisibility(View.VISIBLE);
                            mChronometer.start();

//                            Canvas canvas = surfaces.get(0).lockCanvas(new Rect(0, 0,
//                                    mVideoSize.getWidth(), mVideoSize.getHeight()));
//
//                            // Draw the text
//                            Paint textPaint = new Paint();
//                            float textSizePx = 100;
//                            textPaint.setTextSize(textSizePx);
//                            textPaint.setStyle(Paint.Style.FILL);
//                            textPaint.setAntiAlias(true);
//                            textPaint.setColor(Color.RED);
//
//                            // The date and time of capturing
//                            DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
//                            Date nowDate = Calendar.getInstance().getTime();
//                            String nowDateString = dateFormat.format(nowDate);
//
//                            // Draw the text at the upper left corner
//                            canvas.drawText(nowDateString, 0,textSizePx, textPaint);
//
//                            surfaces.get(0).unlockCanvasAndPost(canvas);
                        }
                    });
                }

                @Override
                public void onConfigureFailed(@NonNull CameraCaptureSession cameraCaptureSession) {
                    if (null != mActivity) {
                        Toast.makeText(mActivity, "Failed", Toast.LENGTH_SHORT).show();
                    }
                }
            }, mBackgroundHandler);
        } catch (CameraAccessException/* | IOException*/ e) {
            e.printStackTrace();
        }
    }

    public void stopCamera() {
//        mediaRecorderPostprocessing();

        // UI
        mIsRecordingVideo = false;
        mButtonVideo.setText(R.string.record);
        // Stop recording
        mMediaRecorder.stop();
        mMediaRecorder.reset();

        if (null != mActivity) {
            Toast.makeText(mActivity, "Video saved: " + mNextVideoAbsolutePath,
                    Toast.LENGTH_SHORT).show();
            Log.d(TAG, "Video saved: " + mNextVideoAbsolutePath);
        }
        mDeleteFileButton.setVisibility(View.VISIBLE);
        mNextVideoAbsolutePath = null;
        startPreview();
    }
}
