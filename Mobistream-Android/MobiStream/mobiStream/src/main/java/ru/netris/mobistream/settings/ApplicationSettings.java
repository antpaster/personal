package ru.netris.mobistream.settings;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.content.Context;
import android.content.SharedPreferences;
import android.util.Pair;

public class ApplicationSettings {

	public static final String APP_PREFERENCES = "mobistreamsettings";
	public static final String APP_PREFERENCES_SERVER = "server";
	public static final String APP_PREFERENCES_SERVER_PORT = "port";
	public static final String APP_PREFERENCES_LOGIN = "login";
	public static final String APP_PREFERENCES_PASSWORD = "password";
	
	public static final String APP_PREFERENCES_VIDEO_SIZE = "video_size";
	public static final String APP_PREFERENCES_BITRATE = "bitrate";
	public static final String APP_PREFERENCES_FRAME_RATE = "frame_rate";
	public static final String APP_PREFERENCES_KEY_FRAME_INTERVAL = "key_frame_interval";
	public static final String APP_PREFERENCES_VIDEO_AUDIO_STREAM = "video_audio_stream";
	
	private Map<String, Pair<Integer, Integer> > videoSizeMap;
	private List<String> videoSizeList;
	private Map<String, List<String> > videoBitrate;
	private List<String> videoStream;
	
	private String streamServer = "";
	private String streamLogin = "";
	private String streamPassword = "";

	private int streamPort = 0;
	private int streamFramerate = 0;
	private int streamKeyFrameInterval = 0;

	private int streamVideoAudioStreamIndex = 0;
	private int streamVideoSizeIndex = 0;
	private int streamBitrateIndex = 0;

	private Context context;
	private SharedPreferences mSettings;

	public ApplicationSettings(Context context) {
		this.context = context;
		init();
		loadSettings();
	}
	
	public void init(){
		
		videoSizeList = new ArrayList<String>();
		videoSizeList.add("1280x720");
		videoSizeList.add("640x480");
		videoSizeList.add("352x288");
		videoSizeList.add("320x240");

		
		videoSizeMap = new HashMap<String, Pair<Integer,Integer>>();
		videoSizeMap.put("1280x720", new Pair<Integer, Integer>(1280, 720));
		videoSizeMap.put("640x480", new Pair<Integer, Integer>(640, 480));
		videoSizeMap.put("352x288", new Pair<Integer, Integer>(352, 288));
		videoSizeMap.put("320x240", new Pair<Integer, Integer>(320, 240));
		
		videoBitrate = new HashMap<String, List<String>>();
		videoBitrate.put("1280x720",  Arrays.asList("1500", "2500", "3500","4500"));
		videoBitrate.put("640x480",  Arrays.asList("700", "1500", "2500", "3500"));
		videoBitrate.put("352x288",  Arrays.asList("140","280","560","700"));
		videoBitrate.put("320x240",  Arrays.asList("140","280","560","700"));
		
		videoStream = new ArrayList<String>();
		videoStream.add("Видео+Звук");
		videoStream.add("Только видео");
		videoStream.add("Только звук");
	}

	public String[] getVideoSizeTitles(){
		return (String[]) videoSizeList.toArray(new String[videoSizeList.size()]);
	}

	public String[] getVideoStreamModes(){
		return (String[]) videoStream.toArray(new String[videoStream.size()]);
	}
	
	public List<String> getVideoBitrates(){
		//return videoBitrate.get(videoSizeMap.keySet().toArray()[this.streamVideoSizeIndex]);
		return videoBitrate.get(videoSizeList.get(streamVideoSizeIndex));
	}

	public void loadSettings(){
		mSettings = this.context.getSharedPreferences(APP_PREFERENCES, Context.MODE_PRIVATE);
		streamServer = mSettings.getString(APP_PREFERENCES_SERVER, "");
		streamPort = mSettings.getInt(APP_PREFERENCES_SERVER_PORT, 30300);
		streamLogin = mSettings.getString(APP_PREFERENCES_LOGIN, "");
		streamPassword = mSettings.getString(APP_PREFERENCES_PASSWORD, "");
		streamVideoSizeIndex = mSettings.getInt(APP_PREFERENCES_VIDEO_SIZE, 0);
		streamBitrateIndex = mSettings.getInt(APP_PREFERENCES_BITRATE, 0);
		streamFramerate = mSettings.getInt(APP_PREFERENCES_FRAME_RATE, 30);
		streamKeyFrameInterval = mSettings.getInt(APP_PREFERENCES_KEY_FRAME_INTERVAL, 2);
		streamVideoAudioStreamIndex = mSettings.getInt(APP_PREFERENCES_VIDEO_AUDIO_STREAM, 0);
	}

	public String getStreamServer() {
		return streamServer;
	}

	public void setStreamServer(String streamServer) {
		this.streamServer = streamServer;
		SharedPreferences.Editor editor = mSettings.edit();
		editor.putString(APP_PREFERENCES_SERVER, this.streamServer);
		editor.commit();
	}

	public int getStreamPort() {
		return streamPort;
	}

	public void setStreamPort(int streamPort) {
		this.streamPort = streamPort;
		SharedPreferences.Editor editor = mSettings.edit();
		editor.putInt(APP_PREFERENCES_SERVER_PORT, this.streamPort);
		editor.commit();
	}

	public String getStreamLogin() {
		return streamLogin;
	}

	public void setStreamLogin(String streamLogin) {
		this.streamLogin = streamLogin;
		SharedPreferences.Editor editor = mSettings.edit();
		editor.putString(APP_PREFERENCES_LOGIN, this.streamLogin);
		editor.commit();
	}

	public String getStreamPassword() {
		return streamPassword;
	}

	public void setStreamPassword(String streamPassword) {
		this.streamPassword = streamPassword;
		SharedPreferences.Editor editor = mSettings.edit();
		editor.putString(APP_PREFERENCES_PASSWORD, this.streamPassword);
		editor.commit();
	}

	public int getStreamVideoSizeIndex() {
		return streamVideoSizeIndex;
	}

	public void setStreamVideoSizeIndex(int streamVideoSize) {
		this.streamVideoSizeIndex = streamVideoSize;
		SharedPreferences.Editor editor = mSettings.edit();
		editor.putInt(APP_PREFERENCES_VIDEO_SIZE, this.streamVideoSizeIndex);
		editor.commit();
		//reset bitrate to maximum
		setStreamBitrateIndex(getVideoBitrates().size()-1);
	}

	public int getStreamBitrateIndex() {
		return streamBitrateIndex;
	}

	public void setStreamBitrateIndex(int streamBitrate) {
		this.streamBitrateIndex = streamBitrate;
		SharedPreferences.Editor editor = mSettings.edit();
		editor.putInt(APP_PREFERENCES_BITRATE, this.streamBitrateIndex);
		editor.commit();
	}

	public int getStreamFramerate() {
		return streamFramerate;
	}

	public void setStreamFramerate(int streamFramerate) {
		this.streamFramerate = streamFramerate;
		SharedPreferences.Editor editor = mSettings.edit();
		editor.putInt(APP_PREFERENCES_FRAME_RATE, this.streamFramerate);
		editor.commit();
	}

	public int getStreamKeyFrameInterval() {
		return streamKeyFrameInterval;
	}

	public void setStreamKeyFrameInterval(int streamKeyFrameInterval) {
		this.streamKeyFrameInterval = streamKeyFrameInterval;
		SharedPreferences.Editor editor = mSettings.edit();
		editor.putInt(APP_PREFERENCES_KEY_FRAME_INTERVAL, this.streamKeyFrameInterval);
		editor.commit();
	}

	public int getStreamVideoAudioStreamIndex() {
		return streamVideoAudioStreamIndex;
	}

	public void setStreamVideoAudioStreamIndex(int streamVideoAudioStream) {
		this.streamVideoAudioStreamIndex = streamVideoAudioStream;
		SharedPreferences.Editor editor = mSettings.edit();
		editor.putInt(APP_PREFERENCES_VIDEO_AUDIO_STREAM, this.streamVideoAudioStreamIndex);
		editor.commit();
	}
	
	// 0 - Video+Audio
	// 1 - Only Video
	// 2 - Only Audio
	public boolean isAudioRecord(){
		switch(streamVideoAudioStreamIndex){
			case 0: return true;
			case 1: return false;
			case 2: return true;
		}
		return false;
	}
	
	// 0 - Video+Audio
	// 1 - Only Video
	// 2 - Only Audio
	public boolean isVideoRecord(){
		switch(streamVideoAudioStreamIndex){
			case 0: return true;
			case 1: return true;
			case 2: return false;
		}
		return false;
	}
	
	public int getVideoWidth(){
		return videoSizeMap.get(videoSizeList.get(streamVideoSizeIndex)).first;
	}
	
	public int getVideoHeight(){
		return videoSizeMap.get(videoSizeList.get(streamVideoSizeIndex)).second;
	}
	
	public int getVideoBitrate(){
		return Integer.valueOf(videoBitrate.get(videoSizeList.get(streamVideoSizeIndex)).get(streamBitrateIndex));
	}
}
