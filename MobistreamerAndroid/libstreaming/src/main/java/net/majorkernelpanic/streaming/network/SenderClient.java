package net.majorkernelpanic.streaming.network;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;

import net.majorkernelpanic.streaming.realm.RTPStackStorage;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

public class SenderClient {

	public static SenderClient tcpClient;
	public Context context;
	public RTPStackStorage storage;

	private SenderClient(Context con){
		context = con;
		storage = new RTPStackStorage(context);
//		storage.startSend();
	}

	public static SenderClient getInstance(Context con){
		if(null == tcpClient){
			tcpClient = new SenderClient(con);
		}
		return tcpClient;
	}

	public boolean isConnected(){
		return true;
	}


	public void writeToBuffer(long ts, byte[] headBuffer, byte[] bodyBuffer) throws IOException{
		byte [] arr = new byte[headBuffer.length + bodyBuffer.length];


	}
	
	public void writeToBuffer(long ts, byte[] buffer) throws IOException{

//		RTPStackStorage.getInstance().pushPacket(ts,buffer);
		storage.pushPacket(ts,buffer);



//		synchronized (mOutputStream) {
//			if(isConnected){
//				mOutputStream.write(buffer);
//				mOutputStream.flush();
//			}
//		}
	}
	
	public void writeToBuffer(byte[] buffer, int offset, int count) throws IOException{
//		synchronized (mOutputStream) {
//			if(isConnected){
//				Log.d("TCPSEND", "Write to buffer");
//				mOutputStream.write(buffer, offset, count);
//				mOutputStream.flush();
//			}
//		}
	}

	public static String byteArrayToHex(byte[] a) {
		StringBuilder sb = new StringBuilder(a.length * 2);
		for(byte b: a)
			sb.append(String.format("%02x ", b & 0xff));
		return sb.toString();
	}

	public void writeToBuffer(byte[] head, byte[] buffer, int offset, int count) throws IOException{
//		synchronized (mOutputStream) {
//			if(isConnected){
//
//		//		Log.d("TCPSEND", byteArrayToHex(head));
//		//		Log.d("TCPSEND", byteArrayToHex(head) + byteArrayToHex(buffer));
//
//				mOutputStream.write(head);
//				mOutputStream.write(buffer, offset, count);
//				mOutputStream.flush();
//			}
//		}
	}

}
