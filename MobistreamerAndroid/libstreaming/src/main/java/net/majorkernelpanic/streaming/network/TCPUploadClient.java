package net.majorkernelpanic.streaming.network;

import android.os.AsyncTask;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

/**
 * Created by alexander on 20.01.16.
 */
public class TCPUploadClient {

    public static String TAG = "TCPUploadClient";

    public String host;
    public int port;

    private TCPUploadClient.CallbackConnection callback;

    private static Socket socket = null;
    private static boolean isConnected = false;
    private OutputStream mOutputStream = null;
    private InputStream mInputStream = null;
    private BufferedReader mBufferedReader = null;

    public interface CallbackConnection{
        void connectedStream(boolean isConnect);
    }

    public TCPUploadClient(String host, int port) {
        this.host = host;
        this.port = port;
    }

    public void writeToBuffer(byte[] buffer) throws IOException{
        synchronized (mOutputStream) {
            if(isConnected){
//   			Log.d("TCPSEND", "Write to buffer: " + buffer.length);
//	    		Log.d("TCPSEND", byteArrayToHex(buffer));
                mOutputStream.write(buffer);
                mOutputStream.flush();
            }
        }
    }

    public void connect(TCPUploadClient.CallbackConnection cal){
        this.callback = cal;
        new CreateConnection(this.callback, this).execute();
    }

    public void closeConnection(){
        try{
            isConnected = false;
            if(mInputStream != null)
                mInputStream.close();
            if(mOutputStream != null)
                mOutputStream.close();
            if(mBufferedReader != null)
                mBufferedReader.close();
            if(socket != null)
                socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }finally{
            socket = null;
        }
    }

    public void run() throws IOException {
        InetAddress serverAddr = InetAddress.getByName(host);
        socket = new Socket(serverAddr, port);
        mOutputStream = socket.getOutputStream();
        mInputStream = socket.getInputStream();
        mBufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
    }

    private static class CreateConnection extends AsyncTask<Void, Void, Void> {

        CallbackConnection callback;
        TCPUploadClient client;

        public CreateConnection(CallbackConnection cal, TCPUploadClient cl) {
            callback = cal;
            client = cl;
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
            try {
                client.run();
                isConnected = true;
                Log.w(TAG, "Connected to host: " + client.host + ":" + client.port);
            } catch (IOException e) {
                Log.w(TAG, e.getMessage());
                isConnected = false;
            }
            return null;
        }
    }
}
