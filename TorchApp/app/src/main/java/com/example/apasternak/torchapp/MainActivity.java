package com.example.apasternak.torchapp;

import android.content.Context;
import android.hardware.camera2.CameraManager;
import android.media.MediaPlayer;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

public class MainActivity extends AppCompatActivity {

    ImageButton mTorchOn;
    boolean mTorchOnFlag = false;
    String mCameraId;
    CameraManager mCameraManager;
    MediaPlayer mMediaPlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mTorchOn = findViewById(R.id.flash);
        mTorchOn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    mCameraManager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
                    mCameraId = mCameraManager.getCameraIdList()[0];

                    if (mTorchOnFlag) {
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                            mCameraManager.setTorchMode(mCameraId, false);
                            playOnOffSound();
                            mTorchOn.setImageResource(R.mipmap.flash_on);
                        }
                        mTorchOnFlag = false;
                    } else {
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                            mCameraManager.setTorchMode(mCameraId, true);
                            playOnOffSound();
                            mTorchOn.setImageResource(R.mipmap.flash_off);
                        }
                        mTorchOnFlag = true;
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
}
