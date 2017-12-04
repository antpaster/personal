package com.example.apasternak.mobistreamertitan;

import android.annotation.TargetApi;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraManager;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Surface;

@RequiresApi(api = Build.VERSION_CODES.N)
public class MainActivity extends AppCompatActivity {
    public static final String TAG = "MobiStreamerTitan";

//    private CameraToMpegTest mCameraToMpegTest = new CameraToMpegTest();
//
//    private Camera2VideoFragment mCamera2VideoFragment
//            = mCameraToMpegTest.getCamera2VideoFragment();

    @TargetApi(Build.VERSION_CODES.O)
    @RequiresApi(api = Build.VERSION_CODES.N)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

//        SurfaceTexture st = new SurfaceTexture(false);
//        Surface surface = new Surface(st);
//
//        Rect rect = new Rect();
//        rect.set(0, 0, 720, 960);
//
//        Canvas canvas = surface.lockCanvas(rect);
//        Bitmap bm = BitmapFactory.decodeResource(getApplicationContext().getResources(), R.mipmap.flash_on);
//        Bitmap mutableBm = bm.copy(Bitmap.Config.ARGB_8888, true);
//        canvas.drawBitmap(mutableBm, 0, 0, null);
//
//        surface.unlockCanvasAndPost(canvas);

//        CodecInputSurface cis = new CodecInputSurface(surface);
//        mCameraToMpegTest.setInputSurface(cis);
//
//        mCamera2VideoFragment.setRecordingSurface(cis.getSurface());

        setContentView(R.layout.activity_main);
        if (null == savedInstanceState) {
//            try {
//                mCameraToMpegTest.testEncodeCameraToMp4();
//            } catch (Throwable throwable) {
//                throwable.printStackTrace();
//            }
//
//            mCameraToMpegTest.setInputSurface(surface);
//
//            mCamera2VideoFragment.setRecordingSurface(surface);
//
////            mCamera2VideoFragment.setRecordingSurface(mCameraToMpegTest.getInputSurface().getSurface());

            getFragmentManager().beginTransaction()
                    .replace(R.id.container, Camera2VideoFragment.newInstance())
                    .commit();
        }
    }
}
