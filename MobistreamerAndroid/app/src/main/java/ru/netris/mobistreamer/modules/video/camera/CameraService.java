package ru.netris.mobistreamer.modules.video.camera;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.graphics.Matrix;
import android.graphics.RectF;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.os.Build;
import android.os.Handler;
import android.os.HandlerThread;
import android.support.annotation.NonNull;
import android.util.Log;
import android.util.Size;
import android.util.SparseIntArray;
import android.view.Surface;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;

import ru.netris.mobistreamer.modules.video.activity.AutoFitTextureView;

/**
 * Created by ps on 11.08.17.
 */

public class CameraService {

    private static final String TAG = "CameraService";

    public static Activity activity = null;

    private static final int SENSOR_ORIENTATION_DEFAULT_DEGREES = 90;
    private static final int SENSOR_ORIENTATION_INVERSE_DEGREES = 270;
    private static final SparseIntArray DEFAULT_ORIENTATIONS = new SparseIntArray();
    private static final SparseIntArray INVERSE_ORIENTATIONS = new SparseIntArray();

    public Callback callback = null;

    public interface Callback {
        void onDeviceOpened();
        void onDeviceDisconnected();
        void onRecording(boolean recording);
    }

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

    private AutoFitTextureView mTextureView;
    private CameraDevice mCameraDevice;
    private CameraCaptureSession mPreviewSession;

    private Size mPreviewSize;
    private Size mVideoSize;

//    private MediaRecorder mMediaRecorder;
//    private Semaphore mCameraOpenCloseLock = new Semaphore(1);

    private Integer mSensorOrientation;

    private CaptureRequest.Builder mPreviewBuilder;

    public HandlerThread mBackgroundThread;
    public Handler mBackgroundHandler;

    public boolean isConnected() {
        if(mCameraDevice == null){
            return false;
        }else{
            return true;
        }
    }
//
//    ImageWriter.OnImageReleasedListener mImageWriterAvailable = new ImageWriter.OnImageReleasedListener() {
//        @TargetApi(Build.VERSION_CODES.M)
//        @Override
//        public void onImageReleased(ImageWriter imageWriter) {
//            Image image = imageWriter.dequeueInputImage();
//            BitmapFactory.Options options = new BitmapFactory.Options();
//            ByteBuffer buffer = image.getPlanes()[0].getBuffer();
//            byte[] bytes = new byte[buffer.capacity()];
//            buffer.get(bytes);
//            Bitmap bitmapImage = BitmapFactory.decodeByteArray(bytes, 0, bytes.length, options);
//
//            if(null != bitmapImage) {
//                Canvas canvas = new Canvas(bitmapImage);
//                Paint paint = new Paint();
//                paint.setColor(Color.BLACK);
//                paint.setTextSize(20);
//                canvas.drawText("TEST MOBISTREAM", 10, 10, paint);
//
//                Log.d(TAG, "ImageWriter w:" + image.getWidth() + " h:" + image.getHeight());
//            }
//
//            image.close();
//
//        }
//    };
//
//    ImageReader.OnImageAvailableListener mImageAvailable = new ImageReader.OnImageAvailableListener() {
//        @Override
//        public void onImageAvailable(ImageReader reader) {
//            Image image = reader.acquireLatestImage();
//            BitmapFactory.Options options = new BitmapFactory.Options();
//            ByteBuffer buffer = image.getPlanes()[0].getBuffer();
//            byte[] bytes = new byte[buffer.capacity()];
//            buffer.get(bytes);
//            Bitmap bitmapImage = BitmapFactory.decodeByteArray(bytes, 0, bytes.length, options);
//
//
//            if(null != bitmapImage) {
//                Canvas canvas = new Canvas(bitmapImage);
//                Paint paint = new Paint();
//                paint.setColor(Color.BLACK);
//                paint.setTextSize(20);
//                canvas.drawText("TEST MOBISTREAM", 10, 10, paint);
//
//                Log.d(TAG, "ImageReader w:" + image.getWidth() + " h:" + image.getHeight());
//            }
//
////            try {
////
////            } catch (IOException exception) {
////
////            } finally {
////
////            }
//
//            image.close();
//        }
//    };

    private CameraDevice.StateCallback mStateCallback = new CameraDevice.StateCallback() {

        @Override
        public void onOpened(CameraDevice cameraDevice) {
            mCameraDevice = cameraDevice;
            if (null != mTextureView) {
                configureTransform(mTextureView.getWidth(), mTextureView.getHeight());
            }
            if(callback != null){
                callback.onDeviceOpened();
            }
            Log.d(TAG, "onOpened cameraDevice");
        }

        @Override
        public void onDisconnected(CameraDevice cameraDevice) {
            cameraDevice.close();
            mCameraDevice = null;
            Log.d(TAG, "onDisconnected cameraDevice");

            if(callback != null){
                callback.onDeviceDisconnected();
            }
//            нужно стопать сервис
        }

        @Override
        public void onError(CameraDevice cameraDevice, int error) {
//            mCameraOpenCloseLock.release();
            cameraDevice.close();
            mCameraDevice = null;
            Log.d(TAG, "onError cameraDevice");
        }
    };

//    public static CameraService newInstance() {
//        return new CameraService();
//    }



    private static Size chooseVideoSize(Size[] choices) {
        for (Size size : choices) {
            if (size.getWidth() == size.getHeight() * 4 / 3 && size.getWidth() <= 1080) {
                return size;
            }
        }
        Log.e(TAG, "Couldn't find any suitable video size");
        return choices[choices.length - 1];
    }

    private static Size chooseOptimalSize(Size[] choices, int width, int height, Size aspectRatio) {
        List<Size> bigEnough = new ArrayList<>();
        int w = aspectRatio.getWidth();
        int h = aspectRatio.getHeight();
        for (Size option : choices) {
            if (option.getHeight() == option.getWidth() * h / w &&
                    option.getWidth() >= width && option.getHeight() >= height) {
                bigEnough.add(option);
            }
        }
        if (bigEnough.size() > 0) {
            return Collections.min(bigEnough, new CompareSizesByArea());
        } else {
            Log.e(TAG, "Couldn't find any suitable preview size");
            return choices[0];
        }
    }

    private void startBackgroundThread() {
        mBackgroundThread = new HandlerThread("CameraBackground");
        mBackgroundThread.start();
        mBackgroundHandler = new Handler(mBackgroundThread.getLooper());
    }

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

    int currentCamera = 0;

//    public ImageReader mImageReader;
//    public ImageWriter mImageWriter;
    public List surfaces = new ArrayList<>();

    @SuppressWarnings("MissingPermission")
    public void openCamera() {
        int width = mVideoSize.getWidth();
        int height = mVideoSize.getHeight();

        if (null == activity || activity.isFinishing()) {
            return;
        }

//        mTextureView = new AutoFitTextureView(activity);
//
//        SurfaceTexture texture = mTextureView.getSurfaceTexture();
//        texture.setDefaultBufferSize(width, height);
//
//        Surface previewSurface = new Surface(texture);
//        surfaces.add(previewSurface);
//        mPreviewBuilder.addTarget(previewSurface);

//        Surface readerSurface = mImageReader.getSurface();
//        surfaces.add(readerSurface);
//        mPreviewBuilder.addTarget(readerSurface);

        CameraManager manager = (CameraManager) activity.getSystemService(Context.CAMERA_SERVICE);
        try {
            if(currentCamera >= manager.getCameraIdList().length) {
                currentCamera = 0;
            }

            String cameraId = manager.getCameraIdList()[currentCamera];

            // Choose the sizes for camera preview and video recording
            CameraCharacteristics characteristics = manager.getCameraCharacteristics(cameraId);
            StreamConfigurationMap map = characteristics.get(CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP);
            mSensorOrientation = characteristics.get(CameraCharacteristics.SENSOR_ORIENTATION);
            if (map == null) {
                throw new RuntimeException("Cannot get available preview/video sizes");
            }


//            mImageReader = ImageReader.newInstance(width, height, ImageFormat.YUV_420_888, 3);
//            mImageReader.setOnImageAvailableListener(mImageAvailable,mBackgroundHandler);


//            mVideoSize = chooseVideoSize(map.getOutputSizes(MediaRecorder.class));
            mPreviewSize = chooseOptimalSize(map.getOutputSizes(SurfaceTexture.class), width, height, mVideoSize);


            int orientation = activity.getResources().getConfiguration().orientation;
//            if (orientation == Configuration.ORIENTATION_LANDSCAPE) {
//                mTextureView.setAspectRatio(mPreviewSize.getWidth(), mPreviewSize.getHeight());
//            } else {
//                mTextureView.setAspectRatio(mPreviewSize.getHeight(), mPreviewSize.getWidth());
//            }
//            configureTransform(width, height);
//            mMediaRecorder = new MediaRecorder();
            manager.openCamera(cameraId, mStateCallback, null);
        } catch (CameraAccessException e) {
            Toast.makeText(activity, "Cannot access the camera.", Toast.LENGTH_SHORT).show();
            activity.finish();
        } catch (NullPointerException e) {
            e.printStackTrace();
        }
    }

    @TargetApi(Build.VERSION_CODES.M)
    public void startPreview() {
        Log.d(TAG, "startPreview()");
        if (null == mTextureView || null == mCameraDevice || !mTextureView.isAvailable() || null == mPreviewSize) {
            return;
        }
        try {
            closePreviewSession();
            SurfaceTexture texture = mTextureView.getSurfaceTexture();
            assert texture != null;
            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());

            mPreviewBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);

            Surface previewSurface = new Surface(texture);
            surfaces.add(previewSurface);
            mPreviewBuilder.addTarget(previewSurface);


//            Surface readerSurface = mImageReader.getSurface();
//            surfaces.add(readerSurface);
//            mPreviewBuilder.addTarget(readerSurface);

//            mImageWriter = ImageWriter.newInstance(previewSurface, 30);
//            mImageWriter.setOnImageReleasedListener(mImageWriterAvailable, mBackgroundHandler);

//            InputConfiguration conf = new InputConfiguration(mPreviewSize.getWidth(), mPreviewSize.getHeight(), ImageFormat.YUV_444_888); // ImageFormat.NV21  YUV_420_888
//
//            mCameraDevice.createReprocessableCaptureSession(conf, surfaces, new CameraCaptureSession.StateCallback() {
//                @Override
//                public void onConfigured(@NonNull CameraCaptureSession cameraCaptureSession) {
//                    mPreviewSession = cameraCaptureSession;
//                    updatePreview();
//                }
//
//                @Override
//                public void onConfigureFailed(@NonNull CameraCaptureSession cameraCaptureSession) {
//                    if (null != activity) {
//                        Toast.makeText(activity, "Failed", Toast.LENGTH_SHORT).show();
//                    }
//                }
//            }, mBackgroundHandler);

            mCameraDevice.createCaptureSession(Collections.singletonList(previewSurface), new CameraCaptureSession.StateCallback() { //Collections.singletonList(previewSurface)  surfaces

                @Override
                public void onConfigured(@NonNull CameraCaptureSession session) {
                    mPreviewSession = session;
                    updatePreview();
                }

                @Override
                public void onConfigureFailed(@NonNull CameraCaptureSession session) {
                    if (null != activity) {
                        Toast.makeText(activity, "Failed", Toast.LENGTH_SHORT).show();
                    }
                }
            }, mBackgroundHandler);


        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    public boolean isTorchOn() {
        if (CameraMetadata.FLASH_MODE_TORCH == mPreviewBuilder.get(CaptureRequest.FLASH_MODE) ) {
            return true;
        }else {
            return false;
        }
    }

    public void turnOnFlashLight() {
        try {
            mPreviewBuilder.set(CaptureRequest.FLASH_MODE, CameraMetadata.FLASH_MODE_TORCH);
            mPreviewSession.setRepeatingRequest(mPreviewBuilder.build(), null, null);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void turnOffFlashLight() {
        try {
            mPreviewBuilder.set(CaptureRequest.FLASH_MODE, CameraMetadata.FLASH_MODE_OFF);
            mPreviewSession.setRepeatingRequest(mPreviewBuilder.build(), null, null);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void closeCamera() {
        closePreviewSession();
        if (null != mCameraDevice) {
            mCameraDevice.close();
            mCameraDevice = null;
        }
//      if (null != mMediaRecorder) {
//          mMediaRecorder.release();
//          mMediaRecorder = null;
//      }
    }

    public boolean isVideoSizeSupported(Size size) {

        return false;
    }

    public AutoFitTextureView getPreview() {
        return mTextureView;
    }

    public void setPreview(AutoFitTextureView textureView) {
        mTextureView = textureView;
    }

    public void removePreview() {
        stopPreview();
        mTextureView = null;
    }

    public void setVideoSize(Size size) {
        mVideoSize = size;
    }

    public Size getVideoSize() {
        return mVideoSize;
    }

    public void setPreviewSize(Size size) {
        mPreviewSize = size;
    }

    public int getCamerasCount() {
        try {
            if (null == activity || activity.isFinishing()) {
                return 0;
            }
            CameraManager manager = (CameraManager) activity.getSystemService(Context.CAMERA_SERVICE);
            String[] cameraList = manager.getCameraIdList();
//            for (String cameraID : cameraList) {
//                Log.i(TAG, "cameraID: "+cameraID);
//            }
            return cameraList.length;
        } catch (CameraAccessException e) {
            Log.e(TAG,e.getMessage());
            e.printStackTrace();
        }
        return 0;
    }

    public void startRecord() {
        activity.runOnUiThread(new Runnable() {
            public void run() {
                if(null!=callback) {
                    callback.onRecording(true);
                }
            }
        });
    }

    public void stopRecord() {
        activity.runOnUiThread(new Runnable() {
            public void run() {
                if(null!=callback) {
                    callback.onRecording(false);
                }
            }
        });
    }

    public Size getPreviewSize() {
        return mPreviewSize;
    }

    public void switchCamera() {
        if(currentCamera == 0) {
            currentCamera = 1;
        }else{
            currentCamera = 0;
        }
        stopPreview();
        closeCamera();
        openCamera();
    }

    public void torch(boolean isOn) {

    }

    public boolean isTorch() {
        return true;
    }

    public boolean isSupportTorch() {

        return false;
    }

    public boolean isSupportSecondCamera() {

        return false;
    }

    public List<Size> supportedSizes() {
        List<Size> list = new LinkedList<Size>();
        list.add(new Size(320,240));
        list.add(new Size(640,480));
        list.add(new Size(1280,720));
        return list;
    }

    public void stopPreview() {
        closePreviewSession();
    }

    public void updatePreview() {
        if (null == mCameraDevice) {
            return;
        }
        try {
            setUpCaptureRequestBuilder(mPreviewBuilder);
            HandlerThread thread = new HandlerThread("CameraPreview");
            thread.start();
            if(mPreviewSession != null) {
                mPreviewSession.setRepeatingRequest(mPreviewBuilder.build(), null, mBackgroundHandler);
            }
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    public void setUpCaptureRequestBuilder(CaptureRequest.Builder builder) {
        if (builder != null) {
            builder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);
        }
    }

    public void configureTransform(int viewWidth, int viewHeight) {
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
            float scale = Math.max((float) viewHeight / mPreviewSize.getHeight(), (float) viewWidth / mPreviewSize.getWidth());
            matrix.postScale(scale, scale, centerX, centerY);
            matrix.postRotate(90 * (rotation - 2), centerX, centerY);
        }
        mTextureView.setTransform(matrix);
    }

    public boolean isPreviewed() {
        if (mPreviewSession != null) {
            return true;
        }else{
            return false;
        }
    }

    public void closePreviewSession() {
        if (mPreviewSession != null) {
            mPreviewSession.close();
            mPreviewSession = null;
        }
    }

    static class CompareSizesByArea implements Comparator<Size> {

        @Override
        public int compare(Size lhs, Size rhs) {
            return Long.signum((long) lhs.getWidth() * lhs.getHeight() -
                    (long) rhs.getWidth() * rhs.getHeight());
        }
    }
}



/*

    private TextureView.SurfaceTextureListener mSurfaceTextureListener = new TextureView.SurfaceTextureListener() {

        @Override
        public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture, int width, int height) {
            openCamera(width, height);
        }

        @Override
        public void onSurfaceTextureSizeChanged(SurfaceTexture surfaceTexture, int width, int height) {
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

 */


/*
    public void onResume() {
        startBackgroundThread();
        if (mTextureView.isAvailable()) {
            openCamera(mTextureView.getWidth(), mTextureView.getHeight());
        } else {
            mTextureView.setSurfaceTextureListener(mSurfaceTextureListener);
        }
    }

    public void onPause() {
        closeCamera();
        stopBackgroundThread();
    }
*/

/*
    private void setUpMediaRecorder() throws IOException {
        if (null == activity) {
            return;
        }
        mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
        mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.SURFACE);
        mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
        if (mNextVideoAbsolutePath == null || mNextVideoAbsolutePath.isEmpty()) {
            mNextVideoAbsolutePath = getVideoFilePath(activity);
        }
        mMediaRecorder.setOutputFile(mNextVideoAbsolutePath);
        mMediaRecorder.setVideoEncodingBitRate(10000000);
        mMediaRecorder.setVideoFrameRate(30);
        mMediaRecorder.setVideoSize(mVideoSize.getWidth(), mVideoSize.getHeight());
        mMediaRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.H264);
        mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AAC);
        int rotation = activity.getWindowManager().getDefaultDisplay().getRotation();
        switch (mSensorOrientation) {
            case SENSOR_ORIENTATION_DEFAULT_DEGREES:
                mMediaRecorder.setOrientationHint(DEFAULT_ORIENTATIONS.get(rotation));
                break;
            case SENSOR_ORIENTATION_INVERSE_DEGREES:
                mMediaRecorder.setOrientationHint(INVERSE_ORIENTATIONS.get(rotation));
                break;
        }
        mMediaRecorder.prepare();
    }

*/

/*
    private String getVideoFilePath(Context context) {
        final File dir = context.getExternalFilesDir(null);
        return (dir == null ? "" : (dir.getAbsolutePath() + "/"))
                + System.currentTimeMillis() + ".mp4";
    }
*/

/*
    private void startRecordingVideo() {
        if (null == mCameraDevice || !mTextureView.isAvailable() || null == mPreviewSize) {
            return;
        }
        try {
            closePreviewSession();
            setUpMediaRecorder();
            SurfaceTexture texture = mTextureView.getSurfaceTexture();
            assert texture != null;
            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
            mPreviewBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_RECORD);
            List<Surface> surfaces = new ArrayList<>();

            // Set up Surface for the camera preview
            Surface previewSurface = new Surface(texture);
            surfaces.add(previewSurface);
            mPreviewBuilder.addTarget(previewSurface);

            // Set up Surface for the MediaRecorder
            Surface recorderSurface = mMediaRecorder.getSurface();
            surfaces.add(recorderSurface);
            mPreviewBuilder.addTarget(recorderSurface);

            // Start a capture session
            // Once the session starts, we can update the UI and start recording
            mCameraDevice.createCaptureSession(surfaces, new CameraCaptureSession.StateCallback() {

                @Override
                public void onConfigured(@NonNull CameraCaptureSession cameraCaptureSession) {
                    mPreviewSession = cameraCaptureSession;
                    updatePreview();
                    activity.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            // UI
//                            mButtonVideo.setText(R.string.stop);
                            mIsRecordingVideo = true;

                            // Start recording
                            mMediaRecorder.start();
                        }
                    });
                }

                @Override
                public void onConfigureFailed(@NonNull CameraCaptureSession cameraCaptureSession) {
                    if (null != activity) {
                        Toast.makeText(activity, "Failed", Toast.LENGTH_SHORT).show();
                    }
                }
            }, mBackgroundHandler);
        } catch (CameraAccessException | IOException e) {
            e.printStackTrace();
        }
    }
*/


/*
    private void stopRecordingVideo() {
        // UI
//        mButtonVideo.setText(R.string.record);
        // Stop recording
        mMediaRecorder.stop();
        mMediaRecorder.reset();

        if (null != activity) {
            Toast.makeText(activity, "Video saved: " + mNextVideoAbsolutePath, Toast.LENGTH_SHORT).show();
            Log.d(TAG, "Video saved: " + mNextVideoAbsolutePath);
        }
        mNextVideoAbsolutePath = null;
//        startPreview();
    }
*/