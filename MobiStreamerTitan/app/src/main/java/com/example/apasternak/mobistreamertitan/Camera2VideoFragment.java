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
import android.media.MediaCodecInfo;
import android.media.MediaFormat;
import android.media.MediaMuxer;
import android.media.MediaRecorder;
import android.opengl.EGL14;
import android.opengl.EGLConfig;
import android.opengl.EGLContext;
import android.opengl.EGLDisplay;
import android.opengl.EGLExt;
import android.opengl.EGLSurface;
import android.opengl.GLES10;
import android.opengl.GLES11Ext;
import android.opengl.GLES20;
import android.opengl.GLES30;
import android.opengl.GLUtils;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Parcel;
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
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
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

//    private static final String TAG = "CameraRecordingStream";
    private static final boolean VERBOSE = Log.isLoggable(TAG, Log.VERBOSE);
    private static final int STREAM_STATE_IDLE = 0;
    private static final int STREAM_STATE_CONFIGURED = 1;
    private static final int STREAM_STATE_RECORDING = 2;
    private static final String MIME_TYPE = "video/avc"; // H.264 AVC encoding
    private static final int FRAME_RATE = 30; // 30fps
    private static final int IFRAME_INTERVAL = 1; // 1 seconds between I-frames
    private static final int TIMEOUT_USEC = 10000; // Timeout value 10ms.
    public static final int DURATION_SEC = 10;
    private int mEncBitRate = 10000000;

    public static final String OUTPUT_DIR
            = Environment.getExternalStorageDirectory().getAbsolutePath();

    // Fragment shader that swaps color channels around.
    private static final String SWAPPED_FRAGMENT_SHADER =
            "#extension GL_OES_EGL_image_external : require\n" +
                    "precision mediump float;\n" +
                    "varying vec2 vTextureCoord;\n" +
                    "uniform samplerExternalOES sTexture;\n" +
                    "void main() {\n" +
                    "  gl_FragColor = texture2D(sTexture, vTextureCoord).gbra;\n" +
                    "}\n";

    // Sync object to protect stream state access from multiple threads.
    private final Object mStateLock = new Object();

    private int mStreamState = STREAM_STATE_IDLE;

    private MediaCodec mEncoder;
    private MediaCodec.BufferInfo mBufferInfo;
    private MediaMuxer mMuxer;
    private int mTrackIndex = -1;
    private boolean mMuxerStarted;
    private boolean mUseMediaCodec = true;

//    private volatile boolean mConfigured;
//    private MediaCodec mDecoder;

//    GLES10 mGles10 = new GLES10();
    GLES20 mGles20 = new GLES20();
//    GLES30 mGles30 = new GLES30();
    int[] mTextures = new int[10];
//    float[] mTexMatrix = new float[16];

//    EglCore mEglCore;
//    WindowSurface mDisplaySurface;
//    WindowSurface mEncoderSurface;
//    FullFrameRect mFullFrameBlit;
//    CircularEncoder mCircEncoder;
//    final float[] mTmpMatrix = new float[16];
//    int mFrameNum = 0;
//    boolean mFileSaveInProgress = false;

    private Integer mSensorOrientation;
//    private String mNextVideoFullFileName;
    private CaptureRequest.Builder mPreviewBuilder;
//
//    public Camera2VideoFragment() {
//
//    }

//    public void setRecordingSurface(Surface recordingSurface) {
//        mRecordingSurface = recordingSurface;
//    }

    private CodecInputSurface mRecordingSurface;
    private SurfaceTextureManager mStManager;
    private Size mStreamSize = new Size(-1, -1);

    private HandlerThread mRecordingThread;
    private Handler mRecordingHandler;
    private Thread mBackgroundThread;

    /**
     * Wraps encodeCameraToMpeg().  This is necessary because SurfaceTexture will try to use
     * the looper in the current thread if one exists, and the CTS tests create one on the
     * test thread.
     *
     * The wrapper propagates exceptions thrown by the worker thread back to the caller.
     */
    private static class CameraToMpegWrapper implements Runnable {
        private Throwable mThrowable;
        private Camera2VideoFragment mTest;

        private CameraToMpegWrapper(Camera2VideoFragment test) {
            mTest = test;
        }

        @Override
        public void run() {
            try {
                mTest.encodeCameraToMpeg();
            } catch (Throwable th) {
                mThrowable = th;
            }
        }

        /** Entry point. */
        public static void runTest(Camera2VideoFragment obj) throws Throwable {
            CameraToMpegWrapper wrapper = new CameraToMpegWrapper(obj);
            Thread th = new Thread(wrapper, "codec test");
            th.start();
            th.join();
            if (wrapper.mThrowable != null) {
                throw wrapper.mThrowable;
            }
        }
    }

    /**
     * Holds state associated with a Surface used for MediaCodec encoder input.
     * <p>
     * The constructor takes a Surface obtained from MediaCodec.createInputSurface(), and uses
     * that to create an EGL window surface.  Calls to eglSwapBuffers() cause a frame of data to
     * be sent to the video encoder.
     * <p>
     * This object owns the Surface -- releasing this will release the Surface too.
     */
    private static class CodecInputSurface {
        private static final int EGL_RECORDABLE_ANDROID = 0x3142;

        private EGLDisplay mEGLDisplay = EGL14.EGL_NO_DISPLAY;
        private EGLContext mEGLContext = EGL14.EGL_NO_CONTEXT;
        private EGLSurface mEGLSurface = EGL14.EGL_NO_SURFACE;

        private Surface mSurface;

        /**
         * Creates a CodecInputSurface from a Surface.
         */
        public CodecInputSurface(Surface surface) {
            if (surface == null) {
                throw new NullPointerException();
            }
            mSurface = surface;

            eglSetup();
        }

        /**
         * Prepares EGL.  We want a GLES 2.0 context and a surface that supports recording.
         */
        private void eglSetup() {
            mEGLDisplay = EGL14.eglGetDisplay(EGL14.EGL_DEFAULT_DISPLAY);
            if (mEGLDisplay == EGL14.EGL_NO_DISPLAY) {
                throw new RuntimeException("unable to get EGL14 display");
            }
            int[] version = new int[2];
            if (!EGL14.eglInitialize(mEGLDisplay, version, 0, version, 1)) {
                throw new RuntimeException("unable to initialize EGL14");
            }

            // Configure EGL for recording and OpenGL ES 2.0.
            int[] attribList = {
                    EGL14.EGL_RED_SIZE, 8,
                    EGL14.EGL_GREEN_SIZE, 8,
                    EGL14.EGL_BLUE_SIZE, 8,
                    EGL14.EGL_ALPHA_SIZE, 8,
                    EGL14.EGL_RENDERABLE_TYPE, EGL14.EGL_OPENGL_ES2_BIT,
                    EGL_RECORDABLE_ANDROID, 1,
                    EGL14.EGL_NONE
            };
            EGLConfig[] configs = new EGLConfig[1];
            int[] numConfigs = new int[1];
            EGL14.eglChooseConfig(mEGLDisplay, attribList, 0, configs, 0, configs.length,
                    numConfigs, 0);
            checkEglError("eglCreateContext RGB888+recordable ES2");

            // Configure context for OpenGL ES 2.0.
            int[] attrib_list = {
                    EGL14.EGL_CONTEXT_CLIENT_VERSION, 2,
                    EGL14.EGL_NONE
            };
            mEGLContext = EGL14.eglCreateContext(mEGLDisplay, configs[0], EGL14.EGL_NO_CONTEXT,
                    attrib_list, 0);
            checkEglError("eglCreateContext");

            // Create a window surface, and attach it to the Surface we received.
            int[] surfaceAttribs = {
                    EGL14.EGL_NONE
            };
            mEGLSurface = EGL14.eglCreateWindowSurface(mEGLDisplay, configs[0], mSurface,
                    surfaceAttribs, 0);
            checkEglError("eglCreateWindowSurface");
        }

        /**
         * Discards all resources held by this class, notably the EGL context.  Also releases the
         * Surface that was passed to our constructor.
         */
        public void release() {
            if (mEGLDisplay != EGL14.EGL_NO_DISPLAY) {
                EGL14.eglMakeCurrent(mEGLDisplay, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_SURFACE,
                        EGL14.EGL_NO_CONTEXT);
                EGL14.eglDestroySurface(mEGLDisplay, mEGLSurface);
                EGL14.eglDestroyContext(mEGLDisplay, mEGLContext);
                EGL14.eglReleaseThread();
                EGL14.eglTerminate(mEGLDisplay);
            }
            mSurface.release();

            mEGLDisplay = EGL14.EGL_NO_DISPLAY;
            mEGLContext = EGL14.EGL_NO_CONTEXT;
            mEGLSurface = EGL14.EGL_NO_SURFACE;

            mSurface = null;
        }

        /**
         * Makes our EGL context and surface current.
         */
        public void makeCurrent() {
            EGL14.eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext);
            checkEglError("eglMakeCurrent");
        }

        /**
         * Calls eglSwapBuffers.  Use this to "publish" the current frame.
         */
        public boolean swapBuffers() {
            boolean result = EGL14.eglSwapBuffers(mEGLDisplay, mEGLSurface);
            checkEglError("eglSwapBuffers");
            return result;
        }

        /**
         * Sends the presentation time stamp to EGL.  Time is expressed in nanoseconds.
         */
        public void setPresentationTime(long nsecs) {
            EGLExt.eglPresentationTimeANDROID(mEGLDisplay, mEGLSurface, nsecs);
            checkEglError("eglPresentationTimeANDROID");
        }

        /**
         * Checks for EGL errors.  Throws an exception if one is found.
         */
        private void checkEglError(String msg) {
            int error;
            if ((error = EGL14.eglGetError()) != EGL14.EGL_SUCCESS) {
                throw new RuntimeException(msg + ": EGL error: 0x" + Integer.toHexString(error));
            }
        }
    }

    /**
     * Manages a SurfaceTexture.  Creates SurfaceTexture and TextureRender objects, and provides
     * functions that wait for frames and render them to the current EGL surface.
     * <p>
     * The SurfaceTexture can be passed to Camera.setPreviewTexture() to receive camera output.
     */
    private static class SurfaceTextureManager
            implements SurfaceTexture.OnFrameAvailableListener {
        private SurfaceTexture mSurfaceTexture;
        private STextureRender mTextureRender;

        private Object mFrameSyncObject = new Object();     // guards mFrameAvailable
        private boolean mFrameAvailable;

        /**
         * Creates instances of TextureRender and SurfaceTexture.
         */
        public SurfaceTextureManager() {
            mTextureRender = new STextureRender();
            mTextureRender.surfaceCreated();

            if (VERBOSE) Log.d(TAG, "textureID=" + mTextureRender.getTextureId());
            mSurfaceTexture = new SurfaceTexture(mTextureRender.getTextureId());

            // This doesn't work if this object is created on the thread that CTS started for
            // these test cases.
            //
            // The CTS-created thread has a Looper, and the SurfaceTexture constructor will
            // create a Handler that uses it.  The "frame available" message is delivered
            // there, but since we're not a Looper-based thread we'll never see it.  For
            // this to do anything useful, OutputSurface must be created on a thread without
            // a Looper, so that SurfaceTexture uses the main application Looper instead.
            //
            // Java language note: passing "this" out of a constructor is generally unwise,
            // but we should be able to get away with it here.
            mSurfaceTexture.setOnFrameAvailableListener(this);
        }

        public void release() {
            // this causes a bunch of warnings that appear harmless but might confuse someone:
            //  W BufferQueue: [unnamed-3997-2] cancelBuffer: BufferQueue has been abandoned!
            //mSurfaceTexture.release();

            mTextureRender = null;
            mSurfaceTexture = null;
        }

        /**
         * Returns the SurfaceTexture.
         */
        public SurfaceTexture getSurfaceTexture() {
            return mSurfaceTexture;
        }

        /**
         * Replaces the fragment shader.
         */
        public void changeFragmentShader(String fragmentShader) {
            mTextureRender.changeFragmentShader(fragmentShader);
        }

        /**
         * Latches the next buffer into the texture.  Must be called from the thread that created
         * the OutputSurface object.
         */
        public void awaitNewImage() {
            final int TIMEOUT_MS = 2500;

            synchronized (mFrameSyncObject) {
                while (!mFrameAvailable) {
                    try {
                        // Wait for onFrameAvailable() to signal us.  Use a timeout to avoid
                        // stalling the test if it doesn't arrive.
                        mFrameSyncObject.wait(TIMEOUT_MS);
                        if (!mFrameAvailable) {
                            // TODO: if "spurious wakeup", continue while loop
                            throw new RuntimeException("Camera frame wait timed out");
                        }
                    } catch (InterruptedException ie) {
                        // shouldn't happen
                        throw new RuntimeException(ie);
                    }
                }
                mFrameAvailable = false;
            }

            // Latch the data.
            mTextureRender.checkGlError("before updateTexImage");
            mSurfaceTexture.updateTexImage();
        }

        /**
         * Draws the data from SurfaceTexture onto the current EGL surface.
         */
        public void drawImage() {
            mTextureRender.drawFrame(mSurfaceTexture);
        }

        @Override
        public void onFrameAvailable(SurfaceTexture st) {
            if (VERBOSE) Log.d(TAG, "new frame available");
            synchronized (mFrameSyncObject) {
                if (mFrameAvailable) {
                    throw new RuntimeException("mFrameAvailable already set, frame could be dropped");
                }
                mFrameAvailable = true;
                mFrameSyncObject.notifyAll();
            }
        }
    }


    /**
     * Code for rendering a texture onto a surface using OpenGL ES 2.0.
     */
    private static class STextureRender {
        private static final int FLOAT_SIZE_BYTES = 4;
        private static final int TRIANGLE_VERTICES_DATA_STRIDE_BYTES = 5 * FLOAT_SIZE_BYTES;
        private static final int TRIANGLE_VERTICES_DATA_POS_OFFSET = 0;
        private static final int TRIANGLE_VERTICES_DATA_UV_OFFSET = 3;
        private final float[] mTriangleVerticesData = {
                // X, Y, Z, U, V
                -1.0f, -1.0f, 0, 0.f, 0.f,
                1.0f, -1.0f, 0, 1.f, 0.f,
                -1.0f,  1.0f, 0, 0.f, 1.f,
                1.0f,  1.0f, 0, 1.f, 1.f,
        };

        private FloatBuffer mTriangleVertices;

        private static final String VERTEX_SHADER =
                "uniform mat4 uMVPMatrix;\n" +
                        "uniform mat4 uSTMatrix;\n" +
                        "attribute vec4 aPosition;\n" +
                        "attribute vec4 aTextureCoord;\n" +
                        "varying vec2 vTextureCoord;\n" +
                        "void main() {\n" +
                        "    gl_Position = uMVPMatrix * aPosition;\n" +
                        "    vTextureCoord = (uSTMatrix * aTextureCoord).xy;\n" +
                        "}\n";

        private static final String FRAGMENT_SHADER =
                "#extension GL_OES_EGL_image_external : require\n" +
                        "precision mediump float;\n" +      // highp here doesn't seem to matter
                        "varying vec2 vTextureCoord;\n" +
                        "uniform samplerExternalOES sTexture;\n" +
                        "void main() {\n" +
                        "    gl_FragColor = texture2D(sTexture, vTextureCoord);\n" +
                        "}\n";

        private float[] mMVPMatrix = new float[16];
        private float[] mSTMatrix = new float[16];

        private int mProgram;
        private int mTextureID = -12345;
        private int muMVPMatrixHandle;
        private int muSTMatrixHandle;
        private int maPositionHandle;
        private int maTextureHandle;

        public STextureRender() {
            mTriangleVertices = ByteBuffer.allocateDirect(
                    mTriangleVerticesData.length * FLOAT_SIZE_BYTES)
                    .order(ByteOrder.nativeOrder()).asFloatBuffer();
            mTriangleVertices.put(mTriangleVerticesData).position(0);

            android.opengl.Matrix.setIdentityM(mSTMatrix, 0);
        }

        public int getTextureId() {
            return mTextureID;
        }

        public void drawFrame(SurfaceTexture st) {
            checkGlError("onDrawFrame start");
            st.getTransformMatrix(mSTMatrix);

            // (optional) clear to green so we can see if we're failing to set pixels
            GLES20.glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            GLES20.glClear(GLES20.GL_DEPTH_BUFFER_BIT | GLES20.GL_COLOR_BUFFER_BIT);

            GLES20.glUseProgram(mProgram);
            checkGlError("glUseProgram");

            GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
            GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, mTextureID);

            mTriangleVertices.position(TRIANGLE_VERTICES_DATA_POS_OFFSET);
            GLES20.glVertexAttribPointer(maPositionHandle, 3, GLES20.GL_FLOAT, false,
                    TRIANGLE_VERTICES_DATA_STRIDE_BYTES, mTriangleVertices);
            checkGlError("glVertexAttribPointer maPosition");
            GLES20.glEnableVertexAttribArray(maPositionHandle);
            checkGlError("glEnableVertexAttribArray maPositionHandle");

            mTriangleVertices.position(TRIANGLE_VERTICES_DATA_UV_OFFSET);
            GLES20.glVertexAttribPointer(maTextureHandle, 2, GLES20.GL_FLOAT, false,
                    TRIANGLE_VERTICES_DATA_STRIDE_BYTES, mTriangleVertices);
            checkGlError("glVertexAttribPointer maTextureHandle");
            GLES20.glEnableVertexAttribArray(maTextureHandle);
            checkGlError("glEnableVertexAttribArray maTextureHandle");

            android.opengl.Matrix.setIdentityM(mMVPMatrix, 0);
            GLES20.glUniformMatrix4fv(muMVPMatrixHandle, 1, false, mMVPMatrix, 0);
            GLES20.glUniformMatrix4fv(muSTMatrixHandle, 1, false, mSTMatrix, 0);

            GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4);
            checkGlError("glDrawArrays");

            // IMPORTANT: on some devices, if you are sharing the external texture between two
            // contexts, one context may not see updates to the texture unless you un-bind and
            // re-bind it.  If you're not using shared EGL contexts, you don't need to bind
            // texture 0 here.
            GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, 0);
        }

        /**
         * Initializes GL state.  Call this after the EGL surface has been created and made current.
         */
        public void surfaceCreated() {
            mProgram = createProgram(VERTEX_SHADER, FRAGMENT_SHADER);
            if (mProgram == 0) {
                throw new RuntimeException("failed creating program");
            }
            maPositionHandle = GLES20.glGetAttribLocation(mProgram, "aPosition");
            checkLocation(maPositionHandle, "aPosition");
            maTextureHandle = GLES20.glGetAttribLocation(mProgram, "aTextureCoord");
            checkLocation(maTextureHandle, "aTextureCoord");

            muMVPMatrixHandle = GLES20.glGetUniformLocation(mProgram, "uMVPMatrix");
            checkLocation(muMVPMatrixHandle, "uMVPMatrix");
            muSTMatrixHandle = GLES20.glGetUniformLocation(mProgram, "uSTMatrix");
            checkLocation(muSTMatrixHandle, "uSTMatrix");

            int[] textures = new int[1];
            GLES20.glGenTextures(1, textures, 0);

            mTextureID = textures[0];
            GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, mTextureID);
            checkGlError("glBindTexture mTextureID");

            GLES20.glTexParameterf(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_MIN_FILTER,
                    GLES20.GL_NEAREST);
            GLES20.glTexParameterf(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_MAG_FILTER,
                    GLES20.GL_LINEAR);
            GLES20.glTexParameteri(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_WRAP_S,
                    GLES20.GL_CLAMP_TO_EDGE);
            GLES20.glTexParameteri(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_WRAP_T,
                    GLES20.GL_CLAMP_TO_EDGE);
            checkGlError("glTexParameter");
        }

        /**
         * Replaces the fragment shader.  Pass in null to reset to default.
         */
        public void changeFragmentShader(String fragmentShader) {
            if (fragmentShader == null) {
                fragmentShader = FRAGMENT_SHADER;
            }
            GLES20.glDeleteProgram(mProgram);
            mProgram = createProgram(VERTEX_SHADER, fragmentShader);
            if (mProgram == 0) {
                throw new RuntimeException("failed creating program");
            }
        }

        private int loadShader(int shaderType, String source) {
            int shader = GLES20.glCreateShader(shaderType);
            checkGlError("glCreateShader type=" + shaderType);
            GLES20.glShaderSource(shader, source);
            GLES20.glCompileShader(shader);
            int[] compiled = new int[1];
            GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, compiled, 0);
            if (compiled[0] == 0) {
                Log.e(TAG, "Could not compile shader " + shaderType + ":");
                Log.e(TAG, " " + GLES20.glGetShaderInfoLog(shader));
                GLES20.glDeleteShader(shader);
                shader = 0;
            }
            return shader;
        }

        private int createProgram(String vertexSource, String fragmentSource) {
            int vertexShader = loadShader(GLES20.GL_VERTEX_SHADER, vertexSource);
            if (vertexShader == 0) {
                return 0;
            }
            int pixelShader = loadShader(GLES20.GL_FRAGMENT_SHADER, fragmentSource);
            if (pixelShader == 0) {
                return 0;
            }

            int program = GLES20.glCreateProgram();
            if (program == 0) {
                Log.e(TAG, "Could not create program");
            }
            GLES20.glAttachShader(program, vertexShader);
            checkGlError("glAttachShader");
            GLES20.glAttachShader(program, pixelShader);
            checkGlError("glAttachShader");
            GLES20.glLinkProgram(program);
            int[] linkStatus = new int[1];
            GLES20.glGetProgramiv(program, GLES20.GL_LINK_STATUS, linkStatus, 0);
            if (linkStatus[0] != GLES20.GL_TRUE) {
                Log.e(TAG, "Could not link program: ");
                Log.e(TAG, GLES20.glGetProgramInfoLog(program));
                GLES20.glDeleteProgram(program);
                program = 0;
            }
            return program;
        }

        public void checkGlError(String op) {
            int error;
            while ((error = GLES20.glGetError()) != GLES20.GL_NO_ERROR) {
                Log.e(TAG, op + ": glError " + error);
                throw new RuntimeException(op + ": glError " + error);
            }
        }

        public static void checkLocation(int location, String label) {
            if (location < 0) {
                throw new RuntimeException("Unable to locate '" + label + "' in program");
            }
        }
    }

    /** test entry point */
    public void testEncodeCameraToMp4() throws Throwable {
        CameraToMpegWrapper.runTest(this);
    }

    /**
     * Tests encoding of AVC video from Camera input.  The output is saved as an MP4 file.
     */
    private void encodeCameraToMpeg() {
        // arbitrary but popular values
        int encWidth = mVideoSize.getWidth();
        int encHeight = mVideoSize.getHeight();
//        int encBitRate = 6000000;      // Mbps
        Log.d(TAG, MIME_TYPE + " output " + encWidth + "x" + encHeight + " @" + mEncBitRate);

        try {
            openCamera(encWidth, encHeight);
//            prepareCamera(encWidth, encHeight);
            prepareEncoder(encWidth, encHeight, mEncBitRate);
            mRecordingSurface.makeCurrent();
//            mCamera2VideoFragment.setRecordingSurface(mRecordingSurface);
//            prepareSurfaceTexture(); // todo check out, done in startCamera()

//            mCamera.startPreview();
            startPreview();

            long startWhen = System.nanoTime();
            long desiredEnd = startWhen + DURATION_SEC * 1000000000L;
            SurfaceTexture st = mStManager.getSurfaceTexture();
            int frameCount = 0;

            while (System.nanoTime() < desiredEnd) {
                // Feed any pending encoder output into the muxer.
                drainEncoder(false);

                // Switch up the colors every 15 frames.  Besides demonstrating the use of
                // fragment shaders for video editing, this provides a visual indication of
                // the frame rate: if the camera is capturing at 15fps, the colors will change
                // once per second.
                if ((frameCount % 15) == 0) {
                    String fragmentShader = null;
                    if ((frameCount & 0x01) != 0) {
                        fragmentShader = SWAPPED_FRAGMENT_SHADER;
                    }
                    mStManager.changeFragmentShader(fragmentShader);
                }
                frameCount++;

                // Acquire a new frame of input, and render it to the Surface.  If we had a
                // GLSurfaceView we could switch EGL contexts and call drawImage() a second
                // time to render it on screen.  The texture can be shared between contexts by
                // passing the GLSurfaceView's EGLContext as eglCreateContext()'s share_context
                // argument.
                mStManager.awaitNewImage();
                mStManager.drawImage();

                // Set the presentation time stamp from the SurfaceTexture's time stamp.  This
                // will be used by MediaMuxer to set the PTS in the video.
                if (VERBOSE) {
                    Log.d(TAG, "present: " +
                            ((st.getTimestamp() - startWhen) / 1000000.0) + "ms");
                }
                mRecordingSurface.setPresentationTime(st.getTimestamp());

                // Submit it to the encoder.  The eglSwapBuffers call will block if the input
                // is full, which would be bad if it stayed full until we dequeued an output
                // buffer (which we can't do, since we're stuck here).  So long as we fully drain
                // the encoder before supplying additional input, the system guarantees that we
                // can supply another frame without blocking.
                if (VERBOSE) Log.d(TAG, "sending frame to encoder");
                mRecordingSurface.swapBuffers();
            }

            // send end-of-stream to encoder, and drain remaining output
            drainEncoder(true);
        } finally {
            // release everything we grabbed
//            releaseCamera(); // todo done in closeCamera()
            releaseEncoder();
//            releaseSurfaceTexture(); // todo done in closeCamera()
            closeCamera();
        }
    }

    /**
     * Configures encoder and muxer state, and prepares the input Surface.  Initializes
     * mEncoder, mMuxer, mRecordingSurface, mBufferInfo, mTrackIndex, and mMuxerStarted.
     */
    private void prepareEncoder(int width, int height, int bitRate) {
        mBufferInfo = new MediaCodec.BufferInfo();

        MediaFormat format = MediaFormat.createVideoFormat(MIME_TYPE, width, height);

        // Set some properties.  Failing to specify some of these can cause the MediaCodec
        // configure() call to throw an unhelpful exception.
        format.setInteger(MediaFormat.KEY_COLOR_FORMAT,
                MediaCodecInfo.CodecCapabilities.COLOR_FormatSurface);
        format.setInteger(MediaFormat.KEY_BIT_RATE, bitRate);
        format.setInteger(MediaFormat.KEY_FRAME_RATE, FRAME_RATE);
        format.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, IFRAME_INTERVAL);
        if (VERBOSE) Log.d(TAG, "format: " + format);

        // Create a MediaCodec encoder, and configure it with our format.  Get a Surface
        // we can use for input and wrap it with a class that handles the EGL work.
        //
        // If you want to have two EGL contexts -- one for display, one for recording --
        // you will likely want to defer instantiation of CodecInputSurface until after the
        // "display" EGL context is created, then modify the eglCreateContext call to
        // take eglGetCurrentContext() as the share_context argument.

        try {
            mEncoder = MediaCodec.createEncoderByType(MIME_TYPE);
        } catch (IOException e) {
            e.printStackTrace();
        }

        mEncoder.configure(format, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
        mRecordingSurface = new CodecInputSurface(mEncoder.createInputSurface());
        mEncoder.start();

        // Output filename.  Ideally this would use Context.getFilesDir() rather than a
        // hard-coded output directory.
        String outputPath = new File(OUTPUT_DIR,
                "test." + width + "x" + height + ".mp4").toString();
        Log.i(TAG, "Output file is " + outputPath);


        // Create a MediaMuxer.  We can't add the video track and start() the muxer here,
        // because our MediaFormat doesn't have the Magic Goodies.  These can only be
        // obtained from the encoder after it has started processing data.
        //
        // We're not actually interested in multiplexing audio.  We just want to convert
        // the raw H.264 elementary stream we get from MediaCodec into a .mp4 file.
        try {
            mMuxer = new MediaMuxer(outputPath, MediaMuxer.OutputFormat.MUXER_OUTPUT_MPEG_4);
        } catch (IOException ioe) {
            throw new RuntimeException("MediaMuxer creation failed", ioe);
        }

        mTrackIndex = -1;
        mMuxerStarted = false;
    }

    /**
     * Releases encoder resources.
     */
    private void releaseEncoder() {
        if (VERBOSE) Log.d(TAG, "releasing encoder objects");
        if (mEncoder != null) {
            mEncoder.stop();
            mEncoder.release();
            mEncoder = null;
        }
        if (mRecordingSurface != null) {
            mRecordingSurface.release();
            mRecordingSurface = null;
        }
        if (mMuxer != null) {
            mMuxer.stop();
            mMuxer.release();
            mMuxer = null;
        }
    }

    /**
     * Extracts all pending data from the encoder and forwards it to the muxer.
     * <p>
     * If endOfStream is not set, this returns when there is no more data to drain.  If it
     * is set, we send EOS to the encoder, and then iterate until we see EOS on the output.
     * Calling this with endOfStream set should be done once, right before stopping the muxer.
     * <p>
     * We're just using the muxer to get a .mp4 file (instead of a raw H.264 stream).  We're
     * not recording audio.
     */
    private void drainEncoder(boolean endOfStream) {
        final int TIMEOUT_USEC = 10000;
        if (VERBOSE) Log.d(TAG, "drainEncoder(" + endOfStream + ")");

        if (endOfStream) {
            if (VERBOSE) Log.d(TAG, "sending EOS to encoder");
            mEncoder.signalEndOfInputStream();
        }

        int encoderStatus = mEncoder.dequeueOutputBuffer(mBufferInfo, TIMEOUT_USEC);
        ByteBuffer encoderOutputBuffer = mEncoder.getOutputBuffer(encoderStatus);
        while (true) {
            encoderStatus = mEncoder.dequeueOutputBuffer(mBufferInfo, TIMEOUT_USEC);
            if (encoderStatus == MediaCodec.INFO_TRY_AGAIN_LATER) {
                // no output available yet
                if (!endOfStream) {
                    break;      // out of while
                } else {
                    if (VERBOSE) Log.d(TAG, "no output available, spinning to await EOS");
                }
//            } else if (encoderStatus == MediaCodec.INFO_OUTPUT_BUFFERS_CHANGED) {
//                // not expected for an encoder
//                encoderOutputBuffers = mEncoder.getOutputBuffers();
            } else if (encoderStatus == MediaCodec.INFO_OUTPUT_FORMAT_CHANGED) {
                // should happen before receiving buffers, and should only happen once
                if (mMuxerStarted) {
                    throw new RuntimeException("format changed twice");
                }
                MediaFormat newFormat = mEncoder.getOutputFormat();
                Log.d(TAG, "encoder output format changed: " + newFormat);

                // now that we have the Magic Goodies, start the muxer
                mTrackIndex = mMuxer.addTrack(newFormat);
                mMuxer.start();
                mMuxerStarted = true;
            } else if (encoderStatus < 0) {
                Log.w(TAG, "unexpected result from encoder.dequeueOutputBuffer: " +
                        encoderStatus);
                // let's ignore it
            } else {
                ByteBuffer encodedData = encoderOutputBuffer;
                if (encodedData == null) {
                    throw new RuntimeException("encoderOutputBuffer " + encoderStatus +
                            " was null");
                }

                if ((mBufferInfo.flags & MediaCodec.BUFFER_FLAG_CODEC_CONFIG) != 0) {
                    // The codec config data was pulled out and fed to the muxer when we got
                    // the INFO_OUTPUT_FORMAT_CHANGED status.  Ignore it.
                    if (VERBOSE) Log.d(TAG, "ignoring BUFFER_FLAG_CODEC_CONFIG");
                    mBufferInfo.size = 0;
                }

                if (mBufferInfo.size != 0) {
                    if (!mMuxerStarted) {
                        throw new RuntimeException("muxer hasn't started");
                    }

                    // adjust the ByteBuffer values to match BufferInfo (not needed?)
                    encodedData.position(mBufferInfo.offset);
                    encodedData.limit(mBufferInfo.offset + mBufferInfo.size);

                    mMuxer.writeSampleData(mTrackIndex, encodedData, mBufferInfo);
                    if (VERBOSE) Log.d(TAG, "sent " + mBufferInfo.size + " bytes to muxer");
                }

                mEncoder.releaseOutputBuffer(encoderStatus, false);

                if ((mBufferInfo.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM) != 0) {
                    if (!endOfStream) {
                        Log.w(TAG, "reached end of stream unexpectedly");
                    } else {
                        if (VERBOSE) Log.d(TAG, "end of stream reached");
                    }
                    break;      // out of while
                }
            }
        }
    }

//    /**
//     * Add the stream output surface to the target output surface list.
//     *
//     * @param outputSurfaces The output surface list where the stream can
//     * add/remove its output surface.
//     * @param detach Detach the recording surface from the outputSurfaces.
//     */
//    public synchronized void onConfiguringOutputs(List<Surface> outputSurfaces,
//                                                  boolean detach) {
//        if (detach) {
//            // Can detach the surface in CONFIGURED and RECORDING state
//            if (getStreamState() != STREAM_STATE_IDLE) {
//                outputSurfaces.remove(mRecordingSurface);
//            } else {
//                Log.w(TAG, "Can not detach surface when recording stream is in IDLE state");
//            }
//        } else {
//            // Can add surface only in CONFIGURED state.
//            if (getStreamState() == STREAM_STATE_CONFIGURED) {
//                outputSurfaces.add(mRecordingSurface);
//            } else {
//                Log.w(TAG, "Can only add surface when recording stream is in CONFIGURED state");
//            }
//        }
//    }

//    /**
//     * Update capture request with configuration required for recording stream.
//     *
//     * @param requestBuilder Capture request builder that needs to be updated
//     * for recording specific camera settings.
//     * @param detach Detach the recording surface from the capture request.
//     */
//    public synchronized void onConfiguringRequest(CaptureRequest.Builder requestBuilder,
//                                                  boolean detach) {
//        if (detach) {
//            // Can detach the surface in CONFIGURED and RECORDING state
//            if (getStreamState() != STREAM_STATE_IDLE) {
//                requestBuilder.removeTarget(mRecordingSurface);
//            } else {
//                Log.w(TAG, "Can not detach surface when recording stream is in IDLE state");
//            }
//        } else {
//            // Can add surface only in CONFIGURED state.
//            if (getStreamState() == STREAM_STATE_CONFIGURED) {
//                requestBuilder.addTarget(mRecordingSurface);
//            } else {
//                Log.w(TAG, "Can only add surface when recording stream is in CONFIGURED state");
//            }
//        }
//    }

//    /**
//     * Start recording stream. Calling startRecording on an already started stream has no
//     * effect.
//     */
//    private synchronized void startRecording() {
//        if (getStreamState() == STREAM_STATE_RECORDING) {
//            Log.w(TAG, "Recording stream is already started");
//            return;
//        }
//
//        if (getStreamState() != STREAM_STATE_CONFIGURED) {
//            throw new IllegalStateException("Recording stream is not configured yet");
//        }
//
//        if (mUseMediaCodec) {
//            setStreamState(STREAM_STATE_RECORDING);
//            encodeCycle();
////            startBackgroundThread();
//        } else {
//            mMediaRecorder.start();
//        }
//    }

//    // todo its an overriden Thread.run() method
//    private void decodeCycle() {
//        try {
//            MediaCodec.BufferInfo info = new MediaCodec.BufferInfo(); // переиспользуем BufferInfo
//            while (getStreamState() == STREAM_STATE_RECORDING) {
//                if (mConfigured) { // если кодек готов
//                    int index = mDecoder.dequeueOutputBuffer(info, TIMEOUT_USEC);
//                    if (index >= 0) { // буфер с индексом index доступен
//                        // info.size > 0: если буфер не нулевого размера, то рендерим на Surface
//                        mDecoder.releaseOutputBuffer(index, info.size > 0);
//                        // заканчиваем работу декодера если достигнут конец потока данных
//                        if ((info.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM) == MediaCodec.BUFFER_FLAG_END_OF_STREAM) {
//                            setStreamState(STREAM_STATE_IDLE);
//                            break;
//                        }
//                    }
//                } else {
//                    // просто спим, т.к. кодек не готов
//                    try {
//                        Thread.sleep(10);
//                    } catch (InterruptedException ignore) {
//                    }
//                }
//            }
//        } finally {
//            // освобождение ресурсов
//            releaseMediaCodec(mDecoder);
//        }
//    }

//    /**
//     * Starts MediaCodec mode recording.
//     */
//    private void encodeCycle() {
//        /**
//         * Start video recording asynchronously. we need a loop to handle output
//         * data for each frame.
//         */
//        mBackgroundThread = new Thread() {
//            @Override
//            public void run() {
////                configureCapturingTool();
//
////                try {
//                    while (getStreamState() == STREAM_STATE_RECORDING) {
//                        if (VERBOSE) {
//                            Log.v(TAG, "Recording thread starts");
//                        }
//
//                        // Feed encoder output into the muxer until recording stops.
//                        doEncoding(/* notifyEndOfStream */false);
//                    }
////                } finally {
//                    if (VERBOSE) {
//                        Log.v(TAG, "Recording thread completes");
//                    }
//
////                    releaseMediaCodec(mEncoder);
////                    releaseMuxer();
////                }
//                return;
//            }
//        };
//        mBackgroundThread.start();
//    }

//    /**
//     * <p>
//     * Stop recording stream. Calling stopEncoding on an already stopped stream has no
//     * effect. Producer(in this case, CameraDevice) should stopEncoding before this call
//     * to avoid sending buffers to a stopped encoder.
//     * </p>
//     * <p>
//     * TODO: We have to release encoder and muxer for MediaCodec mode because
//     * encoder is closely coupled with muxer, and muxer can not be reused
//     * across different recording session(by design, you can not reset/restart
//     * it). To save the subsequent startRecording recording time, we need avoid releasing
//     * encoder for future.
//     * </p>
//     */
//    private synchronized void stopEncoding() {
//        // Added by Ben Ning, to resolve exception issue when stop recording.
//        try {
//            mPreviewSession.stopRepeating();
//            mPreviewSession.abortCaptures();
//        } catch (CameraAccessException e) {
//            e.printStackTrace();
//        }
//
//        if (mUseMediaCodec) {
//            if (getStreamState() != STREAM_STATE_RECORDING) {
//                Log.w(TAG, "Recording stream is not started yet");
//                return;
//            }
//            setStreamState(STREAM_STATE_IDLE);
//            Log.e(TAG, "setting camera to idle");
//
//            // Wait until recording thread stopEncoding todo find out how to deal with bkgd thread
//            try {
//                mBackgroundThread.join();
//            } catch (InterruptedException e) {
//                throw new RuntimeException("Stop recording failed", e);
//            }
//            // Drain encoder
//            doEncoding(/* notifyEndOfStream */true);
//            releaseMediaCodec(mEncoder);
//            releaseMuxer();
//        } else {
//            mMediaRecorder.stop();
//            mMediaRecorder.reset();
//        }
//    }

//    /**
//     * Starts a background thread and its {@link Handler}.
//     */
//    private void startBackgroundThread() {
//        mRecordingThread = new HandlerThread("CameraBackground")/* {
//            @Override
//            public void run() {
//                if (VERBOSE) {
//                    Log.v(TAG, "Recording thread starts");
//                }
//                while (getStreamState() == STREAM_STATE_RECORDING) {
//                    // Feed encoder output into the muxer until recording stops.
//                    doEncoding(*//* notifyEndOfStream *//*false);
//                }
//                if (VERBOSE) {
//                    Log.v(TAG, "Recording thread completes");
//                }
//                return;
//            }
//        }*/;
//        mRecordingThread.start();
//        mRecordingHandler = new Handler(mRecordingThread.getLooper());
//    }
//
//    /**
//     * Stops the background thread and its {@link Handler}.
//     */
//    private void stopBackgroundThread() {
//        mRecordingThread.quitSafely();
//        try {
//            mRecordingThread.join();
//            mRecordingThread = null;
//            mRecordingHandler = null;
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
//    }
//
//    // Thread-safe access to the stream state.
//    private synchronized void setStreamState(int state) {
//        synchronized (mStateLock) {
//            if (state < STREAM_STATE_IDLE) {
//                throw new IllegalStateException("try to set an invalid state");
//            }
//            mStreamState = state;
//        }
//    }
//
//    // Thread-safe access to the stream state.
//    private int getStreamState() {
//        synchronized(mStateLock) {
//            return mStreamState;
//        }
//    }
//
//    private void releaseMediaCodec(MediaCodec mediaCodec) {
//        // Release encoder
//        if (VERBOSE) {
//            Log.v(TAG, "releasing encoder");
//        }
//        if (mediaCodec != null && mConfigured) {
//            mediaCodec.stop();
//            mediaCodec.release();
//            if (mRecordingSurface != null) {
//                mRecordingSurface.release();
//            }
//            mEncoder = null;
//            mConfigured = false;
//        }
//    }
//
//    private void releaseMuxer() {
//        if (VERBOSE) {
//            Log.v(TAG, "releasing muxer");
//        }
//        if (mMuxer != null) {
//            mMuxer.stop();
//            mMuxer.release();
//            mMuxer = null;
//        }
//    }
//
//    private String getOutputMediaFileName() {
//        // Create a media file name
//        String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
//        String mediaFileName = getContext().getExternalFilesDir(null).getAbsolutePath()
//                + File.separator + "VID_" + timeStamp + ".mp4";
//        return mediaFileName;
//    }
//
//    /**
//     * Configures encoder and muxer state, and prepares the input Surface.
//     * Initializes mEncoder, mMuxer, mRecordingSurface, mBufferInfo,
//     * mTrackIndex, and mMuxerStarted.
//     */
//    private void configureCapturingTool() {
//        if (mUseMediaCodec) {
//            mBufferInfo = new MediaCodec.BufferInfo();
//
//            MediaFormat format = MediaFormat.createVideoFormat(MIME_TYPE, mStreamSize.getWidth(),
//                    mStreamSize.getHeight());
//            /**
//             * Set encoding properties. Failing to specify some of these can cause
//             * the MediaCodec configureCapturingTool() call to throw an exception.
//             */
//            format.setInteger(MediaFormat.KEY_COLOR_FORMAT,
//                    MediaCodecInfo.CodecCapabilities.COLOR_FormatSurface);
//            format.setInteger(MediaFormat.KEY_BIT_RATE, mEncBitRate);
//            format.setInteger(MediaFormat.KEY_FRAME_RATE, FRAME_RATE);
//            format.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, IFRAME_INTERVAL);
//            Log.i(TAG, "configureCapturingTool video encoding format: " + format);
//
//            // Create/configureCapturingTool a MediaCodec encoder.
//            try {
//                mEncoder = MediaCodec.createEncoderByType(MIME_TYPE);
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//
//            mEncoder.configure(format, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
//            mConfigured = true;
////            mRecordingSurface = mEncoder.createInputSurface();
//
//            mEncoder.start();
//            String outputFileName = getOutputMediaFileName();
//            if (outputFileName == null) {
//                throw new IllegalStateException("Failed to get video output file");
//            }
//            /**
//             * Create a MediaMuxer. We can't add the video track and startRecording() the
//             * muxer until the encoder starts and notifies the new media format.
//             */
//            try {
//                mMuxer = new MediaMuxer(outputFileName, MediaMuxer.OutputFormat.MUXER_OUTPUT_MPEG_4);
//            } catch (IOException ioe) {
//                throw new IllegalStateException("MediaMuxer creation failed", ioe);
//            }
//            mMuxerStarted = false;
//        } else {
//            final Activity activity = getActivity();
//            if (null == activity) {
//                return;
//            }
//
//            mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
//            mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.SURFACE);
//            mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
//
//            if (mNextVideoFullFileName == null || mNextVideoFullFileName.isEmpty()) {
//                mNextVideoFullFileName = getOutputMediaFileName();
//            }
//
//            mMediaRecorder.setOutputFile(mNextVideoFullFileName);
//            mMediaRecorder.setVideoEncodingBitRate(mEncBitRate);
//            mMediaRecorder.setVideoFrameRate(FRAME_RATE);
//            mMediaRecorder.setVideoSize(mVideoSize.getWidth(), mVideoSize.getHeight());
//            mMediaRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.H264);
//            mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AAC);
//
//            int rotation = activity.getWindowManager().getDefaultDisplay().getRotation();
//            switch (mSensorOrientation) {
//                case SENSOR_ORIENTATION_DEFAULT_DEGREES:
//                    mMediaRecorder.setOrientationHint(DEFAULT_ORIENTATIONS.get(rotation));
//                    break;
//                case SENSOR_ORIENTATION_INVERSE_DEGREES:
//                    mMediaRecorder.setOrientationHint(INVERSE_ORIENTATIONS.get(rotation));
//                    break;
//            }
//
//            try {
//                mMediaRecorder.prepare();
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }
//    }
//
//    /**
//     * Do encoding by using MediaCodec encoder, then extracts all pending data
//     * from the encoder and forwards it to the muxer.
//     * <p>
//     * If notifyEndOfStream is not set, this returns when there is no more data
//     * to output. If it is set, we send EOS to the encoder, and then iterate
//     * until we see EOS on the output. Calling this with notifyEndOfStream set
//     * should be done once, before stopping the muxer.
//     * </p>
//     * <p>
//     * We're just using the muxer to get a .mp4 file and audio is not included
//     * here.
//     * </p>
//     */
//    private void doEncoding(boolean notifyEndOfStream) {
//        if (VERBOSE) {
//            Log.v(TAG, "doEncoding(" + notifyEndOfStream + ")");
//        }
//        if (notifyEndOfStream) {
//            mEncoder.signalEndOfInputStream();
//        }
//
//        boolean notDone = true;
//        while (notDone) {
////            int inputBufferId = mEncoder.dequeueInputBuffer(TIMEOUT_USEC);
////            if (inputBufferId >= 0) {
////                ByteBuffer inputBuffer = mEncoder.getInputBuffer(inputBufferId);
////
////                byte[] bytes;
////
////                if (inputBuffer.hasArray()) {
////                    bytes = inputBuffer.array();
////                } else {
////                    continue;
////                }
////
////                mEncoder.queueInputBuffer(inputBufferId, 0, bytes.length, TIMEOUT_USEC, 0);
////            }
//
//            int outputBufferId = mEncoder.dequeueOutputBuffer(mBufferInfo, TIMEOUT_USEC);
////            if (outputBufferId >= 0) {
////                ByteBuffer outputBuffer = mEncoder.getOutputBuffer(outputBufferId);
////                MediaFormat bufferFormat = mEncoder.getOutputFormat(outputBufferId);
////
////                Parcel parcel = null;
////                byte[] bytes;
////
////                if (outputBuffer.hasArray()) {
////                    bytes = outputBuffer.array();
////                }
////                else {
////                    continue;
////                }
////
////                parcel.unmarshall(bytes, 0, bytes.length);
////                mRecordingSurface.readFromParcel(parcel);
////
////                mEncoder.releaseOutputBuffer(outputBufferId, true);
////            }/* else if (outputBufferId == MediaCodec.INFO_OUTPUT_FORMAT_CHANGED) {
////                outputF
////            }*/
////
////            if ((mBufferInfo.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM) != 0) {
////                if (!notifyEndOfStream) {
////                    Log.w(TAG, "reached end of stream unexpectedly");
////                } else {
////                    if (VERBOSE) {
////                        Log.v(TAG, "end of stream reached");
////                    }
////                }
////                // Finish encoding.
////                notDone = false;
////            }
////        }
//
////        while (notDone) {
//            // = mEncoder.dequeueOutputBuffer(mBufferInfo, TIMEOUT_USEC);
//
//            if (outputBufferId == MediaCodec.INFO_TRY_AGAIN_LATER) {
//                if (!notifyEndOfStream) {
//                    /**
//                     * Break out of the while loop because the encoder is not
//                     * ready to output anything yet.
//                     */
//                    notDone = false;
//                } else {
//                    if (VERBOSE) {
//                        Log.v(TAG, "no output available, spinning to await EOS");
//                    }
//                }
////            } else if (encoderStatus == MediaCodec.INFO_OUTPUT_BUFFERS_CHANGED
////                    /*MediaCodec.INFO_OUTPUT_FORMAT_CHANGED*/) {
////                // generic case for mediacodec, not likely occurs for encoder.
////                encoderOutputBuffers = mEncoder.getOutputBuffer(0);
//            } else if (outputBufferId == MediaCodec.INFO_OUTPUT_FORMAT_CHANGED) {
//                /**
//                 * should happen before receiving buffers, and should only
//                 * happen once
//                 */
//                if (mMuxerStarted) {
//                    throw new IllegalStateException("format changed twice");
//                }
//                MediaFormat newFormat = mEncoder.getOutputFormat();
//                if (VERBOSE) {
//                    Log.v(TAG, "encoder output format changed: " + newFormat);
//                }
//                mTrackIndex = mMuxer.addTrack(newFormat);
//                mMuxer.start();
//                mMuxerStarted = true;
//            } else if (outputBufferId < 0) {
//                Log.w(TAG, "unexpected result from encoder.dequeueOutputBuffer: " + outputBufferId);
//            } else {
//                // Normal flow: get output encoded buffer, send to muxer.
//                ByteBuffer encoderOutputBuffer = mEncoder.getOutputBuffer(outputBufferId);
//
////                Image frameImage = mEncoder.getOutputImage(encoderStatus); // todo work directly with image
////                Bitmap bm = BitmapFactory.decodeResource(frameImage, 0);
//
//                Parcel parcel = null;
//                byte[] bytes;
//
//                if (encoderOutputBuffer.hasArray()) {
//                    bytes = encoderOutputBuffer.array();
//                }
//                else {
//                    continue;
//                }
//
//                parcel.unmarshall(bytes, 0, bytes.length);
//                mRecordingSurface.readFromParcel(parcel);
//
//                if (encoderOutputBuffer == null) {
//                    throw new RuntimeException("encoderOutputBuffer " + outputBufferId +
//                            " was null");
//                }
//                if ((mBufferInfo.flags & MediaCodec.BUFFER_FLAG_CODEC_CONFIG) != 0) {
//                    /**
//                     * The codec config data was pulled out and fed to the muxer
//                     * when we got the INFO_OUTPUT_FORMAT_CHANGED status. Ignore
//                     * it.
//                     */
//                    if (VERBOSE) {
//                        Log.v(TAG, "ignoring BUFFER_FLAG_CODEC_CONFIG");
//                    }
//                    mBufferInfo.size = 0;
//                }
//                if (mBufferInfo.size != 0) {
//                    if (!mMuxerStarted) {
//                        throw new RuntimeException("muxer hasn't started");
//                    }
//                    /**
//                     * It's usually necessary to adjust the ByteBuffer values to
//                     * match BufferInfo.
//                     */
//                    encoderOutputBuffer.position(mBufferInfo.offset);
//                    encoderOutputBuffer.limit(mBufferInfo.offset + mBufferInfo.size);
//                    mMuxer.writeSampleData(mTrackIndex, encoderOutputBuffer, mBufferInfo);
//                    if (VERBOSE) {
//                        Log.v(TAG, "sent " + mBufferInfo.size + " bytes to muxer");
//                    }
//                }
//                mEncoder.releaseOutputBuffer(outputBufferId, false);
//                if ((mBufferInfo.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM) != 0) {
//                    if (!notifyEndOfStream) {
//                        Log.w(TAG, "reached end of stream unexpectedly");
//                    } else {
//                        if (VERBOSE) {
//                            Log.v(TAG, "end of stream reached");
//                        }
//                    }
//                    // Finish encoding.
//                    notDone = false;
//                }
//            }
//        } // End of while (notDone)
//    }

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
//        final Activity activity = getActivity();
//        if (null == activity) {
//            return;
//        }
//
//        if (getStreamState() == STREAM_STATE_RECORDING) {
//            throw new IllegalStateException(
//                    "Stream can only be configured when stream is in IDLE state");
//        }
//        boolean isConfigChanged = !mStreamSize.equals(mVideoSize);
//        mStreamSize = mVideoSize;
//
//        if (getStreamState() == STREAM_STATE_CONFIGURED) {
//            /**
//             * Stream is already configured, need release encoder and muxer
//             * first, then reconfigure only if configuration is changed.
//             */
//            if (!isConfigChanged) {
//                /**
//                 * TODO: this is only the skeleton, it is tricky to
//                 * implement because muxer need reconfigure always. But
//                 * muxer is closely coupled with MediaCodec for now because
//                 * muxer can only be started once format change callback is
//                 * sent from mediacodec. We need decouple MediaCodec and
//                 * Muxer for future.
//                 */
//            }
//            releaseMediaCodec(mEncoder);
//            releaseMuxer();
//            configureCapturingTool();
//        } else {
//            configureCapturingTool();
//        }
    }

//    private synchronized void configureDecoder(Surface surface, int width, int height,
//            ByteBuffer csd0) {
//        if (mConfigured) { // просто флаг, чтобы знать, что декодер готов
//            throw new IllegalStateException();
//        }
//        // создаем видео формат
//        MediaFormat format = MediaFormat.createVideoFormat("video/avc", width, height);
//        // передаем наш csd-0
//        format.setByteBuffer("csd-0", csd0);
//
//        // создаем декодер
//        try {
//            mDecoder = MediaCodec.createDecoderByType("video/avc");
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//        // конфигурируем декодер
//        mDecoder.configure(format, surface, null, 0);
//        mDecoder.start();
//        mConfigured = true;
//    }
//
//    private void decodeSample(byte[] data, int offset, int size, long presentationTimeUs, int flags) {
//        if (mConfigured) {
//            // вызов блокирующий
//                        int index = mDecoder.dequeueInputBuffer(TIMEOUT_USEC);
//            if (index >= 0) {
//                ByteBuffer buffer = mDecoder.getInputBuffer(index);
//                buffer.clear(); // обязательно сбросить позицию и размер буфера
//                buffer.put(data, offset, size);
//                // сообщаем системе о доступности буфера данных
//                mDecoder.queueInputBuffer(index, 0, size, presentationTimeUs, flags);
//            }
//        }
//    }

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

//    /**
//     * Draws a frame onto the SurfaceView and the encoder surface.
//     * <p>
//     * This will be called whenever we get a new preview frame from the camera.  This runs
//     * on the UI thread, which ordinarily isn't a great idea -- you really want heavy work
//     * to be on a different thread -- but we're really just throwing a few things at the GPU.
//     * The upside is that we don't have to worry about managing state changes between threads.
//     * <p>
//     * If there was a pending frame available notification when we shut down, we might get
//     * here after onPause().
//     */
//    private void drawFrame(final View view, SurfaceTexture cameraTexture) {
//        //Log.d(TAG, "drawFrame");
//        if (mEglCore == null) {
//            Log.d(TAG, "Skipping drawFrame after shutdown");
//            return;
//        }
//
//        // Latch the next frame from the camera.
//        mDisplaySurface.makeCurrent();
//        cameraTexture.updateTexImage();
//        cameraTexture.getTransformMatrix(mTmpMatrix);
//
//        mGles20.glGenTextures(1, mTextures, 0);
//
//        try {
//            MediaCodec encoder = MediaCodec.createEncoderByType("video/avc");
//            ByteBuffer outputBuffer = encoder.getOutputBuffer(0);
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//
//        // Fill the SurfaceView with it.
//        SurfaceView sv = view.findViewById(R.id.texture);
//        int viewWidth = sv.getWidth();
//        int viewHeight = sv.getHeight();
//        GLES20.glViewport(0, 0, viewWidth, viewHeight);
//        mFullFrameBlit.drawFrame(mTextures[0], mTmpMatrix);
//
//        drawExtra(mFrameNum, viewWidth, viewHeight);
//
//        mDisplaySurface.swapBuffers();
//
//        // Send it to the video encoder.
//        if (!mFileSaveInProgress) {
//            mEncoderSurface.makeCurrent();
//            GLES20.glViewport(0, 0, mPreviewSize.getWidth(), mPreviewSize.getHeight());
//            mFullFrameBlit.drawFrame(mTextures[0], mTmpMatrix);
//
//            drawExtra(mFrameNum, mPreviewSize.getWidth(), mPreviewSize.getHeight());
//
//            mCircEncoder.frameAvailableSoon();
//            mEncoderSurface.setPresentationTime(cameraTexture.getTimestamp());
//            mEncoderSurface.swapBuffers();
//        }
//
//        mFrameNum++;
//    }

//    /**
//     * Adds a bit of extra stuff to the display just to give it flavor.
//     */
//    private static void drawExtra(int frameNum, int width, int height) {
//        // We "draw" with the scissor rect and clear calls.  Note this uses window coordinates.
//        int val = frameNum % 3;
//        switch (val) {
//            case 0:  GLES20.glClearColor(1.0f, 0.0f, 0.0f, 1.0f);   break;
//            case 1:  GLES20.glClearColor(0.0f, 1.0f, 0.0f, 1.0f);   break;
//            case 2:  GLES20.glClearColor(0.0f, 0.0f, 1.0f, 1.0f);   break;
//        }
//
//        int xpos = (int) (width * ((frameNum % 100) / 100.0f));
//        GLES20.glEnable(GLES20.GL_SCISSOR_TEST);
//        GLES20.glScissor(xpos, 0, width / 32, height / 32);
//        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
//        GLES20.glDisable(GLES20.GL_SCISSOR_TEST);
//    }

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
//        if (null == mCameraDevice || !mTextureView.isAvailable() || null == mPreviewSize) {
//            return;
//        }
//        try {
//            closePreviewSession();
//            configureCamera();
//
//            SurfaceTexture texture = mTextureView.getSurfaceTexture();
//            assert texture != null;
//            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
//            mPreviewBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_RECORD);
//            List<Surface> surfaces = new ArrayList<>();
//
//            // Set up Surface for the camera preview
//            Surface previewSurface = new Surface(texture);
//            surfaces.add(previewSurface);
////            mPreviewBuilder.addTarget(previewSurface);
//
//            // Set up Surface for the MediaRecorder
//            Surface recorderSurface = null;
//
//            if (mUseMediaCodec) {
//                recorderSurface = mRecordingSurface;
//            } else {
//                recorderSurface = mMediaRecorder.getSurface();
//            }
//
//            surfaces.add(recorderSurface);
////            mPreviewBuilder.addTarget(recorderSurface);
//
//            onConfiguringOutputs(surfaces, false);
//            onConfiguringRequest(mPreviewBuilder, false);
//
//            // Start a capture session
//            // Once the session starts, we can update the UI and startRecording recording
//            mCameraDevice.createCaptureSession(surfaces, new CameraCaptureSession.StateCallback() {
//
//                @RequiresApi(api = Build.VERSION_CODES.O)
//                @Override
//                public void onConfigured(@NonNull CameraCaptureSession cameraCaptureSession) {
//                    mPreviewSession = cameraCaptureSession;
//                    updateFrame();
//
//                    final SurfaceTexture surface = new SurfaceTexture(true);
//
//                    getActivity().runOnUiThread(new Runnable() {
//                        @Override
//                        public void run() {
//                            // UI
//                            mButtonVideo.setText(R.string.stop);
//                            mIsRecordingVideo = true;
//
//                            // Start recording
//                            try {
//                                startRecording();
//                            } catch (IllegalStateException e) {
//                                e.printStackTrace();
//                            }
//
////                            drawFrame(mView, surface);
//
//                            // Setting the recording time counter
//                            mChronometer.setBase(SystemClock.elapsedRealtime());
//                            mChronometer.setVisibility(View.VISIBLE);
//                            mChronometer.start();
//                        }
//                    });
//                }
//
//                @Override
//                public void onConfigureFailed(@NonNull CameraCaptureSession cameraCaptureSession) {
//                    Activity activity = getActivity();
//                    if (null != activity) {
//                        Toast.makeText(activity, "Failed", Toast.LENGTH_SHORT).show();
//                    }
//                }
//            }, mRecordingHandler);
//        } catch (CameraAccessException/* | IOException*/ e) {
//            e.printStackTrace();
//        }
    }

    @Override
    public void stopCamera() {
//        // UI
//        mIsRecordingVideo = false;
//        mButtonVideo.setText(R.string.record);
//
//        // Stop recording
//        stopEncoding();
//
//        Activity activity = getActivity();
//        if (null != activity) {
//            Toast.makeText(activity, "Video saved: " + mNextVideoFullFileName,
//                    Toast.LENGTH_SHORT).show();
//            Log.d(TAG, "Video saved: " + mNextVideoFullFileName);
//        }
//        mNextVideoFullFileName = null;
//        startPreview();
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
            mPreviewSession.setRepeatingRequest(mPreviewBuilder.build(), null, mRecordingHandler);
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

    public static Camera2VideoFragment newInstance() {
        return new Camera2VideoFragment();
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

        mToggleFlashButton = view.findViewById(R.id.mediaCodec);
        mToggleFlashButton.setOnClickListener(this);

        mChronometer = view.findViewById(R.id.chronometer);
    }

    @Override
    public void onResume() {
        super.onResume();
//        startBackgroundThread();

        if (mTextureView.isAvailable()) {
            openCamera(mTextureView.getWidth(), mTextureView.getHeight());
        } else {
            mTextureView.setSurfaceTextureListener(mSurfaceTextureListener);
        }
    }

    @Override
    public void onPause() {
        closeCamera();
//        stopBackgroundThread();
        super.onPause();
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.video: {
                if (mIsRecordingVideo) {
                    mChronometer.stop();
                    mChronometer.setVisibility(View.INVISIBLE);

//                    stopCamera();
                    closeCamera();
                } else {
//                    startCamera();
                    try {
                        testEncodeCameraToMp4();
                    } catch (Throwable throwable) {
                        throwable.printStackTrace();
                    }
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

            case R.id.mediaCodec: {
                try {
                    mCameraId = mCameraManager.getCameraIdList()[0];

                    if (mUseMediaCodec) {
                        Toast.makeText(getContext(), "MediaCodec is turned off!",
                                Toast.LENGTH_SHORT).show();
                        mToggleFlashButton.setImageResource(R.mipmap.mediacodec_on);
                        mUseMediaCodec = false;
                    } else {
                        Toast.makeText(getContext(), "MediaCodec is turned on!",
                                Toast.LENGTH_SHORT).show();
                        mToggleFlashButton.setImageResource(R.mipmap.mediacodec_off);
                        mUseMediaCodec = true;
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
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
                        Toast.makeText(getContext(), R.string.permission_request,
                                Toast.LENGTH_LONG).show();
//                        ErrorDialog.newInstance(getString(R.string.permission_request))
//                                .show(getChildFragmentManager(), FRAGMENT_DIALOG);
                        break;
                    }
                }
            } else {
//                ErrorDialog.newInstance(getString(R.string.permission_request))
//                        .show(getChildFragmentManager(), FRAGMENT_DIALOG);
                Toast.makeText(getContext(), R.string.permission_request,
                        Toast.LENGTH_LONG).show();
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
    public void openCamera(int width, int height) {
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
            Toast.makeText(getActivity(), R.string.camera_error, Toast.LENGTH_LONG).show();
//            ErrorDialog.newInstance(getString(R.string.camera_error))
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

            if (mUseMediaCodec) {
                if (null != mEncoder) {
                    mEncoder.release();
                    mEncoder = null;
                }
            } else {
                if (null != mMediaRecorder) {
                    mMediaRecorder.release();
                    mMediaRecorder = null;
                }
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
    public void startPreview() {
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
                    }, mRecordingHandler);
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
            matrix.postRotate(90 * (rotation - 2), centerX, centerY);
        }
        mTextureView.setTransform(matrix);
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

//    public static class ErrorDialog extends DialogFragment {
//
//        private static final String ARG_MESSAGE = "message";
//
//        public static ErrorDialog newInstance(String message) {
//            ErrorDialog dialog = new ErrorDialog();
//            Bundle args = new Bundle();
//            args.putString(ARG_MESSAGE, message);
//            dialog.setArguments(args);
//            return dialog;
//        }
//
//        @Override
//        public Dialog onCreateDialog(Bundle savedInstanceState) {
//            final Activity activity = getActivity();
//            return new AlertDialog.Builder(activity)
//                    .setMessage(getArguments().getString(ARG_MESSAGE))
//                    .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
//                        @Override
//                        public void onClick(DialogInterface dialogInterface, int i) {
//                            activity.finish();
//                        }
//                    })
//                    .create();
//        }
//
//    }

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
