package net.majorkernelpanic.streaming.realm;

import android.content.Context;
import android.util.Log;

/**
 * Created by alexander on 20.01.16.
 */
public class RTPStackUploader implements Runnable {

    public static String TAG = "RTPStackUploader";

    public boolean isRun = false;

    private Thread t = null;

    public RTPStackUploader(){

    }

    public void start(){
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
            Log.d(TAG, "Thread stoped.");
        }
    }

    public boolean isInterrupted(){
        return Thread.interrupted();
    }

    @Override
    public void run() {
        while (!Thread.interrupted()) {

        }
        isRun = false;
    }
}
