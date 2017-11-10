package ru.netris.mobistreamer.modules.login.network;

import android.content.Context;
import android.os.AsyncTask;
import android.os.Parcel;
import android.os.Parcelable;
import android.util.Log;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.UnsupportedEncodingException;
import java.net.CookieHandler;
import java.net.CookieManager;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by ps on 05.09.17.
 */

public class PortalConnection {

    public static final int INPROGRES_STATUS = 0;
    public static final int NOTPROGRES_STATUS = 1;

    public static final String TAG = "PortalConnection";
    public static PortalConnection instance = null;

    public static PortalConnection getInstance() {
        if(instance == null) {
            instance = new PortalConnection();
        }
        return instance;
    }

    public interface PortalConnectionCallback {
        void onError(String message);
        void onSettings(ServerSettings settings);
        void onStatus(int status);
    }

    public List<PortalConnectionCallback> callbackList = new LinkedList<PortalConnectionCallback>();

    //////////////////////////////////////////////////////////////////////////////////////

    public static final String REQUEST_TAG = "LoginRequestTag";
    StringRequest stringRequest;
    RequestQueue mRequestQueue;
    String cookie = null;
    int echdInstance = 0;

    private void cancelRequests() {
        if (mRequestQueue != null) {
            mRequestQueue.cancelAll(REQUEST_TAG);
        }
    }

    public static final String HOST = "http://172.16.1.135:8370";

    Context context;

    public void cancelAuth() {
        cancelRequests();
    }

    public void auth(String login, String password, Context context, final PortalConnectionCallback callback) {
        this.context = context;
        CookieHandler.setDefault(new CookieManager());

        mRequestQueue = Volley.newRequestQueue(context);
        String url = HOST + "/mobile/auth?j_username=" + login + "&j_password=" + password + "&_spring_security_remember_me=true";

        callback.onStatus(INPROGRES_STATUS);
        stringRequest = new StringRequest(Request.Method.POST, url,  new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                try {
                    JSONObject obj = new JSONObject(response);
                    if(obj.getBoolean("success")) {
                        echdInstance = obj.getInt("instance");
                        requestSettings(callback);
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                    callback.onStatus(NOTPROGRES_STATUS);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                callback.onError(error.getMessage());
            }
        }){
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                return super.getParams();
            }

            @Override
            public Map<String, String> getHeaders() throws AuthFailureError {
                Map<String,String> params = new HashMap<String, String>();
                params.put("Content-Type","application/json");
                params.put("X-Requested-With","XMLHttpRequest");
                params.put("X-Auth-Source","NETRIS-MOBILE-STREAMER");
                return params;
            }
        };

        stringRequest.setTag(REQUEST_TAG);
        mRequestQueue.add(stringRequest);
    }

    //////////////////////////////////////////////////////////////////////////////////////

    public void addCallback(PortalConnectionCallback callback) {
        callbackList.add(callback);
    }

    public void removeCallback(PortalConnectionCallback callback) {
        callbackList.remove(callback);
    }

    public void removeAllCallbacks() {
        callbackList.clear();
    }

    public void requestSettings(final PortalConnectionCallback callback) {
//        String requestString = HOST + "/mobistream/static/recording/settings";
        String requestString = HOST + "/mobistream/recording/settings";
        StringRequest settingsRequest = new StringRequest(Request.Method.GET, requestString,  new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                try {
                    JSONObject obj = new JSONObject(response);
                    if(obj.getBoolean("success")) {
                        JSONObject settings = obj.getJSONObject("settings");
                        String login = settings.getString("login");
                        final String host = settings.getString("host");
                        String stream = settings.getString("stream");
                        String live = settings.getString("live");
                        String geohost = settings.getString("geohost");
                        String imei = settings.getString("imei");
                        int port = settings.getInt("port");
                        int geoport = settings.getInt("geoport");

                        ServerSettings serverSettings = new ServerSettings();
                        serverSettings.login = settings.getString("login");
                        serverSettings.host = settings.getString("host");
                        serverSettings.stream = settings.getString("stream");
                        serverSettings.live = settings.getString("live");
                        serverSettings.geohost = settings.getString("geohost");
                        serverSettings.imei = settings.getString("imei");
                        serverSettings.port = settings.getInt("port");
                        serverSettings.geoport = settings.getInt("geoport");

                        new HostToIpTask(serverSettings, new HostToIpTaskCallback() {
                            @Override
                            public void onResult(ServerSettings settings) {
                                callback.onSettings(settings);
                                startKeepAlive();
                            }
                            @Override
                            public void onError(String message) {
                                callback.onError(message);
                            }
                        }).execute(serverSettings.host, serverSettings.geohost);
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                    callback.onError("Ошибка обработки json настроек: " + e.getMessage());
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.d(TAG, error.getMessage());
                callback.onError(error.getMessage());
            }
        }){

        };
        settingsRequest.setTag(REQUEST_TAG);
        mRequestQueue.add(settingsRequest);
    }

    public static class ServerSettings implements Parcelable { //implements Serializable { //implements Parcelable {
        public String login;
        public String host;
        public String ip;
        public String stream;
        public String live;
        public String geohost;
        public String geoip;
        public String imei;
        public int port;
        public int geoport;

        public ServerSettings() {

        }

        protected ServerSettings(Parcel in) {
            login = in.readString();
            host = in.readString();
            ip = in.readString();
            stream = in.readString();
            live = in.readString();
            geohost = in.readString();
            geoip = in.readString();
            imei = in.readString();
            port = in.readInt();
            geoport = in.readInt();
        }

        public static final Creator<ServerSettings> CREATOR = new Creator<ServerSettings>() {
            @Override
            public ServerSettings createFromParcel(Parcel in) {
                return new ServerSettings(in);
            }

            @Override
            public ServerSettings[] newArray(int size) {
                return new ServerSettings[size];
            }
        };

        @Override
        public int describeContents() {
            return 0;
        }

        @Override
        public void writeToParcel(Parcel parcel, int i) {
            parcel.writeString(login);
            parcel.writeString(host);
            parcel.writeString(ip);
            parcel.writeString(stream);
            parcel.writeString(live);
            parcel.writeString(geohost);
            parcel.writeString(geoip);
            parcel.writeString(imei);
            parcel.writeInt(port);
            parcel.writeInt(geoport);
        }
    }

    interface  HostToIpTaskCallback {
        void onResult(ServerSettings settings);
        void onError(String message);
    }

    private class HostToIpTask extends AsyncTask<String, Integer, Boolean> {

        ServerSettings settings;
        HostToIpTaskCallback callback;

        public HostToIpTask(ServerSettings settings, HostToIpTaskCallback callback) {
            this.settings = settings;
            this.callback = callback;
        }

        protected Boolean doInBackground(String... urls) {
            try {
                if(urls.length > 0) {
                    InetAddress address = InetAddress.getByName(urls[0]);
                    settings.ip = address.getHostAddress();
                    if(urls.length > 1) {
                        InetAddress geoAddress = InetAddress.getByName(urls[1]);
                        settings.geoip = geoAddress.getHostAddress();
                    }
                    return true;
                }
            } catch (UnknownHostException e) {
                e.printStackTrace();
                callback.onError("UnknownHostException: неполучилось получить ip адрес");
            }
            return false;
        }

        protected void onPostExecute(Boolean result) {
            if(result) {
                callback.onResult(settings);
            }else{
                callback.onError("Проблемы с получением ip адреса сервера");
            }
        }
    }

    public Timer mTimer;
    public KeepAliveTimerTask keepAliveTimerTask;

    public void startKeepAlive() {

        if(null == context) {
            return;
        }

        if (mTimer != null) {
            mTimer.cancel();
        }

        mTimer = new Timer();
        keepAliveTimerTask = new KeepAliveTimerTask(echdInstance, this.context);
        mTimer.schedule(keepAliveTimerTask, 1000, 30000); //30000
    }

    public void stopKeepAlive() {
        if (mTimer != null) {
            mTimer.cancel();
        }
    }

    class KeepAliveTimerTask extends TimerTask {

        int instance;
        public static final String TIMER_REQUEST_TAG = "KeepAliveTimerTask";
        RequestQueue mTimerRequestQueue;
        Context context;

        public KeepAliveTimerTask(int instance, Context context) {
            this.instance = instance;
            this.context = context;
            mTimerRequestQueue = Volley.newRequestQueue(context);
        }

        @Override
        public void run() {
            String requestString = HOST + "/beat";
            StringRequest timerRequest = new StringRequest(Request.Method.GET, requestString,  new Response.Listener<String>() {
                @Override
                public void onResponse(String response) {
                    Log.d("Timer beat", response);
                }
            }, new Response.ErrorListener() {
                @Override
                public void onErrorResponse(VolleyError error) {
                    Log.d(TAG, error.getMessage());
                }
            }){
                @Override
                public Map<String, String> getHeaders() throws AuthFailureError {
                    Map<String,String> params = new HashMap<String, String>();
                    params.put("Content-Type","application/json");
                    params.put("X-Auth-Source","NETRIS-MOBILE-STREAMER");
                    return params;
                }

                @Override
                public String getBodyContentType() {
                    return "application/json; charset=utf-8";
                }

                @Override
                public byte[] getBody() throws AuthFailureError {
                    try {
                        JSONObject jsonBody = new JSONObject();
                        try {
                            jsonBody.put("instance", instance);
                            jsonBody.put("active", true);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        final String mRequestBody = jsonBody.toString();
                        return mRequestBody.getBytes("utf-8");
                    } catch (UnsupportedEncodingException uee) {
                        return null;
                    }
                }
            };
            timerRequest.setTag(TIMER_REQUEST_TAG);
            mTimerRequestQueue.add(timerRequest);
        }
    }
}

/*
//aa_asinenko/38c6iJbui3
 */
