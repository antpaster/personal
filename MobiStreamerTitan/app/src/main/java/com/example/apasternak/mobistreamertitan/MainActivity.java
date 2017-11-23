package com.example.apasternak.mobistreamertitan;

import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.camera2.CameraManager;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @RequiresApi(api = Build.VERSION_CODES.N)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Camera2VideoFragment mCamera2videoFragment = new Camera2VideoFragment();

//        GLSurfaceView mGLSurfaceView = new GLSurfaceView(this);
//        mCamera2videoFragment.setGLSurfaceView(mGLSurfaceView);
//
//        setContentView(mCamera2videoFragment.getGLSurfaceView());

        // Setting up the camera manager
        mCamera2videoFragment.setCameraManager(
                (CameraManager) getSystemService(Context.CAMERA_SERVICE));

        // Checking whether the device has a flash
        mCamera2videoFragment.setTorchFlag(
                getApplicationContext().getPackageManager().hasSystemFeature(
                        PackageManager.FEATURE_CAMERA_FLASH));

        setContentView(R.layout.activity_main);
        if (null == savedInstanceState) {
            getFragmentManager().beginTransaction()
                    .replace(R.id.container, mCamera2videoFragment)
                    .commit();
        }
    }
}
