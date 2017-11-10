package ru.netris.mobistreamer.modules.video.activity;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.AlertDialog;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.graphics.SurfaceTexture;
import android.os.Bundle;
import android.os.IBinder;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.TextureView;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

import ru.netris.mobistreamer.modules.video.camera.CameraService;
import ru.netris.mobistreamer.MobistreamService;
import ru.netris.mobistreamer.R;
import ru.netris.mobistreamer.modules.login.network.PortalConnection;

public class Camera2Activity extends Activity {

    public static final String TAG = "Camera2Activity";

    private MobistreamService mobistreamService;
    private AutoFitTextureView mTextureView;
    private Integer mSensorOrientation;

    private ImageButton recordButton;
    private ImageButton closeButton;
    private ImageButton switchButton;
    private ImageButton torchButton;
    private ImageButton settingsButton;

    private TextureView.SurfaceTextureListener mSurfaceTextureListener = new TextureView.SurfaceTextureListener() {

        @Override
        public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture, int width, int height) {
//            openCamera(width, height);
//            mobistreamService.cameraService.setPreview(mTextureView);
//            mobistreamService.cameraService.startPreview();
            Log.d(TAG, "onSurfaceTextureAvailable(SurfaceTexture surfaceTexture, int width, int height) {");
            if (mobistreamService != null) {
                mBinder.setPreview(mTextureView);

                mobistreamService.cameraService.updatePreview();
                mobistreamService.cameraService.configureTransform(mTextureView.getWidth(),mTextureView.getHeight());
                mBinder.startPreview();
            }
        }

        @Override
        public void onSurfaceTextureSizeChanged(SurfaceTexture surfaceTexture, int width, int height) {
            Log.d(TAG, "onSurfaceTextureSizeChanged(SurfaceTexture surfaceTexture, int width, int height)");
            if (mobistreamService != null) {
                mobistreamService.cameraService.configureTransform(width,height);
            }
//            configureTransform(width, height);
        }

        @Override
        public boolean onSurfaceTextureDestroyed(SurfaceTexture surfaceTexture) {
            return true;
        }

        @Override
        public void onSurfaceTextureUpdated(SurfaceTexture surfaceTexture) {
        }

    };

    private void bindService() {
        Log.d(TAG, "bindService");
        bindService(new Intent(getApplication(), MobistreamService.class), mobistreamServiceConnection, Context.BIND_AUTO_CREATE);
    }

    private void unbindService() {
        Log.d(TAG, "unbindService");
        unbindService(mobistreamServiceConnection);
    }

    MobistreamService.LocalBinder mBinder = null;

    ServiceConnection mobistreamServiceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
            mBinder = (MobistreamService.LocalBinder)iBinder;
            Log.d(TAG, "mobistreamServiceConnection onServiceConnected");
            // устанавливаем превью если и серфейс создан и подключен
            //
            mobistreamService = ((MobistreamService.LocalBinder)iBinder).getService();
            mobistreamService.addCallbackListener(serviceListener);

            mBinder.setPreview(mTextureView);

            mobistreamService.cameraService.updatePreview();
            mobistreamService.cameraService.configureTransform(mTextureView.getWidth(),mTextureView.getHeight());
            mBinder.startPreview();
//            mobistreamService.cameraService.setPreview(mTextureView);
//            mobistreamService.cameraService.startPreview();
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            Log.d(TAG, "mobistreamServiceConnection onServiceDisconnected");
        }
    };

    public MobistreamService.CallbackListener serviceListener = new MobistreamService.CallbackListener() {
        @Override
        public void onError(MobistreamService service, Exception e, int error) {
            Log.d(TAG, "MobistreamService.CallbackListener onError: " + error + " " + e.getLocalizedMessage());
        }

        @Override
        public void onMessage(MobistreamService service, int message) {
            Log.d(TAG, "MobistreamService.CallbackListener onMessage: " + message);
        }

        @Override
        public void onDeviceOpen() {
            Log.d(TAG, "onDeviceOpen()");

            if (mobistreamService != null) {
                mBinder.setPreview(mTextureView);

                mobistreamService.cameraService.updatePreview();
                mobistreamService.cameraService.configureTransform(mTextureView.getWidth(),mTextureView.getHeight());
                mBinder.startPreview();
            }
            if(mTextureView.isAvailable()) {
//                mBinder.setPreview(mTextureView);
//                mBinder.startPreview();
//                mobistreamService.cameraService.configureTransform(mTextureView.getWidth(), mTextureView.getHeight());
//                mobistreamService.cameraService.updatePreview();
            }else{
                mTextureView.setSurfaceTextureListener(mSurfaceTextureListener);
            }
        }

        @Override
        public void onRecording(final boolean recording) {
            isRecord = recording;
            if(recording) {
                runOnUiThread(new Runnable() {
                    public void run() {
                        Log.d(TAG, "recordButton.setImageResource(R.drawable.mobistream_pause)");
                        recordButton.setImageResource(R.drawable.mobistream_pause);
                    }
                });
            }else{
                runOnUiThread(new Runnable() {
                    public void run() {
                        Log.d(TAG, "recordButton.setImageResource(R.drawable.mobistream_play)");
                        recordButton.setImageResource(R.drawable.mobistream_play);
                    }
                });
            }
        }
    };

    public boolean check(){
        ActivityManager manager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
        for (ActivityManager.RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE))
        {
            if ("ru.netris.mobistreamer.MobistreamService"
                    .equals(service.service.getClassName()))
            {
                return true;
            }
        }
        return false;
    }

    public boolean isRecord = false;
    public static PortalConnection.ServerSettings staticSettings = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera2);

        Log.d(TAG, "onCreate");

        CameraService.activity = this;


        Intent intent = getIntent();
        PortalConnection.ServerSettings set = (PortalConnection.ServerSettings) intent.getParcelableExtra("Settings");
        if(set != null) {
            staticSettings = set;
            Log.d(TAG, "" + set.geohost);
            Log.d(TAG, "" + set.geoip);
            Log.d(TAG, "" + set.host);
            Log.d(TAG, "" + set.ip);
            Log.d(TAG, "" + set.stream);
            Log.d(TAG, "" + set.imei);
            Log.d(TAG, "" + set.live);
        }else{
            set = staticSettings;
        }




        mTextureView = (AutoFitTextureView) findViewById(R.id.texture);
        recordButton = (ImageButton) findViewById(R.id.recordButton);
        recordButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(isRecord) {
                    mobistreamService.cameraService.stopRecord();
                }else {
                    mobistreamService.cameraService.startRecord();
                }
            }
        });

        closeButton = (ImageButton) findViewById(R.id.closeButton);
        closeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AlertDialog alertDialog = new AlertDialog.Builder(Camera2Activity.this).create();
                alertDialog.setTitle("Закрыть приложение?");
                alertDialog.setMessage("Приложение будет полностью завершено.");
                alertDialog.setButton(AlertDialog.BUTTON_POSITIVE, "Закрыть",
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int which) {
                                stopService(new Intent(getApplicationContext(), MobistreamService.class));
                                finishAffinity();
                            }
                        });
                alertDialog.setButton(AlertDialog.BUTTON_NEUTRAL, "Отменить",
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int which) {
                                dialog.dismiss();
                            }
                        });
                alertDialog.show();
            }
        });
        switchButton = (ImageButton) findViewById(R.id.switchCameraButton);
        switchButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                if (mTextureView.isAvailable()) {
//                    openCamera(mTextureView.getWidth(), mTextureView.getHeight());
//                } else {
//                    mTextureView.setSurfaceTextureListener(mSurfaceTextureListener);
//                }
                mobistreamService.cameraService.switchCamera();
            }
        });
        torchButton = (ImageButton) findViewById(R.id.torchButton);
        torchButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mobistreamService.cameraService.isTorchOn()) {
                    mobistreamService.cameraService.turnOffFlashLight();
                }else{
                    mobistreamService.cameraService.turnOnFlashLight();
                }
            }
        });

        settingsButton = (ImageButton) findViewById(R.id.settingsButton);
        settingsButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(isRecord) {
                    Toast.makeText(getApplicationContext(), "Остановите видео!", Toast.LENGTH_LONG);
                }else {
                    Intent intent = new Intent(getApplicationContext(), Settings2Activity.class);
                    startActivity(intent);
                }
            }
        });

        startService(new Intent(getApplicationContext(), MobistreamService.class));

        loadSettings();

    }

    public void loadSettings() {
        SharedPreferences sharedPref = PreferenceManager.getDefaultSharedPreferences(this);
        String videoStream = sharedPref.getString("video_stream", "нихуя");
        String videoBitrate = sharedPref.getString("video_bitrate", "2");
        String videoSize = sharedPref.getString("video_size", "нихуя");

        Log.d(TAG, "size: " + videoSize + " bitrate: " + videoBitrate + " stream: " + videoStream);
    }

    public void saveSettings(String size, String bitrate, String stream) {

        SharedPreferences sharedPref = PreferenceManager.getDefaultSharedPreferences(this);
        sharedPref.edit().putString("video_stream", stream).apply(); //commit
        sharedPref.edit().putString("video_bitrate", bitrate).apply();
        sharedPref.edit().putString("video_size", size).apply();

    }

//    @Override
//    protected void onStart() {
//        super.onStart();
//
//    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.d(TAG, "onStop");
        // Unbind from the service
//        if (mBound) {
//            unbindService(mConnection);
//            mBound = false;
//        }



        if (mobistreamService != null){
            mobistreamService.removeCallbackListener(serviceListener);
            unbindService();
        }

    }


    @Override
    protected void onResume() {
        super.onResume();
        bindService();
        Log.d(TAG, "onResume");



        if (mTextureView.isAvailable()) {
//            mBinder.startPreview();
//            mobistreamService
//            openCamera(mTextureView.getWidth(), mTextureView.getHeight());
        } else {
            mTextureView.setSurfaceTextureListener(mSurfaceTextureListener);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.d(TAG, "onPause");

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "onDestroy");
    }

    @Override
    public void onBackPressed() {
//        super.onBackPressed();
    }

    public void setupInteface() {

    }
}
