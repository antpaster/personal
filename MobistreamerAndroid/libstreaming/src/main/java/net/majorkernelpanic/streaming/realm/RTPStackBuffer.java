package net.majorkernelpanic.streaming.realm;

import android.content.Context;
import android.util.Log;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ConcurrentLinkedQueue;

import io.realm.Realm;
import io.realm.RealmConfiguration;
import io.realm.RealmResults;
//import ru.netris.posixsockets.TCPNativeClient;

import ru.netris.posixsocket.NativeSocketClient;
//import ru.netris.nativesocket.java.NativeSocketClient;

/**
 * Created by alexander on 20.01.16.
 */
public class RTPStackBuffer {

    public static String TAG = "RTPStackBuffer";
    public static RTPStackSessionSettings sessionSettings;

    public List<RTPStackItem> list = new LinkedList<RTPStackItem>();
    public ConcurrentLinkedQueue<RTPStackItem> queue = new ConcurrentLinkedQueue<RTPStackItem>();
//    public PriorityQueue<RTPStackItem> queue;

    RTPBufferUploader uploader;

    public Context context;
    public final int maxBufferPacketsCount = 5000; // ~1300 байт в каждом

    public RTPStackBuffer(Context con) {
        context = con;
//        Comparator<RTPStackItem> comparator = new StringLengthComparator();
//        queue = new PriorityQueue<RTPStackItem>(maxBufferPacketsCount + 100, comparator);

        uploader = new RTPBufferUploader(queue);
        uploader.start();

    }

//    public class StringLengthComparator implements Comparator<RTPStackItem> {
//        @Override
//        public int compare(RTPStackItem lhs, RTPStackItem rhs) {
//            if (lhs.getRtpTimeStamp() < rhs.getRtpTimeStamp()) {
//                return -1;
//            }
//            if (lhs.getRtpTimeStamp() > rhs.getRtpTimeStamp()){
//                return 1;
//            }
//            return 0;
//        }
//    }

    public void stop(){
        uploader.stop();
    }

    public void pushPacket(final long timestamp, final byte [] data){

        Log.d("TESTTS", "" + timestamp);

        if(queue.size() >= maxBufferPacketsCount){
            flushBuffer();
        }
        RTPStackItem item = new RTPStackItem();
        item.setRtpTimeStamp(timestamp);
        item.setRtpData(data);
        item.setRtpSession(sessionSettings);
        synchronized (queue) {
            queue.add(item);
        }

        if(!uploader.isRun){
            uploader.start();
        }
    }

    public void flushBuffer(){

        ConcurrentLinkedQueue<RTPStackItem> temp = new ConcurrentLinkedQueue<RTPStackItem>();

        uploader.pauseUploader();
        Log.d(TAG, "Pause uploader before create temp!");

        for (int i=0; i<maxBufferPacketsCount; ++i){
            temp.add(queue.poll());
        }

        Log.d(TAG, "Continue uploader after create temp!");
        uploader.continueUploader();

        class FlushData implements Runnable {
            ConcurrentLinkedQueue<RTPStackItem> queue;
            FlushData(ConcurrentLinkedQueue<RTPStackItem> q) {
                queue = q;
            }
            public void run() {
                writeToDb(queue);
            }
        }
        new Thread(new FlushData(temp)).start(); //хуячим в базу
    }

    public synchronized long getLastNumber(Realm r) {
        RealmResults<RTPStackItem> results = r.where(RTPStackItem.class).findAll();
        long max = 0;
        if(results.max("rtpNumber") != null) {
            max = results.max("rtpNumber").longValue();
        }
        return max;
    }

    public synchronized void writeToDb(ConcurrentLinkedQueue<RTPStackItem> l){
        RealmConfiguration realmConfiguration = new RealmConfiguration.Builder(context).build();
        Realm.setDefaultConfiguration(realmConfiguration);
        Realm realm = Realm.getDefaultInstance();

        long last = getLastNumber(realm) + 100;
        Log.d(TAG, "Start save data to realm with first number: " + last + ". Queue size: " + l.size());
        realm.beginTransaction();
        for(int i = 0; i < l.size(); i++){
            RTPStackItem item = l.poll();
            if(item != null) {
                item.setRtpNumber(last++);
                RTPStackItem it = realm.copyToRealm(item);
            }else{
                Log.d(TAG, "Item in queue is null! Eto huinya.");
            }
        }
        realm.commitTransaction();
        realm.close();
        Log.d(TAG, "Data saved!");
    }

    public void clearBuffer(){
        queue.clear();
        Log.d(TAG, "clearedBuffer()!");
    }

    public class RTPBufferUploader implements Runnable {

        public String TAG = "RTPBufferUploader";

        public boolean isRun = false;
        private Thread t = null;

        private ConcurrentLinkedQueue<RTPStackItem> threadQueue;

        public RTPBufferUploader(ConcurrentLinkedQueue<RTPStackItem> l){
            threadQueue = l;
        }

        public void start(){
            if (t==null) {
                t = new Thread(this);
                t.start();
                isRun = true;
                Log.d(TAG, "Thread started.");
            }
        }

        public synchronized void pauseUploader(){
            if (t==null) {
                try {
                    t.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        public synchronized void continueUploader(){
            if (t==null) {
                t.notify();
            }
        }

        public void stop(){
            if (t != null) {
                t.interrupt();
                try {
                    t.join();
                } catch (InterruptedException e) {

                }finally {
                    t = null;
                    isRun = false;
                    Log.d(TAG, "Thread stoped.");
                }

            }
        }

        public boolean isInterrupted(){
            return Thread.interrupted();
        }

        @Override
        public void run() {
            while (!Thread.interrupted()) {
//                if(queue.size() > 50){  // возможно нужно будет убрать
                    RTPStackItem item = queue.peek();
                    if(item != null){
                        try {
                            Thread.sleep(1);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        boolean issend = send(item.getRtpData());
                        if(issend){
                            synchronized (queue) {
                                queue.poll(); // нахуй из очереди
                            }
                        }else{
                            stop();
                        }
                    }else{
                        try {
                            Thread.sleep(20);
       //                     Log.d(TAG, "Fuck Sleeping Thread.");
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
         //       }else{
//                    try {
//                        Thread.sleep(40);
//                        Log.d(TAG, "Sleeping Thread.");
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
           //     }
            }
            isRun = false;
        }
    }

    public boolean send(byte [] data) {
        boolean res = false;
//        try {
//            TCPClient.getInstance().writeToBuffer(data);

        long s = System.currentTimeMillis();

//        int result = TCPNativeClient.getInstance().writeToBuffer(data);

        int result = NativeSocketClient.getInstance().writeToBuffer(data);


        long r = System.currentTimeMillis() - s;

        if (result == 0){
            uploader.stop();
        }

   //     Log.w(TAG, "send time" + String.valueOf(r) + " size: " + result);

        if(result == data.length)
            res = true;

//        } catch (IOException e) {
//            Log.e(TAG, "Send error!" + e.getMessage() );
//            //e.printStackTrace();
//        }
        return res;
    }

    static {
        sessionSettings = new RTPStackSessionSettings();
    }

    public void createSessionSettings(){
        sessionSettings = new RTPStackSessionSettings();
    }
}
