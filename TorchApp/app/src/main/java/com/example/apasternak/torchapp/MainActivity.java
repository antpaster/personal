package com.example.apasternak.torchapp;

import android.content.Context;
import android.content.Intent;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraManager;
import android.media.MediaPlayer;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

public class MainActivity extends AppCompatActivity {

    ImageButton mTorchOn;
    ImageButton mTorchOff;
    boolean mTorchOnFlag = false;
    String mCameraId;
    CameraManager mCameraManager;
    MediaPlayer mMediaPlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mCameraManager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
        try {
            mCameraId = mCameraManager.getCameraIdList()[0];
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }

        mTorchOn = findViewById(R.id.flash_on);
        mTorchOn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startService(v);

                try {
                    if (!mTorchOnFlag) {
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                            mCameraManager.setTorchMode(mCameraId, true);
//                            playOnOffSound();

                            mTorchOn.setVisibility(View.INVISIBLE);
                            mTorchOff.setVisibility(View.VISIBLE);
                        }
                        mTorchOnFlag = true;
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        mTorchOff = findViewById(R.id.flash_off);
        mTorchOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                stopService(v);

                try {
                    if (mTorchOnFlag) {
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                            mCameraManager.setTorchMode(mCameraId, false);
//                            playOnOffSound();

                            mTorchOff.setVisibility(View.INVISIBLE);
                            mTorchOn.setVisibility(View.VISIBLE);
                        }
                        mTorchOnFlag = false;
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    void playOnOffSound() {
        mMediaPlayer = MediaPlayer.create(MainActivity.this, R.raw.haha);
        mMediaPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {

            @Override
            public void onCompletion(MediaPlayer mp) {
                // TODO Auto-generated method stub
                mp.release();
            }
        });
        mMediaPlayer.start();
    }

    public void startService(View view) {
        startService(new Intent(getBaseContext(), TorchService.class));
    }

    public void stopService(View view) {
        stopService(new Intent(getBaseContext(), TorchService.class));
    }
}
