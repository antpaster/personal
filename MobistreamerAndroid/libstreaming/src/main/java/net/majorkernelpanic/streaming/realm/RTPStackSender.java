package net.majorkernelpanic.streaming.realm;

import android.content.Context;
import android.util.Log;

import net.majorkernelpanic.streaming.network.TCPClient;

import java.io.IOException;

/**
 * Created by alexander on 14.01.16.
 */
public class RTPStackSender implements Runnable {

    public static String TAG = "RTPStackSender";

    public static long lastSended = -1;
    public boolean isRun = false;

    private Thread t = null;

    public Context context;

    public RTPStackStorage storage;

    public void start(Context con){

        context = con;
//        storage.startSend();
        if (t==null) {
            t = new Thread(this);
            t.start();
            isRun = true;
            Log.d(TAG, "Thread started.");
        }
    }

    public void stop(){
        if (t != null) {
            //try {
                //is.close();
            //} catch (IOException ignore) {}
            t.interrupt();
            try {
                t.join();
            } catch (InterruptedException e) {}
            t = null;
            isRun = false;
            storage.close();
            Log.d(TAG, "Thread stoped.");
        }
    }

    public boolean isInterrupted(){
        return Thread.interrupted();
    }

    @Override
    public void run() {
//        try {
            if (storage == null) {
  //              Log.d(TAG, "RTPStackStorage(context);");
                storage = new RTPStackStorage(context);
            }
//            Log.d(TAG, "Run function called.");
            while (!Thread.interrupted()) {
                RTPStackItem item = null;
                if(lastSended == -1) {
  //                  Log.d(TAG, "lastSended is -1");
//                    item = RTPStackStorage.getInstance().getLastPacket();
                    item = storage.getLastPacket();
                }else{
//                    if(RTPStackStorage.getInstance().hasNext(lastSended)) {
                    if(storage.hasNext(lastSended)) {
 //                       Log.d(TAG, "RTPStackStorage.getInstance().hasNext(lastSended).");
//                        item = RTPStackStorage.getInstance().getPacket(lastSended + 1);
                        item = storage.getPacket(lastSended + 1);
                    }else{
  //                      Log.d(TAG, "NOT hasNext(lastSended).");
                        item = null;
                    }
                }
                if(item != null) {
                    if(send(item.getRtpData())){
                        lastSended = item.getRtpNumber();
//                        RTPStackStorage.getInstance().deletePacket(item);
                        storage.deletePacket(item);
  //                      Log.d(TAG, "Packet sent. lastSended = " + lastSended + ". Packet deleted.");
                    }else{
  //                      Log.e(TAG, "не шмогла отправить");
                        // если не шмогла отправить?
                        //item = RTPStackStorage.getInstance().getLastPacket();
                    }
                }else{
                    try {
                        Log.d(TAG, "Sleep thread!!!");
                        Thread.sleep(80);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
//        } catch (IOException e) {
//        } catch (InterruptedException e) {}
    }

    public boolean send(byte [] data) {
        boolean res = true;
        try {
            TCPClient.getInstance().writeToBuffer(data);
        } catch (IOException e) {
            Log.e(TAG, "Send error!" + e.getMessage() );
            //e.printStackTrace();
        }
        return res;
    }
}
