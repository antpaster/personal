/*
 * Copyright 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.example.apasternak.mediacodecvideo;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.media.ImageReader;
import android.media.MediaCodec;
import android.net.Uri;
import android.os.Handler;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.util.Size;
import android.util.SparseIntArray;
import android.view.Gravity;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.widget.VideoView;

import java.io.ByteArrayInputStream;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import static android.graphics.ImageFormat.JPEG;

public class MainActivity extends AppCompatActivity {

    CameraToMpegTest mCameraToMpegTest = new CameraToMpegTest();

    /** App and UI dealing members */
    static final String TAG = "MediaCodecVideo";
    Button mCaptureButton;
    TextureView mTextureView;
    static final SparseIntArray ORIENTATIONS = new SparseIntArray();
    static {
        ORIENTATIONS.append(Surface.ROTATION_0, 0);
        ORIENTATIONS.append(Surface.ROTATION_90, 90);
        ORIENTATIONS.append(Surface.ROTATION_180, 180);
        ORIENTATIONS.append(Surface.ROTATION_270, 270);
    }

    /** Camera dealing members */
    CameraManager mCameraManagerSaved;
    static final int REQUEST_CAMERA_PERMISSION = 200;
    CameraDevice mCameraDevice;
    String mCameraId;
    Size mPreviewSize;
    ImageReader mImageReader;
    CaptureRequest.Builder mPreviewRequestBuilder;
    CameraCaptureSession mCaptureSession;

    /** Thread agenda */
    Handler mBackgroundHandler;


    /** Video stuff */
    MediaCodec.BufferInfo mBufferInfo = new MediaCodec.BufferInfo(); /**!< holds the info about the
     current buffer */
    MediaCodec mEncoder;
    volatile boolean mRunning;
    final long mTimeoutUsec = 10000l; /**!< lock time while waiting the available buffer */
    static final int MAX_BUFFERS = 100;
    static final int REQUEST_VIDEO_CAPTURE = 300;
    VideoView mDisplayRecordedVideo;
    Uri mUri;
    String mPathToStoredVideo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

//        if (savedInstanceState != null) {
//            byte[] savedByteArray = savedInstanceState.getByteArray(mCameraId);
//            mCameraManagerSaved = (CameraManager) savedByteArray;
//        }

        setContentView(R.layout.activity_main);

//        final Activity currActivity = this.getParent();

        mTextureView = findViewById(R.id.texture);
        assert mTextureView != null;
        mTextureView.setSurfaceTextureListener(mTextureListener);

        mCaptureButton = findViewById(R.id.capture);
//        if( !getApplicationContext())
        mCaptureButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(getApplicationContext(), "Pressed!", Toast.LENGTH_SHORT).show();

                Intent videoCaptureIntent = new Intent(MediaStore.ACTION_VIDEO_CAPTURE);

                if (videoCaptureIntent.resolveActivity(getPackageManager()) != null) {
                    startActivityForResult(videoCaptureIntent, REQUEST_VIDEO_CAPTURE);
                }

//                // Captures the video here
//                try {
////                    mCameraToMpegTest.testEncodeCameraToMp4();
//
//                } catch (Throwable throwable) {
//                    throwable.printStackTrace();
//                }
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (resultCode == Activity.RESULT_OK && requestCode == REQUEST_VIDEO_CAPTURE) {
            mUri = data.getData();
//
//            if (EasyPermissions.hasPermissions(MainActivity.this,
//                    android.Manifest.permission.READ_EXTERNAL_STORAGE)) {
                mDisplayRecordedVideo.setVideoURI(mUri);
                mDisplayRecordedVideo.start();

                mPathToStoredVideo = getRealPathFromURIPath(mUri, MainActivity.this);
                Log.d(TAG, "Recorded Video Path " + mPathToStoredVideo);

//                /// Store the video to your server
//                uploadVideoToServer(mPathToStoredVideo);
//            } else {
//                EasyPermissions.requestPermissions(VideoToServerActivity.this,
//                        getString(R.string.read_file), READ_REQUEST_CODE,
//                        Manifest.permission.READ_EXTERNAL_STORAGE);
//            }
        }
    }

    String getRealPathFromURIPath(Uri contentURI, Activity activity) {
        Cursor cursor = activity.getContentResolver().query(contentURI, null, null, null, null);
        if (cursor == null) {
            return contentURI.getPath();
        } else {
            cursor.moveToFirst();
            int idx = cursor.getColumnIndex(MediaStore.Images.ImageColumns.DATA);
            return cursor.getString(idx);
        }
    }

    /** Preview texture handling */
    TextureView.SurfaceTextureListener mTextureListener = new TextureView.SurfaceTextureListener() {

        @Override
        public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
            Toast toast = new Toast(getApplicationContext());
            toast.setGravity(Gravity.TOP, 0, 50);
            toast.makeText(getApplicationContext(), "TextureView is available!",
                    Toast.LENGTH_SHORT).show();

            openCamera();
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

    /** Camera state changing handling */
    final CameraDevice.StateCallback mStateCallback = new CameraDevice.StateCallback() {
        @Override
        public void onOpened(@NonNull CameraDevice camera) {
            // Camera is opened
            Log.e(TAG, "onOpened");
            mCameraDevice = camera;
            createCameraPreview();
        }

        @Override
        public void onDisconnected(@NonNull CameraDevice camera) {
            camera.close();
//            mCameraDevice = null;
        }

        @Override
        public void onError(@NonNull CameraDevice camera, int error) {
            camera.close();
            mCameraDevice = null;
        }
    };

    /** Create preview */
    void createCameraPreview() {
        try {
            SurfaceTexture texture = mTextureView.getSurfaceTexture();
            assert texture != null;

            // Getting an instance of the ImageReader. Here was a NullPointerException
            mImageReader = ImageReader.newInstance(640, 480, JPEG, 1);

            // We configure the size of default buffer to be the size of camera preview we want.
            texture.setDefaultBufferSize(mImageReader.getWidth(), mImageReader.getHeight());

            // This is the output Surface we need to start preview.
            Surface surface = new Surface(texture);

            // We set up a CaptureRequest.Builder with the output Surface.
            mPreviewRequestBuilder
                    = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
            mPreviewRequestBuilder.addTarget(surface);

            // Create a CameraCaptureSession for camera preview.
            mCameraDevice.createCaptureSession(Arrays.asList(surface),
                    new CameraCaptureSession.StateCallback() {

                        @Override
                        public void onConfigured(@NonNull CameraCaptureSession
                                cameraCaptureSession) {
                            // The camera is already closed
                            if (null == mCameraDevice) {
                                return;
                            }

                            // When the session is ready, we start displaying the preview.
                            mCaptureSession = cameraCaptureSession;
                            updatePreview();
                        }

                        @Override
                        public void onConfigureFailed(
                                @NonNull CameraCaptureSession cameraCaptureSession) {
                            Toast.makeText(getApplicationContext(), "Configuration change",
                                    Toast.LENGTH_SHORT).show();
                        }
                    }, null);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    /** Updating preview */
    protected void updatePreview() {
        if (null == mCameraDevice) {
            Log.e(TAG, "updatePreview error, return");
        }
        mPreviewRequestBuilder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);
        try {
            mCaptureSession.setRepeatingRequest(mPreviewRequestBuilder.build(), null,
                    mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }

    /** Starting working with the camera */
    void openCamera() {
        CameraManager manager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
        Log.e(TAG, "is camera open");
        try {

            // Default preview sizes
            int width = /*mImageReader.getWidth()*/640;
            int height = /*mImageReader.getHeight()*/480;

            /// All available cameras loop
            for (String cameraId : manager.getCameraIdList()) {
                CameraCharacteristics characteristics
                        = manager.getCameraCharacteristics(cameraId);

                if (characteristics.get(CameraCharacteristics.LENS_FACING)
                        == CameraCharacteristics.LENS_FACING_FRONT) {
                    continue;
                }

                StreamConfigurationMap map
                        = characteristics.get(CameraCharacteristics.
                        SCALER_STREAM_CONFIGURATION_MAP);
                assert map != null;

                int deviceOrientation = getWindowManager().getDefaultDisplay().getRotation();

                if (deviceOrientation == Surface.ROTATION_0) {
                    mPreviewSize = new Size(height, width);
                    sensorToDeviceRotation(characteristics, 0);
                } else if (deviceOrientation == Surface.ROTATION_90) {
                    mPreviewSize = new Size(width, height);
                } else if (deviceOrientation == Surface.ROTATION_180) {
                    mPreviewSize = new Size(height, width);
                } else {
                    mPreviewSize = new Size(width, height);
                    sensorToDeviceRotation(characteristics, 270);
                }

                mCameraId = cameraId;

                // Add permission for camera and let user grant the permission
                if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA)
                        != PackageManager.PERMISSION_GRANTED
                        && ActivityCompat.checkSelfPermission(this,
                        Manifest.permission.WRITE_EXTERNAL_STORAGE)
                        != PackageManager.PERMISSION_GRANTED) {

                    ActivityCompat.requestPermissions(this, new
                            String[]{Manifest.permission.CAMERA,
                            Manifest.permission.WRITE_EXTERNAL_STORAGE}, REQUEST_CAMERA_PERMISSION);
                    return;
                }
                manager.openCamera(mCameraId, mStateCallback, null);

            }
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
        Log.e(TAG, "openCamera X");
    }

    /** Rotate camera sensor according to the device rotation */
    static int sensorToDeviceRotation(CameraCharacteristics cameraCharacteristics,
                int deviceOrientation) {
        int sensorOrientation = cameraCharacteristics.get(CameraCharacteristics.SENSOR_ORIENTATION);
        deviceOrientation = ORIENTATIONS.get(deviceOrientation);

        return (sensorOrientation + deviceOrientation + 360) % 360;
    }

    static class CompareSizeByArea implements Comparator<Size> {

        @Override
        public int compare(Size o1, Size o2) {
            return Long.signum((long) o1.getWidth() * o1.getHeight()
                    / (long) o2.getWidth() * o2.getHeight());
        }
    }

    static Size chooseOptimalSize(Size[] choices, int width, int height) {
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

    /**! Encoding video */
    void encode() {
        if (!mRunning) {
            mEncoder.signalEndOfInputStream(); // сообщить кодеку о конце потока данных
        }

        // получаем массив буферов кодека
        ByteBuffer[] outputBuffers = new ByteBuffer[MAX_BUFFERS];

        for (;;) {
            // статус является кодом возврата или же, если 0 и позитивное число, индексом буфера в массиве
            int status = mEncoder.dequeueOutputBuffer(mBufferInfo, mTimeoutUsec);
            outputBuffers[status] = mEncoder.getOutputBuffer(status);

            if (status == MediaCodec.INFO_TRY_AGAIN_LATER) {
                // нет доступного буфера, пробуем позже
                if (!mRunning) break; // выходим если поток закончен
            } else if (status == MediaCodec.INFO_OUTPUT_BUFFERS_CHANGED) {
                // на случай если кодек меняет буфера
                outputBuffers[status] = mEncoder.getOutputBuffer(status);
            } else if (status < 0) {
                // просто ничего не делаем
            } else {
                // статус является индексом буфера кодированных данных
                ByteBuffer data = outputBuffers[status];
                data.position(mBufferInfo.offset);
                data.limit(mBufferInfo.offset + mBufferInfo.size);
                // ограничиваем кодированные данные
                // делаем что-то с данными...
                mEncoder.releaseOutputBuffer(status, false);
                if ((mBufferInfo.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM)
                        == MediaCodec.BUFFER_FLAG_END_OF_STREAM) {
                    break;
                }
            }
        }
    }

}
