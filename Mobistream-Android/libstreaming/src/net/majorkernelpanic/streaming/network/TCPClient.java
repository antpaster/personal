package net.majorkernelpanic.streaming.network;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

import android.os.AsyncTask;
import android.util.Log;

public class TCPClient {

	public static final int STATUS_DISCONNECTED = 0;// подключаемся
	public static final int STATUS_CONNECTED = 1;// подключено

	private static Socket socket = null;
	private static boolean isConnected = false;
//	public static String SERVER = "pnp.netris.ru";
	public static String SERVER = "172.16.1.66";
	public static int PORT = 2032;

	private static TCPClient tcpClient = null;
		
	private OutputStream mOutputStream = null;
	private InputStream mInputStream = null;
	private BufferedReader mBufferedReader = null;
	private TCPClient.CallbackConnection callback;

	public interface CallbackConnection{
		public void connectedStream(boolean isConnect);
	}
		
	private TCPClient(){
		
	}
	
	public static TCPClient getInstance(){
		if(null == tcpClient){
			tcpClient = new TCPClient();
		}
		return tcpClient;
	}
	
	public boolean isConnected(){
		return isConnected;
	}

	public synchronized void connect(TCPClient.CallbackConnection callback){
		this.callback = callback;
		new CreateConnection(this.callback).execute();
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

	public void writeToBuffer(byte[] headBuffer, byte[] bodyBuffer) throws IOException{
		synchronized (mOutputStream) {
			if(isConnected){
				mOutputStream.write(headBuffer);
				mOutputStream.write(bodyBuffer);
				mOutputStream.flush();
			}
		}
	}
	
	public int read(byte []buffer) throws IOException{
		return mInputStream.read(buffer);
	}
	
	public String readLine() throws IOException{
		return mBufferedReader.readLine();
	}
	
	public void writeToBuffer(byte[] buffer) throws IOException{
		synchronized (mOutputStream) {
			if(isConnected){
				mOutputStream.write(buffer);
				mOutputStream.flush();
			}
		}
	}
	
	public void writeToBuffer(byte[] buffer, int offset, int count) throws IOException{
		synchronized (mOutputStream) {
			if(isConnected){
				mOutputStream.write(buffer, offset, count);
				mOutputStream.flush();
			}
		}
	}
	
	public void writeToBuffer(byte[] head, byte[] buffer, int offset, int count) throws IOException{
		synchronized (mOutputStream) {
			if(isConnected){
				mOutputStream.write(head);
				mOutputStream.write(buffer, offset, count);
				mOutputStream.flush();
			}
		}
	}
	
	public void run() throws IOException{
		if(socket != null){
			closeConnection();
		}

		InetAddress serverAddr = InetAddress.getByName(SERVER);
		socket = new Socket(serverAddr, PORT);
		mOutputStream = socket.getOutputStream();
		mInputStream = socket.getInputStream();
		mBufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
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
			try {
				tcpClient.run();
				isConnected = true;
			} catch (IOException e) {
				Log.w("TCPClient", e.getMessage());
				isConnected = false;
			}
			return null;
		}
	}

	public BufferedReader getBufferedReader() {
		return mBufferedReader;
	}

}
