package ru.netris.mobistream.settings;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;

import ru.netris.mobistream.R;

public class ApplicationPropertiesMenu {

    public final static String OPTIONS_STRING = "Настройки";
    public final static String DONE_STRING = "Закрыть";
    public final static String BITRATE_STRING = "Битрейт";

	private EditText editTextServer;
	private EditText editTextPort;
	private EditText editTextLogin;
	private EditText editTextPassword;
	private EditText fpsEdit;
	private EditText keyFrameEdit;
	 
	private Activity activity;
	private ApplicationSettings settings;

	public ApplicationPropertiesMenu(Activity activity, ApplicationSettings settings) {
		this.activity = activity;
		this.settings = settings;
	}
	
    public void showOptions(){
    	//CharSequence[] names = {"Server", "Video", "Stream", "Bitrate"};
        CharSequence[] names = {"Сервер", "Видео", "Поток", "Битрейт"};
		AlertDialog.Builder builder = new AlertDialog.Builder(activity);
	    builder.setTitle("Настройки").setItems(names, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				if(id==0){
					showServerOptions();
				}else if(id == 1){
					showVideoOptions();
				}else if(id == 2){
					showStreamOptions();
				}else if(id == 3){
					showBitrateOptions();
				}
			}
		}).setNegativeButton(DONE_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				
			}
		}).show();
    }

    public void showServerOptions(){
    	AlertDialog.Builder builder = new AlertDialog.Builder(activity);
		LayoutInflater inflater = activity.getLayoutInflater();
		View view = inflater.inflate(R.layout.options_server, null);
	
		editTextServer = (EditText) view.findViewById(R.id.server);
		editTextPort = (EditText) view.findViewById(R.id.port);
	    editTextLogin = (EditText) view.findViewById(R.id.login);
	    editTextPassword = (EditText) view.findViewById(R.id.password);

//		editTextServer.setOnEditorActionListener(new TextView.OnEditorActionListener() {
//			
//			@Override
//			public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
//				
//				//Log.w("11111111111111111", "22222222222222");
//				
//				if(actionId == EditorInfo.IME_ACTION_DONE || actionId == EditorInfo.IME_ACTION_GO || actionId == EditorInfo.IME_ACTION_NEXT ) {
//		            settings.setStreamServer(v.getText().toString());
//					
//		            Log.w("11111111111111111", v.getText().toString());
//		            
//		            return true;
//				}
//				return false;
//			}
//		});
		editTextServer.addTextChangedListener(new TextWatcher() {
	        @Override
	        public void afterTextChanged(Editable s) {
	            settings.setStreamServer(s.toString());
	        }
			@Override
			public void beforeTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
			@Override
			public void onTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
	    });
		editTextServer.setText(settings.getStreamServer());

		editTextPort.addTextChangedListener(new TextWatcher() {
	        @Override
	        public void afterTextChanged(Editable s) {
	        	if(!s.toString().equals(""))
	        		settings.setStreamPort(Integer.valueOf(s.toString()));
	        	else
	        		settings.setStreamPort(0);
	        }
			@Override
			public void beforeTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
			@Override
			public void onTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
	    });
		editTextPort.setText(String.valueOf(settings.getStreamPort()));
	    
		editTextLogin.addTextChangedListener(new TextWatcher() {
	        @Override
	        public void afterTextChanged(Editable s) {
	            settings.setStreamLogin(s.toString());
	        }
			@Override
			public void beforeTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
			@Override
			public void onTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
	    });
		editTextLogin.setText(settings.getStreamLogin());
	    
		editTextPassword.addTextChangedListener(new TextWatcher() {
	        @Override
	        public void afterTextChanged(Editable s) {
	            settings.setStreamPassword(s.toString());
	        }
			@Override
			public void beforeTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
			@Override
			public void onTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
	    });
		editTextPassword.setText(settings.getStreamPassword());
	
	    builder.setTitle("Настройки сервера").setView(view).
	    setPositiveButton(OPTIONS_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				showOptions();
			}
		}).setNegativeButton(DONE_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				
			}
		}).show();    	
    }
    
    public void showVideoSizeOptions(){
    	AlertDialog.Builder builder = new AlertDialog.Builder(this.activity);
	    builder.setTitle("Размер видео").setSingleChoiceItems(settings.getVideoSizeTitles(), settings.getStreamVideoSizeIndex(), new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				settings.setStreamVideoSizeIndex(id);
			}
		}).setPositiveButton(BITRATE_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				showBitrateOptions();
			}
		}).setNegativeButton(DONE_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				
			}
		}).show();
    }
    
    public void showStreamOptions(){
    	AlertDialog.Builder builder = new AlertDialog.Builder(this.activity);
	    builder.setTitle("Настройки потока").setSingleChoiceItems(settings.getVideoStreamModes(), settings.getStreamVideoAudioStreamIndex(), new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				settings.setStreamVideoAudioStreamIndex(id);
			}
		}).setPositiveButton(OPTIONS_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				showOptions();
			}
		}).setNegativeButton(DONE_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				
			}
		}).show();
    }

    public void showVideoOptions(){
    	AlertDialog.Builder builder = new AlertDialog.Builder(activity);
		LayoutInflater inflater = activity.getLayoutInflater();
		View view = inflater.inflate(R.layout.options_video, null);
	
		fpsEdit = (EditText) view.findViewById(R.id.fps);
		keyFrameEdit = (EditText) view.findViewById(R.id.keyframeinterval);

		fpsEdit.addTextChangedListener(new TextWatcher() {
	        @Override
	        public void afterTextChanged(Editable s) {
	            settings.setStreamFramerate(Integer.valueOf(s.toString()));
	        }
			@Override
			public void beforeTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
			@Override
			public void onTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
	    });
		fpsEdit.setText(String.valueOf(settings.getStreamFramerate()));

		
		keyFrameEdit.addTextChangedListener(new TextWatcher() {
	        @Override
	        public void afterTextChanged(Editable s) {
	            settings.setStreamKeyFrameInterval(Integer.valueOf(s.toString()));
	        }
			@Override
			public void beforeTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
			@Override
			public void onTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
	    });
		keyFrameEdit.setText(String.valueOf(settings.getStreamKeyFrameInterval()));
		
	    builder.setTitle("Настройки видео").setView(view)
		.setPositiveButton(OPTIONS_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				showOptions();
			}
		}).setNegativeButton(DONE_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				
			}
		}).show();    	
    }


    public void showBitrateOptions(){
    	AlertDialog.Builder builder = new AlertDialog.Builder(this.activity);
    	List<CharSequence> list = new ArrayList<CharSequence>();
    	for (String charSequence : settings.getVideoBitrates()) {
			list.add(charSequence);
		}   	
    	CharSequence[] array = list.toArray(new CharSequence[list.size()]);
    	builder.setTitle("Битрейт").setSingleChoiceItems(array , settings.getStreamBitrateIndex(), new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				settings.setStreamBitrateIndex(id);
			}
		}).setPositiveButton(OPTIONS_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				showOptions();
			}
		}).setNegativeButton(DONE_STRING, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface arg0, int id) {
				
			}
		}).show();
    }
}
