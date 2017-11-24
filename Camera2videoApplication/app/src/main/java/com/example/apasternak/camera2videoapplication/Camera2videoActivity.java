package com.example.apasternak.camera2videoapplication;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.hardware.camera2.TotalCaptureResult;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.media.MediaRecorder;
import android.os.Build;
import android.os.Environment;
import android.os.Handler;
import android.os.HandlerThread;
import android.support.annotation.NonNull;
import android.support.annotation.RequiresApi;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Size;
import android.util.SparseIntArray;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.List;

@RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
public class Camera2videoActivity extends AppCompatActivity {

    // Constants for app permissions
    private static final int REQUEST_CAMERA_PERMISSION_RESULT = 0;
    private static final int REQUEST_WRITE_EXTERNAL_STORAGE_PERMISSION_RESULT = 1;

    // Texture view for background
    private TextureView mTextureView;

    // Camera device definition
    private CameraDevice mCameraDevice;

    // Background thread and its handler definition
    private HandlerThread mBackgroundHandlerThread;
    private Handler mBackgroundHandler;

    private String mCameraId;

    private Size mPreviewSize;

    private Size mVideoSize;

    private MediaRecorder mMediaRecorder;

    private int mTotalRotation;

    private CaptureRequest.Builder mCaptureRequestBuilder;
    private CameraCaptureSession mPreviewSession;

    private ImageButton mRecordImageButton;
    private boolean mIsRecording = false;

    private File mVideoFolder;
    private String mVideoFileName;

    /// Orientations array
    private static SparseIntArray ORIENTATIONS = new SparseIntArray();
    static {
        ORIENTATIONS.append(Surface.ROTATION_0, 0);
        ORIENTATIONS.append(Surface.ROTATION_90, 90);
        ORIENTATIONS.append(Surface.ROTATION_180, 180);
        ORIENTATIONS.append(Surface.ROTATION_270, 270);
    }

    private TextureView.SurfaceTextureListener mSurfaceTextureListener
        = new TextureView.SurfaceTextureListener() {
        @Override
        public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
            setupCamera(width, height);
            connectCamera();
        }

        @Override
        public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {

        }

        @Override
        public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
            return false;
        }

        @Override
        public void onSurfaceTextureUpdated(SurfaceTexture surface) {

        }
    };

    private CameraDevice.StateCallback mCameraDeviceStateCallback
        = new CameraDevice.StateCallback() {
        @Override
        public void onOpened(CameraDevice camera) {
            mCameraDevice = camera;
            if (mIsRecording) {
                try {
                    createVideoFileName();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                startRecord();
                mMediaRecorder.start();
            } else {
                startPreview();
            }
            startPreview();
            Toast.makeText(getApplicationContext(), "Camera connection established!",
                    Toast.LENGTH_SHORT).show();
        }

        @Override
        public void onDisconnected(CameraDevice camera) {
            camera.close();
            mCameraDevice = null;
        }

        @Override
        public void onError(CameraDevice camera, int error) {
            camera.close();
            mCameraDevice = null;
        }
    };

    private static class CompareSizeByArea implements Comparator<Size> {

        @Override
        public int compare(Size o1, Size o2) {
            return Long.signum((long) o1.getWidth() * o1.getHeight()
                / (long) o2.getWidth() * o2.getHeight());
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera2video);

        createVideoFolder();

        mMediaRecorder = new MediaRecorder();

        // Setting up listeners
        mTextureView = findViewById(R.id.textureView);
        mRecordImageButton = findViewById(R.id.videoOnlineImageButton);
        mRecordImageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mIsRecording) {
                    mIsRecording = false;
                    mRecordImageButton.setImageResource(R.mipmap.ic_videocam);
                    mMediaRecorder.stop();
                    mMediaRecorder.reset();
                    startPreview();
                } else {
                    checkWriteStoragePermission();
                }
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();

        startBackgroundThread();

        if (mTextureView.isAvailable()) {
            setupCamera(mTextureView.getWidth(), mTextureView.getHeight());
            connectCamera();
        } else {
            mTextureView.setSurfaceTextureListener(mSurfaceTextureListener);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions,
        int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (requestCode == REQUEST_CAMERA_PERMISSION_RESULT) {
            if (grantResults[0] != PackageManager.PERMISSION_GRANTED) {
                Toast.makeText(getApplicationContext(),
                        "Application will not run without camera services",
                        Toast.LENGTH_SHORT).show();
            }
        }
        if (requestCode == REQUEST_WRITE_EXTERNAL_STORAGE_PERMISSION_RESULT) {
            if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                mIsRecording = true;
                mRecordImageButton.setImageResource(R.mipmap.ic_videocam_off);

                try {
                    createVideoFileName();
                } catch (IOException e) {
                    e.printStackTrace();
                }

                Toast.makeText(this, "Permission successfully granted!",
                        Toast.LENGTH_SHORT).show();
            } else {
                Toast.makeText(this, "App needs to save video to run",
                        Toast.LENGTH_SHORT).show();
            }
        }
    }

    @Override
    protected void onPause() {
        closeCamera();

        stopBackgroundThread();

        super.onPause();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        View decorView = getWindow().getDecorView();

        if (hasFocus) {
            decorView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                    | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY | View.SYSTEM_UI_FLAG_FULLSCREEN
                    | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_FULLSCREEN
                    | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION);
        }
    }

    private void setupCamera(int width, int height) {
        CameraManager cameraManager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
        try {
            // All available cameras loop
            for (String cameraId : cameraManager.getCameraIdList()) {
                CameraCharacteristics cameraCharacteristics
                        = cameraManager.getCameraCharacteristics(cameraId);

                if (cameraCharacteristics.get(CameraCharacteristics.LENS_FACING)
                        == CameraCharacteristics.LENS_FACING_FRONT) {
                    continue;
                }

                StreamConfigurationMap map = cameraCharacteristics.get(
                    CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP);

                int deviceOrientation = getWindowManager().getDefaultDisplay().getRotation();
                mTotalRotation = sensorToDeviceRotation(cameraCharacteristics,
                    deviceOrientation);
                boolean swapRotation = (mTotalRotation == 90 || mTotalRotation == 270);

                int rotatedWidth = width;
                int rotatedHeight = height;
                if (swapRotation) {
                    rotatedWidth = height;
                    rotatedHeight = width;
                }

                mPreviewSize = chooseOptimalSize(map.getOutputSizes(SurfaceTexture.class),
                    rotatedWidth, rotatedHeight);

                mVideoSize = chooseOptimalSize(map.getOutputSizes(MediaRecorder.class),
                        rotatedWidth, rotatedHeight);

                mCameraId = cameraId;
                return;
            }
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    private void connectCamera() {
        CameraManager cameraManager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
        try {
            /// Checking whether the SDK version is greater than Marshmallow
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                if (ContextCompat.checkSelfPermission(this, android.Manifest.permission.CAMERA)
                    == PackageManager.PERMISSION_GRANTED) {
                    cameraManager.openCamera(mCameraId, mCameraDeviceStateCallback, null);
                } else {
                    if (shouldShowRequestPermissionRationale(android.Manifest.permission.CAMERA)) {
                        Toast.makeText(this, "Video app requires access to camera",
                            Toast.LENGTH_SHORT).show();
                    }
                    requestPermissions(new String[] {Manifest.permission.CAMERA},
                        REQUEST_CAMERA_PERMISSION_RESULT);
                }

            } else {
                cameraManager.openCamera(mCameraId, mCameraDeviceStateCallback, null);
            }
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    final CameraCaptureSession.CaptureCallback mCaptureListener
            = new CameraCaptureSession.CaptureCallback() {

        @Override
        public void onCaptureCompleted(CameraCaptureSession session, CaptureRequest request,
                TotalCaptureResult result) {
            super.onCaptureCompleted(session, request, result);
        }
    };

    private void startRecord() {
        try {
            setupMediaRecorder();

            SurfaceTexture surfaceTexture = mTextureView.getSurfaceTexture();
            surfaceTexture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
            List<Surface> surfaces = new ArrayList<>();

            // Set up Surface for camera preview
            Surface previewSurface = new Surface(surfaceTexture);
            surfaces.add(previewSurface);

            // Set up Surface for MediaRecorder
            Surface recordSurface = mMediaRecorder.getSurface();
            surfaces.add(recordSurface);

            mCaptureRequestBuilder
                    = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_RECORD);
            mCaptureRequestBuilder.addTarget(previewSurface);
            mCaptureRequestBuilder.addTarget(recordSurface);

            mCameraDevice.createCaptureSession(Arrays.asList(previewSurface, recordSurface),
                new CameraCaptureSession.StateCallback() {

                    @Override
                    public void onConfigured(@NonNull CameraCaptureSession session) {
                        mPreviewSession = session;
                        updateFrame();
                    }

                    @Override
                    public void onConfigureFailed(@NonNull CameraCaptureSession session) {

                    }
                }, null);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void setUpCaptureRequestBuilder(CaptureRequest.Builder builder) {
        builder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);
    }

    /**
     * Update the camera preview. {@link #startPreview()} needs to be called in advance.
     */
//    @Override
    public void updateFrame() {
        if (null == mCameraDevice) {
            return;
        }
        try {
            setUpCaptureRequestBuilder(mCaptureRequestBuilder);
            HandlerThread thread = new HandlerThread("CameraPreview");
            thread.start();
            mPreviewSession.setRepeatingRequest(mCaptureRequestBuilder.build(), null,
                    mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    private void startPreview() {
        SurfaceTexture surfaceTexture = mTextureView.getSurfaceTexture();
        surfaceTexture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
        Surface previewSurface = new Surface(surfaceTexture);

        try {
            mCaptureRequestBuilder
                    = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
            mCaptureRequestBuilder.addTarget(previewSurface);

            // Capturing camera image
            mCameraDevice.createCaptureSession(Arrays.asList(previewSurface),
                    new CameraCaptureSession.StateCallback() {
                @Override
                public void onConfigured(@NonNull CameraCaptureSession session) {
                    mPreviewSession = session;
                    updateFrame();
                }

                @Override
                public void onConfigureFailed(@NonNull CameraCaptureSession session) {
                    Toast.makeText(getApplicationContext(), "Unable to set up camera preview",
                            Toast.LENGTH_SHORT).show();
                }
            }, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    private void closeCamera() {
        if (mCameraDevice != null) {
            mCameraDevice.close();
            mCameraDevice = null;
        }
    }

    private void startBackgroundThread() {
        mBackgroundHandlerThread = new HandlerThread("Camera2videoImage");
        mBackgroundHandlerThread.start();
        mBackgroundHandler = new Handler(mBackgroundHandlerThread.getLooper());
    }

    private void stopBackgroundThread() {
        mBackgroundHandlerThread.quitSafely();
        try {
            mBackgroundHandlerThread.join();
            mBackgroundHandlerThread = null;
            mBackgroundHandler = null;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static int sensorToDeviceRotation(CameraCharacteristics cameraCharacteristics,
        int deviceOrientation) {
        int sensorOrientation = cameraCharacteristics.get(CameraCharacteristics.SENSOR_ORIENTATION);
        deviceOrientation = ORIENTATIONS.get(deviceOrientation);

        return (sensorOrientation + deviceOrientation + 360) % 360;
    }

    private static Size chooseOptimalSize(Size[] choices, int width, int height) {
        List<Size> bigEnough = new ArrayList<>();
        for (Size option : choices) {
            if ((option.getHeight() == option.getWidth() * height / width)
                && (option.getWidth() >= width) && (option.getHeight() >= height)) {
                bigEnough.add(option);
            }
        }

        if (bigEnough.size() > 0) {
            return Collections.min(bigEnough, new CompareSizeByArea());
        } else {
            return choices[0];
        }
    }

    private void createVideoFolder() {
        File movieFile
            = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_MOVIES);
        mVideoFolder = new File(movieFile, "camera2videoImage");
        if (!mVideoFolder.exists()) {
            mVideoFolder.mkdirs();
        }
    }

    private File createVideoFileName() throws IOException {
        String timestamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        String prepend = "VIDEO_" + timestamp + "_";
        File videoFile = File.createTempFile(prepend, ".mp4", mVideoFolder);

        mVideoFileName = videoFile.getAbsolutePath();

        return videoFile;
    }

    private void checkWriteStoragePermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (ContextCompat.checkSelfPermission(this,
                Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED) {
                mIsRecording = true;
                mRecordImageButton.setImageResource(R.mipmap.ic_videocam_off);

                try {
                    createVideoFileName();
                } catch (IOException e) {
                    e.printStackTrace();
                }

                startRecord();

                mMediaRecorder.start();
            } else {
                if (shouldShowRequestPermissionRationale(
                    Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                    Toast.makeText(this, "App needs to be able to save videos",
                        Toast.LENGTH_SHORT).show();
                }
                requestPermissions(new String[] {Manifest.permission.WRITE_EXTERNAL_STORAGE},
                    REQUEST_WRITE_EXTERNAL_STORAGE_PERMISSION_RESULT);
            }
        } else {
            mIsRecording = true;
            mRecordImageButton.setImageResource(R.mipmap.ic_videocam_off);

            try {
                createVideoFileName();
            } catch (IOException e) {
                e.printStackTrace();
            }

            startRecord();

            mMediaRecorder.start();
        }
    }

    // Media recorder settings definition
    private void setupMediaRecorder() throws IOException {
        mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.SURFACE);
        mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
        mMediaRecorder.setOutputFile(mVideoFileName);
        mMediaRecorder.setVideoEncodingBitRate(1000000);
        mMediaRecorder.setVideoFrameRate(30);
        mMediaRecorder.setVideoSize(mVideoSize.getWidth(), mVideoSize.getHeight());
        mMediaRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.H264);
        mMediaRecorder.setOrientationHint(mTotalRotation);
        mMediaRecorder.prepare();
    }
}
