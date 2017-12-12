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

package com.example.android.camera2video;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.app.Fragment;
import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.ImageFormat;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.SurfaceTexture;
import android.graphics.YuvImage;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
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
import android.media.MediaCodec;
import android.media.MediaExtractor;
import android.media.MediaFormat;
import android.media.MediaRecorder;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.os.Build;
import android.os.Bundle;
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
import android.view.LayoutInflater;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Chronometer;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.List;
import java.util.Random;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

import static android.graphics.ImageFormat.NV21;
import static android.opengl.GLES11Ext.GL_TEXTURE_EXTERNAL_OES;

@RequiresApi(api = Build.VERSION_CODES.M)
public class Camera2VideoFragment extends Fragment
        implements View.OnClickListener, FragmentCompat.OnRequestPermissionsResultCallback,
        MobiServiceable {

//    private static final int SENSOR_ORIENTATION_DEFAULT_DEGREES = 90;
//    private static final int SENSOR_ORIENTATION_INVERSE_DEGREES = 270;
//    private static final SparseIntArray DEFAULT_ORIENTATIONS = new SparseIntArray();
//    private static final SparseIntArray INVERSE_ORIENTATIONS = new SparseIntArray();

    private static final String TAG = "Camera2VideoFragment";
    private static final int REQUEST_VIDEO_PERMISSIONS = 1;
    private static final String FRAGMENT_DIALOG = "dialog";

    private static final String[] VIDEO_PERMISSIONS = {
            Manifest.permission.CAMERA,
            Manifest.permission.RECORD_AUDIO,
    };

//    static {
//        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_0, 90);
//        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_90, 0);
//        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_180, 270);
//        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_270, 180);
//    }
//
//    static {
//        INVERSE_ORIENTATIONS.append(Surface.ROTATION_0, 270);
//        INVERSE_ORIENTATIONS.append(Surface.ROTATION_90, 180);
//        INVERSE_ORIENTATIONS.append(Surface.ROTATION_180, 90);
//        INVERSE_ORIENTATIONS.append(Surface.ROTATION_270, 0);
//    }

//    /**
//     * A reference to the opened {@link CameraDevice}.
//     */
//    private CameraDevice mCameraDevice;

//    /**
//     * A reference to the current {@link CameraCaptureSession} for
//     * preview.
//     */
//    private CameraCaptureSession mPreviewSession;

    /**
     * {@link TextureView.SurfaceTextureListener} handles several lifecycle events on a
     * {@link TextureView}.
     */
    private TextureView.SurfaceTextureListener mSurfaceTextureListener
            = new TextureView.SurfaceTextureListener() {

        @Override
        public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture,
                                              int width, int height) {
//            openCamera(width, height);
//            mContext.startService(mRecordingIntent); // todo find out whether it's needed or not
        }

        @Override
        public void onSurfaceTextureSizeChanged(SurfaceTexture surfaceTexture,
                                                int width, int height) {
            mRecorderService.configureTransform(width, height);
        }

        @Override
        public boolean onSurfaceTextureDestroyed(SurfaceTexture surfaceTexture) {
            return true;
        }

        @Override
        public void onSurfaceTextureUpdated(SurfaceTexture surfaceTexture) {
        }

    };

//    /**
//     * The {@link Size} of camera preview.
//     */
//    private Size mPreviewSize;

//    /**
//     * The {@link Size} of video recording.
//     */
//    private Size mVideoSize;

//    /**
//     * MediaRecorder
//     */
//    private MediaRecorder mMediaRecorder;

    /**
     * Whether the app is recording video now
     */
    private boolean mIsRecordingVideo;

//    /**
//     * An additional thread for running tasks that shouldn't block the UI.
//     */
//    private HandlerThread mBackgroundThread;

//    /**
//     * A {@link Handler} for running tasks in the background.
//     */
//    private Handler mBackgroundHandler;

//    /**
//     * A {@link Semaphore} to prevent the app from exiting before closing the camera.
//     */
//    private Semaphore mCameraOpenCloseLock = new Semaphore(1);

    private String mCameraId;

    public void setTorchFlag(boolean torchFlag) {
        mTorchFlag = torchFlag;
    }

    boolean mTorchFlag = false;

    boolean mTorchOnFlag = false;

    private ImageReader mImageReader;
    private Image mCurrentFrame;

    private String mCapturedImagePath;
    private String mVideoFolderPath;
    private String mRecordedVideoFileName;

    private RecorderService mRecorderService;
    private Intent mRecordingIntent;

    GLES20 mGles20 = mRecorderService.getGles20();
    int[] mTextures = mRecorderService.getTextures();

    private Activity mActivity;
    private Context mContext;

    // UI section

    /**
     * An {@link AutoFitTextureView} for camera preview.
     */
    private AutoFitTextureView mTextureView;

    /**
     * Button to record video
     */
    private Button mButtonVideo;

    private ImageButton mDeleteFileButton;

    private ImageButton mToggleFlashButton;

    private Chronometer mChronometer;

    public static Camera2VideoFragment newInstance() {
        return new Camera2VideoFragment();
    }

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
//        if (null == mActivity) {
//            return;
//        }
//        mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
//        mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.SURFACE);
//        mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
//        if (mNextVideoAbsolutePath == null || mNextVideoAbsolutePath.isEmpty()) {
//            mNextVideoAbsolutePath = getVideoFilePath(mActivity);
//            mDeleteFileButton.setVisibility(View.INVISIBLE);
//        }
//        mMediaRecorder.setOutputFile(mNextVideoAbsolutePath);
//        mMediaRecorder.setVideoEncodingBitRate(10000000);
//        mMediaRecorder.setVideoFrameRate(30);
//        mMediaRecorder.setVideoSize(mVideoSize.getWidth(), mVideoSize.getHeight());
//        mMediaRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.H264);
//        mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AAC);
//        int rotation = mActivity.getWindowManager().getDefaultDisplay().getRotation();
//        switch (mSensorOrientation) {
//            case SENSOR_ORIENTATION_DEFAULT_DEGREES:
//                mMediaRecorder.setOrientationHint(DEFAULT_ORIENTATIONS.get(rotation));
//                break;
//            case SENSOR_ORIENTATION_INVERSE_DEGREES:
//                mMediaRecorder.setOrientationHint(INVERSE_ORIENTATIONS.get(rotation));
//                break;
//        }
//
//        try {
//            mMediaRecorder.prepare();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
    }

    private int setGlTexture(Bitmap sourceBm) {
        // Generate one texture pointer...
        mGles20.glGenTextures(1, mTextures, 0);
        // ...and bind it to our array
        mGles20.glBindTexture(GLES20.GL_TEXTURE_2D, mTextures[0]);

        // Create Nearest Filtered Texture
        mGles20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
        mGles20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);

        // Different possible texture parameters, e.g. GLES20.GL_CLAMP_TO_EDGE
        mGles20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_REPEAT);
        mGles20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_REPEAT);

        // Use the Android GLUtils to specify a two-dimensional texture image from our bitmap
        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, sourceBm, 0);

        return mTextures[0];
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

//        setGlTexture(resultBm);

        return resultBm;
    }

    private Bitmap writeTextOnBitmap(Bitmap source, String captionString) {
        Bitmap newBitmap = null;

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

    private void mediaRecorderPostprocessing() {
        String mimeType = "video/avc";

        MediaCodec codec = null;
        try {
            codec = MediaCodec.createDecoderByType(mimeType);
        } catch (IOException e) {
            e.printStackTrace();
        }

        MediaFormat format = MediaFormat.createVideoFormat(mimeType, 720, 480);
        byte[] header_sps = {0, 0, 0, 1, 0x67, 0x42, 0x00, 0x1f, (byte) 0xe9, 0x01, 0x68, 0x7b, (byte) 0x20}; // sps
        byte[] header_pps = {0, 0, 0, 1, 0x68, (byte) 0xce, 0x06, (byte) 0xf2}; // pps
        format.setByteBuffer("csd-0", ByteBuffer.wrap(header_sps));
        format.setByteBuffer("csd-1", ByteBuffer.wrap(header_pps));

        format.setInteger(MediaFormat.KEY_MAX_INPUT_SIZE, 720 * 480);
        codec.configure(format, null, null, 0);
        codec.start();
        boolean isCodecRecording = true;

        RandomAccessFile dis = null;
        try {
            dis = new RandomAccessFile(mNextVideoAbsolutePath, "r");
            byte buffer[] = new byte[4];
            // Skip all atoms preceding mdat atom
            while (true) {
                while (dis.read() != 'm')
                    ;
                dis.read(buffer, 0, 3);
                if (buffer[0] == 'd' &&
                        buffer[1] == 'a' &&
                        buffer[2] == 't')
                    break;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            Log.e(TAG, "Couldn't skip mp4 header :/");
            return;
        }

        MediaExtractor extractor = new MediaExtractor();
//                            MediaFormat format;
        try {
            extractor.setDataSource(mNextVideoAbsolutePath);
        } catch (IOException e) {
            e.printStackTrace();
        }
//                            int numTracks = extractor.getTrackCount();
//                            for (int i = 0; i < numTracks; ++i) {
//                                format = extractor.getTrackFormat(i);
//                                String mime = format.getString(MediaFormat.KEY_MIME);
//                                if (mime.startsWith("video/")) {
//                                    extractor.selectTrack(i);
//                                    break;
//                                }
//                            }

        boolean sawInputEOS = false;

        while (!sawInputEOS) {
            int inputBufIndex = codec.dequeueInputBuffer(10000);
            if (inputBufIndex >= 0) {
                ByteBuffer dstBuf = codec.getInputBuffer(inputBufIndex);
//                                int sampleSize = extractor.readSampleData(dstBuf, 0 /* offset */);
                byte[] bt = new byte[dstBuf.capacity()];
                dstBuf.get(bt);

                byte[] sampleData = new byte[1000];
//while loop
                int length = 0;
                try {
                    length = dis.read(sampleData, 0, 4);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (length != -1) {
                    int sampleSize = (sampleData[0] << 24)
                            & 0xff000000 | (sampleData[1] << 16)
                            & 0xff0000 | (sampleData[2] << 8)
                            & 0xff00 | (sampleData[3]) & 0xff;
                    sampleData[0] = 0;
                    sampleData[1] = 0;
                    sampleData[2] = 0;
                    sampleData[3] = 1;
                    int remainData = sampleSize;
                    dstBuf.clear();
                    for (int i = 0; remainData > 0; i++) {
                        int a = ((i == 0) ? (sampleData.length - 4) : sampleData.length);
                        int b = ((i == 0) ? 4 : 0);
                        if (remainData < a) {
                            try {
                                dis.read(sampleData, b, remainData);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            dstBuf.put(sampleData, 0, remainData);
                        } else {
                            try {
                                dis.read(sampleData, b, a);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            dstBuf.put(sampleData, 0, sampleData.length);
                        }
                        remainData = remainData - a;
                    }
                    codec.queueInputBuffer(
                            inputBufIndex,
                            0 /* offset */,
                            sampleSize + 4,
                            0,
                            sawInputEOS ? MediaCodec.BUFFER_FLAG_END_OF_STREAM
                                    : 0);
                } else {
                    Log.d(TAG, "saw sawInputEOS");
                    sawInputEOS = true;
                }

                dstBuf.clear();
                String s = "";
                for (int i = 0; i < 6; i++) {
                    s += "0x" + Integer.toHexString(bt[i]) + " ";
                }
                Log.d(TAG, "input: " + dstBuf + ", " + /*sampleSize + */", " + s);
            }
        }
    }

    private int[] decodeYUV420SPsingleBuf(byte[] yuv420p, int width, int height) {

        final int frameSize = width * height;
        int[] myPixels = new int[width * height];
        for (int j = 0, yp = 0; j < height; j++) {
            int u = 0, v = 0, uIndex = 0, vIndex = 0;

            for (int i = 0; i < width; i++, yp++) {
                int y = (0xff & ((int) yuv420p[yp])) - 16;
                if (y < 0) y = 0;
                if ((i & 1) == 0) {
                    uIndex = frameSize + ((width >> 1) * (j >> 1)) + (i >> 1);
                    vIndex = uIndex + (frameSize >> 2);
                    u = (0xff & yuv420p[uIndex]) - 128;
                    v = (0xff & yuv420p[vIndex]) - 128;
                }
                int y1192 = 1192 * y;
                int r = (y1192 + 1634 * v);
                int g = (y1192 - 833 * v - 400 * u);
                int b = (y1192 + 2066 * u);

                if (r < 0)
                    r = 0;
                else if (r > 262143)
                    r = 262143;
                if (g < 0)
                    g = 0;
                else if (g > 262143)
                    g = 262143;
                if (b < 0)
                    b = 0;
                else if (b > 262143)
                    b = 262143;

                myPixels[yp] = 0xff000000 | ((r << 6) & 0xff0000)
                        | ((g >> 2) & 0xff00) | ((b >> 10) & 0xff);
            }
        }
        return myPixels;
    }

    private void decodeYUV420SP(int[] rgb, ByteBuffer yBuf, ByteBuffer cbBuf, ByteBuffer crBuf,
                                int width, int height) {
        Log.e("camera", "   decodeYUV420SP  ");

        // TODO Auto-generated method stub
        final int frameSize = width * height;

//        for (int j = 0, yp = 0; j < height; j++) {
////            int uvp = frameSize + (j >> 1) * width, u = 0, v = 0;
//            for (int i = 0; i < width; i++, yp++) {
////                int y = (0xff & ((int) yuv420sp[yp])) - 16;
////                if (y < 0) y = 0;
////                if ((i & 1) == 0) {
////                    v = (0xff & yuv420sp[uvp++]) - 128;
////                    u = (0xff & yuv420sp[uvp++]) - 128;
////                }
        byte[] yBytes = new byte[yBuf.limit()];
        yBuf.get(yBytes);
        byte[] cbBytes = new byte[cbBuf.limit()];
        cbBuf.get(cbBytes);
        byte[] crBytes = new byte[crBuf.limit()];
        crBuf.get(crBytes);

        for (int i = 0; i < cbBuf.limit(); i++) {
//            int y = 0; //yBytes[i];
//            int u = cbBytes[i];
//            int v = 0; //crBytes[i];

//            int y1192 = 1192 * y;
//            int r = (y1192 + 1634 * v);
//            int g = (y1192 - 833 * v - 400 * u);
//            int b = (y1192 + 2066 * u);

            int r = yBytes[i];
            int g = cbBytes[i];
            int b = crBytes[i];

            if (r < 0) r = 0; else if (r > 262143) r = 262143;
            if (g < 0) g = 0; else if (g > 262143) g = 262143;
            if (b < 0) b = 0; else if (b > 262143) b = 262143;

            rgb[i] = 0xff000000 | ((r << 6) & 0xff0000) | ((g >> 2) & 0xff00)
                    | ((b >> 10) & 0xff);
//            }
        }
    }

    private byte[] getRawCopy(ByteBuffer in) {
        ByteBuffer rawCopy = ByteBuffer.allocate(in.capacity());
        rawCopy.put(in);
        return rawCopy.array();
    }

    private void fastReverse(byte[] array, int offset, int length) {
        int end = offset + length;
        for (int i = offset; i < offset + (length / 2); i++) {
            array[i] = (byte)(array[i] ^ array[end - i  - 1]);
            array[end - i  - 1] = (byte)(array[i] ^ array[end - i  - 1]);
            array[i] = (byte)(array[i] ^ array[end - i  - 1]);
        }
    }

    private ByteBuffer convertYUV420ToN21(Image imgYUV420, boolean grayscale) {
        Image.Plane yPlane = imgYUV420.getPlanes()[0];
        byte[] yData = getRawCopy(yPlane.getBuffer());

        Image.Plane uPlane = imgYUV420.getPlanes()[1];
        byte[] uData = getRawCopy(uPlane.getBuffer());

        Image.Plane vPlane = imgYUV420.getPlanes()[2];
        byte[] vData = getRawCopy(vPlane.getBuffer());

        // NV21 stores a full frame luma (y) and half frame chroma (u,v), so total size is
        // size(y) + size(y) / 2 + size(y) / 2 = size(y) + size(y) / 2 * 2 = size(y) + size(y) = 2 * size(y)
        int npix = imgYUV420.getWidth() * imgYUV420.getHeight();
        byte[] nv21Image = new byte[npix * 2];
        Arrays.fill(nv21Image, (byte)127); // 127 -> 0 chroma (luma will be overwritten in either case)

        // Copy the Y-plane
        ByteBuffer nv21Buffer = ByteBuffer.wrap(nv21Image);
        for(int i = 0; i < imgYUV420.getHeight(); i++) {
            nv21Buffer.put(yData, i * yPlane.getRowStride(), imgYUV420.getWidth());
        }

        // Copy the u and v planes interlaced
        if(!grayscale) {
            for (int row = 0; row < imgYUV420.getHeight() / 2; row++) {
                for (int cnt = 0, upix = 0, vpix = 0; cnt < imgYUV420.getWidth() / 2;
                     upix += uPlane.getPixelStride(), vpix += vPlane.getPixelStride(), cnt++) {
                    nv21Buffer.put(uData[row * uPlane.getRowStride() + upix]);
                    nv21Buffer.put(vData[row * vPlane.getRowStride() + vpix]);
                }
            }

            fastReverse(nv21Image, npix, npix);
        }

        fastReverse(nv21Image, 0, npix);

        return nv21Buffer;
    }

    private Bitmap savePixels(int w, int h) {
        int b[] = new int[w * h];
        int bt[] = new int[w * h];
        IntBuffer ib = IntBuffer.wrap(b);
        ib.position(0);
        GLES20.glReadPixels(0, 0, w, h, GLES20.GL_RGBA, GLES20.GL_UNSIGNED_BYTE, ib);

        for (int i = 0, k = 0; i < h; i++, k++) {
            //remember, that OpenGL bitmap is incompatible with Android bitmap
            //and so, some correction need.
            for (int j = 0; j < w; j++) {
                int pix = b[i * w + j];
                int pb = (pix >> 16) & 0xff;
                int pr = (pix << 16) & 0x00ff0000;
                int pix1 = (pix & 0xff00ff00) | pr | pb;
                bt[(h - k - 1) * w + j] = pix1;
            }
        }

        Bitmap sb = Bitmap.createBitmap(bt, w, h, Bitmap.Config.ARGB_8888);
        return sb;
    }

    private void saveImage(Bitmap finalBitmap) {
        File myDir = new File(mVideoFolderPath);
        myDir.mkdirs();
        Random generator = new Random();
        int n = 10000;
        n = generator.nextInt(n);
        String fname = "Image-" + n + ".jpg";
        File file = new File(myDir, fname);
        if (file.exists()) file.delete();
        try {
            FileOutputStream out = new FileOutputStream(file);
            finalBitmap.compress(Bitmap.CompressFormat.JPEG, 90, out);
            out.flush();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private class DrawThread extends Thread {
        private boolean runFlag = false;
        private SurfaceHolder surfaceHolder;
        private Bitmap picture;
        private Matrix matrix;
        private long prevTime;

        public DrawThread(SurfaceHolder surfaceHolder) {
            this.surfaceHolder = surfaceHolder;

            // загружаем картинку, которую будем отрисовывать
            picture = BitmapFactory.decodeResource(getResources(), R.drawable.ic_launcher);
//            picture = savePixels(mVideoSize.getWidth(), mVideoSize.getHeight());

            // формируем матрицу преобразований для картинки
            matrix = new Matrix();
            matrix.postScale(3.0f, 3.0f);
            matrix.postTranslate(100.0f, 100.0f);

            // сохраняем текущее время
            prevTime = System.currentTimeMillis();
        }

        public void setRunning(boolean run) {
            runFlag = run;
        }

        @Override
        public void run() {
            Canvas canvas;
            while (runFlag) {
                // получаем текущее время и вычисляем разницу с предыдущим
                // сохраненным моментом времени
                long now = System.currentTimeMillis();
                long elapsedTime = now - prevTime;
                if (elapsedTime > 30){
                    // если прошло больше 30 миллисекунд - сохраним текущее время
                    // и повернем картинку на 2 градуса.
                    // точка вращения - центр картинки
                    prevTime = now;
                    matrix.preRotate(2.0f, picture.getWidth() / 2, picture.getHeight() / 2);
                }
                canvas = null;
                try {
                    // получаем объект Canvas и выполняем отрисовку
                    canvas = surfaceHolder.lockCanvas(null);
                    synchronized (surfaceHolder) {
                        canvas.drawColor(Color.BLACK);
                        canvas.drawBitmap(picture, matrix, null);
                    }
                }
                finally {
                    if (canvas != null) {
                        // отрисовка выполнена. выводим результат на экран
                        surfaceHolder.unlockCanvasAndPost(canvas);
                    }
                }
            }
        }
    }

    private class SingleFrame extends SurfaceView implements SurfaceHolder.Callback {
        private DrawThread mDrawThread;
        private SurfaceHolder mSurfaceHolder;

//        public void setSurfaceTexture(SurfaceTexture surfaceTexture) {
//            mSurfaceTexture = surfaceTexture;
//        }

//        private SurfaceTexture mSurfaceTexture;
//        private Surface mSurface;

        public SingleFrame(Context context) {
            super(context);
            mSurfaceHolder = getHolder();
            mSurfaceHolder.addCallback(this);
        }

        @Override
        public void surfaceCreated(SurfaceHolder holder) {
            mDrawThread = new DrawThread(getHolder());
            mDrawThread.setRunning(true);
            mDrawThread.start();

//            mSurfaceHolder = holder;
////            mSurface = holder.getSurface();
//
//            Canvas canvas = mSurfaceHolder.lockCanvas();
//
//            // Draw the text
//            Paint textPaint = new Paint();
//            float textSizePx = 100;
//            textPaint.setTextSize(textSizePx);
//            textPaint.setStyle(Paint.Style.FILL);
//            textPaint.setAntiAlias(true);
//            textPaint.setColor(Color.RED);
//
//            // The date and time of capturing
//            DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
//            Date nowDate = Calendar.getInstance().getTime();
//            String nowDateString = dateFormat.format(nowDate);
//
//            // Draw the text at the upper left corner
//            canvas.drawText(nowDateString, 0,textSizePx, textPaint);
//
//            mSurfaceHolder.unlockCanvasAndPost(canvas);
        }

        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

        }

        @Override
        public void surfaceDestroyed(SurfaceHolder holder) {
            boolean retry = true;
            // завершаем работу потока
            mDrawThread.setRunning(false);
            while (retry) {
                try {
                    mDrawThread.join();
                    retry = false;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    // если не получилось, то будем пытаться еще и еще
                }
            }
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    public void startCamera() {
//        if (null == mCameraDevice || !mTextureView.isAvailable() || null == mPreviewSize) {
//            return;
//        }
//        try {
//            closePreviewSession();
//            configureCamera();
//            SurfaceTexture texture = mTextureView.getSurfaceTexture();
//            assert texture != null;
//            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
//            mPreviewBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_RECORD);
//            final List<Surface> surfaces = new ArrayList<>();
//
//            // Set up Surface for the camera preview
//            Surface previewSurface = new Surface(texture);
//            surfaces.add(previewSurface);
//            mPreviewBuilder.addTarget(previewSurface);
//
//            // Set up Surface for the MediaRecorder
//            Surface recorderSurface = mMediaRecorder.getSurface();
//
//            surfaces.add(recorderSurface);
//            mPreviewBuilder.addTarget(recorderSurface);
//
//            surfaces.add(mImageReader.getSurface());
//
//            final CaptureRequest.Builder captureBuilder
//                    = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_STILL_CAPTURE);
//            captureBuilder.addTarget(mImageReader.getSurface());
//            captureBuilder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);
//
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
//
//            final CameraCaptureSession.CaptureCallback captureListener
//                    = new CameraCaptureSession.CaptureCallback() {
//
//                @RequiresApi(api = Build.VERSION_CODES.M)
//                @Override
//                public void onCaptureCompleted(CameraCaptureSession session, CaptureRequest request,
//                                               TotalCaptureResult result) {
//
//                    super.onCaptureCompleted(session, request, result);
//
////                    Toast.makeText(getContext(), "Saved:" + file,
////                            Toast.LENGTH_SHORT).show();
////                    startPreview();
//                }
//            };
//
//            // Start a capture session
//            // Once the session starts, we can update the UI and start recording
//            mCameraDevice.createCaptureSession(surfaces, new CameraCaptureSession.StateCallback() {
//
//                @RequiresApi(api = Build.VERSION_CODES.O)
//                @Override
//                public void onConfigured(@NonNull CameraCaptureSession cameraCaptureSession) {
//                    mPreviewSession = cameraCaptureSession;
//                    updateFrame();
//
//                    try {
//                        cameraCaptureSession.capture(captureBuilder.build(), captureListener,
//                                mBackgroundHandler);
//                    } catch (CameraAccessException e) {
//                        e.printStackTrace();
//                    }
//
//                    mActivity.runOnUiThread(new Runnable() {
//                        @Override
//                        public void run() {
//                            // UI
//                            mButtonVideo.setText(R.string.stop);
//                            mIsRecordingVideo = true;
//
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
//
//                   /*
//* Create the SurfaceTexture that will feed this textureID,
//* and pass it to the MediaPlayer
//*/
//                            final SurfaceTexture surfaceTexture = new SurfaceTexture(mTextures[0]);
//                            surfaceTexture.setOnFrameAvailableListener(onFrameAvailableListener);
//
//                            Surface surface = new Surface(surfaceTexture);
//                            surface.release();
//
//                            // Start recording
//                            mMediaRecorder.start();
//
//                            // Setting the recording time counter
//                            mChronometer.setBase(SystemClock.elapsedRealtime());
//                            mChronometer.setVisibility(View.VISIBLE);
//                            mChronometer.start();
//
////                            Canvas canvas = surfaces.get(0).lockCanvas(new Rect(0, 0,
////                                    mVideoSize.getWidth(), mVideoSize.getHeight()));
////
////                            // Draw the text
////                            Paint textPaint = new Paint();
////                            float textSizePx = 100;
////                            textPaint.setTextSize(textSizePx);
////                            textPaint.setStyle(Paint.Style.FILL);
////                            textPaint.setAntiAlias(true);
////                            textPaint.setColor(Color.RED);
////
////                            // The date and time of capturing
////                            DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
////                            Date nowDate = Calendar.getInstance().getTime();
////                            String nowDateString = dateFormat.format(nowDate);
////
////                            // Draw the text at the upper left corner
////                            canvas.drawText(nowDateString, 0,textSizePx, textPaint);
////
////                            surfaces.get(0).unlockCanvasAndPost(canvas);
//                        }
//                    });
//                }
//
//                @Override
//                public void onConfigureFailed(@NonNull CameraCaptureSession cameraCaptureSession) {
//                    if (null != mActivity) {
//                        Toast.makeText(mActivity, "Failed", Toast.LENGTH_SHORT).show();
//                    }
//                }
//            }, mBackgroundHandler);
//        } catch (CameraAccessException/* | IOException*/ e) {
//            e.printStackTrace();
//        }
    }

    @Override
    public void stopCamera() {
////        mediaRecorderPostprocessing();
//
//        // UI
//        mIsRecordingVideo = false;
//        mButtonVideo.setText(R.string.record);
//        // Stop recording
//        mMediaRecorder.stop();
//        mMediaRecorder.reset();
//
//        if (null != mActivity) {
//            Toast.makeText(mActivity, "Video saved: " + mNextVideoAbsolutePath,
//                    Toast.LENGTH_SHORT).show();
//            Log.d(TAG, "Video saved: " + mNextVideoAbsolutePath);
//        }
//        mDeleteFileButton.setVisibility(View.VISIBLE);
//        mNextVideoAbsolutePath = null;
//        startPreview();
    }

    @Override
    public void switchCamera() {

    }

//    /**
//    * Update the camera preview. {@link #startPreview()} needs to be called in advance.
//    */
    @Override
    public void updateFrame() {
//        if (null == mCameraDevice) {
//            return;
//        }
//        try {
//            setUpCaptureRequestBuilder(mPreviewBuilder);
//            HandlerThread thread = new HandlerThread("CameraPreview");
//            thread.start();
//            mPreviewSession.setRepeatingRequest(mPreviewBuilder.build(), null, mBackgroundHandler);
//        } catch (CameraAccessException e) {
//            e.printStackTrace();
//        }
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

//    /**
//     * {@link CameraDevice.StateCallback} is called when {@link CameraDevice} changes its status.
//     */
//    private CameraDevice.StateCallback mStateCallback = new CameraDevice.StateCallback() {
//
//        @Override
//        public void onOpened(@NonNull CameraDevice cameraDevice) {
//            mCameraDevice = cameraDevice;
//            startPreview();
//            mCameraOpenCloseLock.release();
//            if (null != mTextureView) {
//                configureTransform(mTextureView.getWidth(), mTextureView.getHeight());
//            }
//        }
//
//        @Override
//        public void onDisconnected(@NonNull CameraDevice cameraDevice) {
//            mCameraOpenCloseLock.release();
//            cameraDevice.close();
//            mCameraDevice = null;
//        }
//
//        @Override
//        public void onError(@NonNull CameraDevice cameraDevice, int error) {
//            mCameraOpenCloseLock.release();
//            cameraDevice.close();
//            mCameraDevice = null;
//            if (null != mActivity) {
//                mActivity.finish();
//            }
//        }
//
//    };

//    private Integer mSensorOrientation;
    private String mNextVideoAbsolutePath;
//    private String mRecordedVideoFileName;
//    private CaptureRequest.Builder mPreviewBuilder;

    public Camera2VideoFragment() {

    }

//    /**
//     * In this sample, we choose a video size with 3x4 aspect ratio. Also, we don't use sizes
//     * larger than 1080p, since MediaRecorder cannot handle such a high-resolution video.
//     *
//     * @param choices The list of available sizes
//     * @return The video size
//     */
//    private static Size chooseVideoSize(Size[] choices) {
//        for (Size size : choices) {
//            if (size.getWidth() == size.getHeight() * 4 / 3 && size.getWidth() <= 1080) {
//                return size;
//            }
//        }
//        Log.e(TAG, "Couldn't find any suitable video size");
//        return choices[choices.length - 1];
//    }
//
//    /**
//     * Given {@code choices} of {@code Size}s supported by a camera, chooses the smallest one whose
//     * width and height are at least as large as the respective requested values, and whose aspect
//     * ratio matches with the specified value.
//     *
//     * @param choices     The list of sizes that the camera supports for the intended output class
//     * @param width       The minimum desired width
//     * @param height      The minimum desired height
//     * @param aspectRatio The aspect ratio
//     * @return The optimal {@code Size}, or an arbitrary one if none were big enough
//     */
//    private static Size chooseOptimalSize(Size[] choices, int width, int height, Size aspectRatio) {
//        // Collect the supported resolutions that are at least as big as the preview Surface
//        List<Size> bigEnough = new ArrayList<>();
//        int w = aspectRatio.getWidth();
//        int h = aspectRatio.getHeight();
//        for (Size option : choices) {
//            if (option.getHeight() == option.getWidth() * h / w &&
//                    option.getWidth() >= width && option.getHeight() >= height) {
//                bigEnough.add(option);
//            }
//        }
//
//        // Pick the smallest of those, assuming we found any
//        if (bigEnough.size() > 0) {
//            return Collections.min(bigEnough, new CompareSizesByArea());
//        } else {
//            Log.e(TAG, "Couldn't find any suitable preview size");
//            return choices[0];
//        }
//    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_camera2_video, container, false);
    }

    @Override
    public void onViewCreated(final View view, Bundle savedInstanceState) {

        // todo suspicious technique
        mTextureView = view.findViewById(R.id.texture);
        mRecorderService.setTextureView(mTextureView);

//        mSingleFrame = new SingleFrame(getContext());
//        mSingleFrame = (SurfaceView) view.findViewById(R.id.glTexture);

        mButtonVideo = view.findViewById(R.id.video);
        mButtonVideo.setOnClickListener(this);
        mRecorderService.setButtonVideo(mButtonVideo);

        view.findViewById(R.id.info).setOnClickListener(this);

        mDeleteFileButton = view.findViewById(R.id.deleteFile);
        mDeleteFileButton.setOnClickListener(this);
        mRecorderService.setDeleteFileButton(mDeleteFileButton);

//        mToggleFlashButton = view.findViewById(R.id.flash_off);
//        mToggleFlashButton.setOnClickListener(this);

        mChronometer = view.findViewById(R.id.chronometer);
        mRecorderService.setChronometer(mChronometer);

//        mRecorderService = new RecorderService();

        mNextVideoAbsolutePath = mRecorderService.getNextVideoAbsolutePath();

        mActivity = getActivity();
        mRecorderService.setActivity(mActivity);

        mContext = getContext();
        mRecorderService.setContext(mContext);
    }

    @Override
    public void onResume() {
        super.onResume();
//        startBackgroundThread(); // todo find out where to place it
        if (mTextureView.isAvailable()) {
            openCamera(mTextureView.getWidth(), mTextureView.getHeight());
        } else {
            mTextureView.setSurfaceTextureListener(mSurfaceTextureListener);
        }
    }

    @Override
    public void onPause() {
        closeCamera();
//        stopBackgroundThread();  // todo find out where to place it
        super.onPause();
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.video: {
                if (mIsRecordingVideo) {
                    mChronometer.stop();
                    mChronometer.setVisibility(View.INVISIBLE);

//                    stopCamera();
                    mContext.stopService(mRecordingIntent);
                } else {
//                    startCamera();
//                    mContext = getContext();
                    mRecordingIntent = new Intent(mContext, RecorderService.class);
                    mContext.startService(mRecordingIntent);
                }
                break;
            }

            case R.id.info: {
                if (null != mActivity) {
                    new AlertDialog.Builder(mActivity)
                            .setMessage(R.string.intro_message)
                            .setPositiveButton(android.R.string.ok, null)
                            .show();
                }
                break;
            }

            case R.id.deleteFile: {
                if (null != mRecordedVideoFileName) {
                    File recordedFile = new File(mVideoFolderPath, mRecordedVideoFileName);
                    boolean isFileDeleted = recordedFile.delete();
                    if (isFileDeleted) {
                        Toast.makeText(mContext, "File " + mVideoFolderPath + "/"
                                + mRecordedVideoFileName + " has been deleted!",
                                Toast.LENGTH_SHORT).show();
                        mDeleteFileButton.setVisibility(View.INVISIBLE);
                    }
                }
                break;
            }

//            case R.id.flash: {
//                try {
//                    mCameraId = mCameraManager.getCameraIdList()[0];
//
//                    if (mTorchOnFlag) {
//                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
//                            mCameraManager.setTorchMode(mCameraId, false);
//                            mToggleFlashButton.setImageResource(R.mipmap.flash_off);
//                        }
//                        mTorchOnFlag = false;
//                    } else {
//                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
//                            mCameraManager.setTorchMode(mCameraId, true);
//                            mToggleFlashButton.setImageResource(R.mipmap.flash_on);
//                        }
//                        mTorchOnFlag = true;
//                    }
//                } catch (Exception e) {
//                    e.printStackTrace();
//                }
//                break;
//            }
        }
    }

//    /**
//     * Starts a background thread and its {@link Handler}.
//     */
//    private void startBackgroundThread() {
//        mBackgroundThread = new HandlerThread("CameraBackground");
//        mBackgroundThread.start();
//        mBackgroundHandler = new Handler(mBackgroundThread.getLooper());
//    }
//
//    /**
//     * Stops the background thread and its {@link Handler}.
//     */
//    private void stopBackgroundThread() {
//        mBackgroundThread.quitSafely();
//        try {
//            mBackgroundThread.join();
//            mBackgroundThread = null;
//            mBackgroundHandler = null;
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
//    }

//    /**
//     * Gets whether you should show UI with rationale for requesting permissions.
//     *
//     * @param permissions The permissions your app wants to request.
//     * @return Whether you can show permission rationale UI.
//     */
//    private boolean shouldShowRequestPermissionRationale(String[] permissions) {
//        for (String permission : permissions) {
//            if (FragmentCompat.shouldShowRequestPermissionRationale(this, permission)) {
//                return true;
//            }
//        }
//        return false;
//    }

//    /**
//     * Requests permissions needed for recording video.
//     */
//    private void requestVideoPermissions() {
//        if (shouldShowRequestPermissionRationale(VIDEO_PERMISSIONS)) {
//            new ConfirmationDialog().show(getChildFragmentManager(), FRAGMENT_DIALOG);
//        } else {
//            FragmentCompat.requestPermissions(this, VIDEO_PERMISSIONS, REQUEST_VIDEO_PERMISSIONS);
//        }
//    }

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

//    private boolean hasPermissionsGranted(String[] permissions) {
//        for (String permission : permissions) {
//            if (ActivityCompat.checkSelfPermission(mActivity, permission)
//                    != PackageManager.PERMISSION_GRANTED) {
//                return false;
//            }
//        }
//        return true;
//    }

    /**
     * Tries to open a {@link CameraDevice}. The result is listened by `mStateCallback`.
     */
    @SuppressWarnings("MissingPermission")
    public void openCamera(int width, int height) {
//        if (!hasPermissionsGranted(VIDEO_PERMISSIONS)) {
//            requestVideoPermissions();
//            return;
//        }
//
//        if (null == mActivity || mActivity.isFinishing()) {
//            return;
//        }
//
//        CameraManager manager = (CameraManager) mActivity.getSystemService(Context.CAMERA_SERVICE);
//        try {
//            Log.d(TAG, "tryAcquire");
//            if (!mCameraOpenCloseLock.tryAcquire(2500, TimeUnit.MILLISECONDS)) {
//                throw new RuntimeException("Time out waiting to lock camera opening.");
//            }
//            String cameraId = manager.getCameraIdList()[0];
//
//            // Choose the sizes for camera preview and video recording
//            CameraCharacteristics characteristics = manager.getCameraCharacteristics(cameraId);
//            StreamConfigurationMap map = characteristics
//                    .get(CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP);
//            mSensorOrientation = characteristics.get(CameraCharacteristics.SENSOR_ORIENTATION);
//            if (map == null) {
//                throw new RuntimeException("Cannot get available preview/video sizes");
//            }
//            mVideoSize = chooseVideoSize(map.getOutputSizes(MediaRecorder.class));
//            mPreviewSize = chooseOptimalSize(map.getOutputSizes(SurfaceTexture.class),
//                    width, height, mVideoSize);
//
//            int orientation = getResources().getConfiguration().orientation;
//            if (orientation == Configuration.ORIENTATION_LANDSCAPE) {
//                mTextureView.setAspectRatio(mPreviewSize.getWidth(), mPreviewSize.getHeight());
//            } else {
//                mTextureView.setAspectRatio(mPreviewSize.getHeight(), mPreviewSize.getWidth());
//            }
//            configureTransform(width, height);
//            mMediaRecorder = new MediaRecorder();
//            manager.openCamera(cameraId, mStateCallback, null);
//        } catch (CameraAccessException e) {
//            Toast.makeText(mActivity, "Cannot access the camera.", Toast.LENGTH_SHORT).show();
//            mActivity.finish();
//        } catch (NullPointerException e) {
//            // Currently an NPE is thrown when the Camera2API is used but not supported on the
//            // device this code runs.
//            ErrorDialog.newInstance(getString(R.string.camera_error))
//                    .show(getChildFragmentManager(), FRAGMENT_DIALOG);
//        } catch (InterruptedException e) {
//            throw new RuntimeException("Interrupted while trying to lock camera opening.");
//        }
    }

    public void closeCamera() {
//        try {
//            mCameraOpenCloseLock.acquire();
//            closePreviewSession();
//            if (null != mCameraDevice) {
//                mCameraDevice.close();
//                mCameraDevice = null;
//            }
//            if (null != mMediaRecorder) {
//                mMediaRecorder.release();
//                mMediaRecorder = null;
//            }
//
//            if (null != mImageReader) {
//                mImageReader.close();
//                mImageReader = null;
//            }
//        } catch (InterruptedException e) {
//            throw new RuntimeException("Interrupted while trying to lock camera closing.");
//        } finally {
//            mCameraOpenCloseLock.release();
//        }
    }

//    /**
//     * Start the camera preview.
//     */
//    private void startPreview() {
//        if (null == mCameraDevice || !mTextureView.isAvailable() || null == mPreviewSize) {
//            return;
//        }
//        try {
//            closePreviewSession();
//
//            mImageReader = ImageReader.newInstance(mPreviewSize.getWidth(),
//                    mPreviewSize.getHeight(), ImageFormat.YUV_420_888, 1);
////                    mPreviewSize.getHeight(), ImageFormat.JPEG, 1);
//
//
//            SurfaceTexture texture = mTextureView.getSurfaceTexture();
//            assert texture != null;
//            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
//            mPreviewBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
//
//            Surface previewSurface = new Surface(texture);
//            mPreviewBuilder.addTarget(previewSurface);
//
//
//            mCameraDevice.createCaptureSession(Collections.singletonList(previewSurface),
//                    new CameraCaptureSession.StateCallback() {
//
//                        @Override
//                        public void onConfigured(@NonNull CameraCaptureSession session) {
//                            mPreviewSession = session;
//                            updateFrame();
//                        }
//
//                        @Override
//                        public void onConfigureFailed(@NonNull CameraCaptureSession session) {
//                            if (null != mActivity) {
//                                Toast.makeText(mActivity, "Failed", Toast.LENGTH_SHORT).show();
//                            }
//                        }
//                    }, mBackgroundHandler);
//        } catch (CameraAccessException e) {
//            e.printStackTrace();
//        }
//    }

//    private void setUpCaptureRequestBuilder(CaptureRequest.Builder builder) {
//        builder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);
//    }

//    /**
//     * Configures the necessary {@link Matrix} transformation to `mTextureView`.
//     * This method should not to be called until the camera preview size is determined in
//     * openCamera, or until the size of `mTextureView` is fixed.
//     *
//     * @param viewWidth  The width of `mTextureView`
//     * @param viewHeight The height of `mTextureView`
//     */
//    private void configureTransform(int viewWidth, int viewHeight) {
//        if (null == mTextureView || null == mPreviewSize || null == mActivity) {
//            return;
//        }
//        int rotation = mActivity.getWindowManager().getDefaultDisplay().getRotation();
//        Matrix matrix = new Matrix();
//        RectF viewRect = new RectF(0, 0, viewWidth, viewHeight);
//        RectF bufferRect = new RectF(0, 0, mPreviewSize.getHeight(), mPreviewSize.getWidth());
//        float centerX = viewRect.centerX();
//        float centerY = viewRect.centerY();
//        if (Surface.ROTATION_90 == rotation || Surface.ROTATION_270 == rotation) {
//            bufferRect.offset(centerX - bufferRect.centerX(), centerY - bufferRect.centerY());
//            matrix.setRectToRect(viewRect, bufferRect, Matrix.ScaleToFit.FILL);
//            float scale = Math.max(
//                    (float) viewHeight / mPreviewSize.getHeight(),
//                    (float) viewWidth / mPreviewSize.getWidth());
//            matrix.postScale(scale, scale, centerX, centerY);
//            matrix.postRotate(90 * (rotation - 2), centerX, centerY);
//        }
//        mTextureView.setTransform(matrix);
//    }

//    private String getVideoFilePath(Context context) {
//        mVideoFolderPath = mContext.getExternalFilesDir(null).getAbsolutePath();
//        mRecordedVideoFileName = System.currentTimeMillis() + ".mp4";
//        final File dir = context.getExternalFilesDir(null);
//        return (dir == null ? "" : (mVideoFolderPath + "/"))
//                + mRecordedVideoFileName;
//    }

//    private void closePreviewSession() {
//        if (mPreviewSession != null) {
//            mPreviewSession.close();
//            mPreviewSession = null;
//        }
//    }

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
            return new AlertDialog.Builder(getActivity())
                    .setMessage(getArguments().getString(ARG_MESSAGE))
                    .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialogInterface, int i) {
                            getActivity().finish();
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
