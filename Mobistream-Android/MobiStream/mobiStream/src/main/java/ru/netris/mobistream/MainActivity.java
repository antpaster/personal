package ru.netris.mobistream;

import net.majorkernelpanic.streaming.network.TCPClient;
import net.majorkernelpanic.streaming.network.TCPClient.CallbackConnection;
import net.majorkernelpanic.streaming.MediaStream;
import net.majorkernelpanic.streaming.Session;
import net.majorkernelpanic.streaming.SessionBuilder;
import net.majorkernelpanic.streaming.audio.AudioQuality;
import net.majorkernelpanic.streaming.gl.SurfaceView;
import net.majorkernelpanic.streaming.rtsp.RtspClient;
import net.majorkernelpanic.streaming.video.VideoQuality;
import ru.netris.mobistream.R;
import android.app.Activity;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.hardware.Camera;
import android.hardware.Camera.CameraInfo;
import android.os.Bundle;
import android.os.PowerManager;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;
import ru.netris.mobistream.settings.ApplicationPropertiesMenu;
import ru.netris.mobistream.settings.ApplicationSettings;

public class MainActivity extends Activity implements RtspClient.Callback, Session.Callback,SurfaceHolder.Callback {
	
	private ImageView switchCameraButton;
	private ImageView lightButton;
	private ImageView settingsButton;
	private ImageView qualityButton;
	private ImageView recordButton;

    static public Camera camera;
    
    private final String TAG = "VideoServer";
	
	private PowerManager.WakeLock wl;
	private ApplicationPropertiesMenu propertyMenu;
	private ApplicationSettings appSettings;
	
	private SurfaceView mSurfaceView;
	
	private TextView mTextBitrate;
	private ProgressBar mProgressBar;
	private Session mSession;
	private RtspClient mClient;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		setContentView(R.layout.activity_main);
		
		appSettings = new ApplicationSettings(this);
    	propertyMenu = new ApplicationPropertiesMenu(this, appSettings);
    	TCPClient.SERVER = appSettings.getStreamServer();
		TCPClient.PORT = appSettings.getStreamPort();
		
		PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
        wl = pm.newWakeLock(PowerManager.FULL_WAKE_LOCK, "My Tag");
        wl.acquire();
		mProgressBar = (ProgressBar) findViewById(R.id.progress_bar);
		mTextBitrate = (TextView) findViewById(R.id.bitrate);

		mSurfaceView = (SurfaceView) findViewById(R.id.surface);
        recordButton = (ImageView) findViewById(R.id.recordVideo);
        recordButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				toggleStream();
			}
		});

    	switchCameraButton = (ImageView) findViewById(R.id.recordBack);
    	switchCameraButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				mSession.switchCamera();
			}
    	});

    	lightButton = (ImageView) findViewById(R.id.recordLight);
    	lightButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				if (lightButton.getTag().equals("on")) {
					lightButton.setTag("off");
					//lightButton.setImageResource(R.drawable.ic_flash_on_holo_light);
				} else {
					//lightButton.setImageResource(R.drawable.ic_flash_off_holo_light);
					lightButton.setTag("on");
				}
				mSession.toggleFlash();
			}
    	});
    	lightButton.setTag("off");

    	settingsButton = (ImageView) findViewById(R.id.recordServer);
    	settingsButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				if(mClient.isStreaming()){
					Toast.makeText(MainActivity.this, "Для редактирования настроек остановите запись видео", Toast.LENGTH_LONG).show();
				}else{
					propertyMenu.showOptions();
				}
			}
    	});

    	qualityButton = (ImageView) findViewById(R.id.recordQuality);
    	qualityButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				if(mClient.isStreaming()){
					Toast.makeText(MainActivity.this, "Для редактирования настроек остановите запись видео", Toast.LENGTH_LONG).show();
				}else{
					propertyMenu.showVideoSizeOptions();
				}
			}
    	});

    	mSession = SessionBuilder.getInstance()
    			.setContext(getApplicationContext())
    			.setAudioEncoder(SessionBuilder.AUDIO_NONE)
    			.setAudioQuality(new AudioQuality(8000,16000))
    			.setVideoEncoder(SessionBuilder.VIDEO_H264)//MediaRecorder.VideoEncoder.H264
    			.setSurfaceView(mSurfaceView)
    			.setPreviewOrientation(0)
    			.setCallback(this)
    			.build();
    
    	mClient = new RtspClient(null);
    	mClient.setSession(mSession);
    	mClient.setCallback(this);

    	mSession.getVideoTrack().setStreamingMethod(MediaStream.MODE_MEDIARECORDER_API);
    	mSurfaceView.getHolder().addCallback(this);

    	selectQuality();
	}
	
	// Connects/disconnects to the RTSP server and starts/stops the stream
	public void toggleStream() {
		mProgressBar.setVisibility(View.VISIBLE);
		if (!mClient.isStreaming()) {
			TCPClient.getInstance().connect(new CallbackConnection() {
				@Override
				public void connectedStream(boolean isConnect) {
					if(isConnect){
					//	mClient.setCredentials(appSettings.getStreamLogin(), appSettings.getStreamPassword());
					//	mClient.setServerAddress(appSettings.getStreamServer(), appSettings.getStreamPort());
						selectQuality();
						mClient.startStream();
					}
				}
			});
		} else {
			mClient.stopStream();
			TCPClient.getInstance().closeConnection();
		}
	}
	
	
	private void selectQuality() {
		mSession.setVideoQuality(new VideoQuality(appSettings.getVideoWidth(), appSettings.getVideoHeight(), appSettings.getStreamFramerate(), appSettings.getVideoBitrate() * 1000));
		//Toast.makeText(this, , Toast.LENGTH_SHORT).show();
		Log.d(TAG, "Selected resolution: "+appSettings.getVideoWidth()+"x"+appSettings.getVideoHeight());
		Log.d(TAG, "Framerate: "+ appSettings.getStreamFramerate());
		Log.d(TAG, "Bitrate: "+ appSettings.getVideoBitrate());
	}
	
	private void enableUI() {
		recordButton.setEnabled(true);
		switchCameraButton.setEnabled(true);
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		mSession.startPreview();
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,	int height) {
	
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		mClient.stopStream();
	}

	@Override
	public void onBitrateUpdate(long bitrate) {
		mTextBitrate.setText(""+bitrate/1000+" kbps");
	}

	@Override
	public void onPreviewStarted() {
		if (mSession.getCamera() == CameraInfo.CAMERA_FACING_FRONT) {
			lightButton.setEnabled(false);
			lightButton.setTag("off");
			//lightButton.setImageResource(R.drawable.ic_flash_on_holo_light);
		}
		else {
			lightButton.setEnabled(true);
		}
	}

	@Override
	public void onSessionConfigured() {

	}

	@Override
	public void onSessionStarted() {
		enableUI();
		//recordButton.setImageResource();
		recordButton.setBackgroundResource(R.drawable.pause_big);
		mProgressBar.setVisibility(View.GONE);
	}
    
	@Override
	public void onSessionStopped() {
		enableUI();
		//recordButton.setImageResource(R.drawable.ic_switch_video);
		recordButton.setBackgroundResource(R.drawable.record_big);
		mProgressBar.setVisibility(View.GONE);
	}

	@Override
	public void onSessionError(int reason, int streamType, Exception e) {
		mProgressBar.setVisibility(View.GONE);
		switch (reason) {
		case Session.ERROR_CAMERA_ALREADY_IN_USE:
			break;
		case Session.ERROR_CAMERA_HAS_NO_FLASH:
			//lightButton.setImageResource(R.drawable.ic_flash_on_holo_light);
			lightButton.setTag("off");
			break;
		case Session.ERROR_INVALID_SURFACE:
			break;
		case Session.ERROR_STORAGE_NOT_READY:
			break;
		case Session.ERROR_CONFIGURATION_NOT_SUPPORTED:
			VideoQuality quality = mSession.getVideoTrack().getVideoQuality();
		//	logError("The following settings are not supported on this phone: "+
		//	quality.toString()+" "+
		//	"("+e.getMessage()+")");
	//		e.printStackTrace();
			return;
		case Session.ERROR_OTHER:
			break;
		}

		if (e != null) {
			//logError(e.getMessage());
			e.printStackTrace();
		}
	}

	@Override
	public void onRtspUpdate(int message, Exception e) {
		switch (message) {
		case RtspClient.ERROR_CONNECTION_FAILED:
		case RtspClient.ERROR_WRONG_CREDENTIALS:
			mProgressBar.setVisibility(View.GONE);
			enableUI();
			//logError(e.getMessage());
			e.printStackTrace();
			break;
		}
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		mClient.release();
		mSession.release();
		mSurfaceView.getHolder().removeCallback(this);
		wl.release();
	}
}
