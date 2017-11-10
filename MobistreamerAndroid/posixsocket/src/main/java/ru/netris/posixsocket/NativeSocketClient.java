package ru.netris.posixsocket;

import android.os.AsyncTask;
import android.util.Log;

/**
 * Created by ps on 29.08.17.
 */

public class NativeSocketClient {

    static {
        System.loadLibrary("SenderSocket");
    }

    public static String TAG = "TCPNativeClient";

    private static boolean isConnected = false;
    public static String HOST = "";
    public static int PORT = 2032;

    private static NativeSocketClient tcpClient = null;
    private NativeSocketClient.CallbackConnection callback;

    public SenderSocket socket;

    public interface CallbackConnection{
        void connectedStream(boolean isConnect);
    }

    public static NativeSocketClient getInstance(){
        if(null == tcpClient){
            Log.d(TAG, "Create NativeSocketClient");
            tcpClient = new NativeSocketClient();
        }
        return tcpClient;
    }

    public boolean isConnected(){
        return isConnected;
    }

    public synchronized int writeToBuffer(byte [] buffer){
        int res = 0;
        if(isConnected) {
            res = socket.sendToHost(buffer);
            if (res == -1) {
                Log.d(TAG, "Connection closed! Send error!");
                closeConnection();
            }
        }
        return res;
    }

    public synchronized int readFromBuffer(byte [] buffer){
        int res = 0;
        if(isConnected) {
            res = socket.readFromHost(buffer);
            if (res == -1) {
                Log.d(TAG, "Connection closed! Send error!");
                closeConnection();
            }else {
            }
        }
        return res;
    }

    public synchronized void connect(NativeSocketClient.CallbackConnection callback){
        this.callback = callback;
        new CreateConnection(this.callback).execute();
    }

    public void closeConnection(){
        socket.closeSocket();
        isConnected = false;
        callback.connectedStream(isConnected);
    }

    public boolean createConnection(){
        socket = new SenderSocket();
        Log.e(TAG, "Connection PORT: " + PORT);
        boolean result = socket.connectToHost(HOST, PORT);
        return result;
    }

    private static class CreateConnection extends AsyncTask<Void, Void, Void> {

        CallbackConnection callback;
        public CreateConnection(CallbackConnection cal) {
            callback = cal;
        }

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
        }

        @Override
        protected void onPostExecute(Void result) {
            callback.connectedStream(isConnected);
            super.onPostExecute(result);
        }

        @Override
        protected Void doInBackground(Void... asd) {
            isConnected = tcpClient.createConnection();
            if(isConnected) {
                Log.w(TAG, "Connected to host: " + HOST + ":" + PORT);
            }else{
                Log.w(TAG, "Errno: " + tcpClient.writeToBuffer(null));
                Log.w(TAG, "Not Connected to host: " + HOST + ":" + PORT);
            }
            return null;
        }
    }
}
