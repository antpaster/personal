package net.majorkernelpanic.streaming.realm;

import android.content.Context;
import android.util.Log;

import io.realm.Realm;
import io.realm.RealmChangeListener;
import io.realm.RealmConfiguration;
import io.realm.RealmResults;

/**
 * Created by alexander on 13.01.16.
 */
public class RTPStackStorage {

    public static String TAG = "RTPStackStorage";
  //  private static RTPStackSender sender;

    private Context context;
//    private static RTPStackStorage instance = null;

    public static volatile long lastNumber = -1;

    RealmConfiguration realmConfiguration;
    private Realm realm;
    private RealmResults<RTPStackItem> allRTPItemsResult;

    private RealmChangeListener realmRTPListener = new RealmChangeListener() {
        @Override
        public void onChange() {
//            if(sender.isInterrupted()){
//                sender.start();
//            }
//            adapter.notifyDataSetChanged();
//            listview.invalidateViews();
        }
    };

//    public static RTPStackStorage getInstance(Context con) {
//        if(instance == null){
//            instance = new RTPStackStorage(con);
//        }
//        return instance;
//    }

//    public static RTPStackStorage getInstance() {
//        return instance;
//    }

    private RTPStackStorage() {

    }

    public RTPStackStorage(Context con) {
        context = con;

        realmConfiguration = new RealmConfiguration.Builder(context).build();
        Realm.setDefaultConfiguration(realmConfiguration);
        realm = Realm.getDefaultInstance();
        realm.addChangeListener(realmRTPListener);

        //lastNumber = getLastNumber();
        lastNumber = getFirstNumber();

 //       sender = new RTPStackSender();
//        if(!sender.isRun){

//            sender.start(context);

//        }

    }

//    public void startSend(){
//        sender = new RTPStackSender();
//        sender.start(context);
//    }

    public synchronized void pushPacket(final long timestamp, final byte [] data){

        realm.beginTransaction();

        RTPStackItem item = realm.createObject(RTPStackItem.class);
        long newNumber = lastNumber + 1;
        lastNumber = newNumber;
        item.setRtpNumber(newNumber);
        item.setRtpTimeStamp(timestamp);
        item.setRtpData(data);
   //     Log.d(TAG, "numder: " + item.getRtpNumber() + " ts: " + item.getRtpTimeStamp());

        //User realmUser = realm.copyToRealm(user);
        realm.commitTransaction();

//        realm.executeTransaction(new Realm.Transaction() {
//            @Override
//            public void execute(Realm bgRealm) {
//                RTPStackItem item = bgRealm.createObject(RTPStackItem.class);
//                long newNumber = lastNumber + 1;
//                lastNumber = newNumber;
//                item.setRtpNumber(newNumber);
//                item.setRtpTimeStamp(timestamp);
//                item.setRtpData(data);
//            }
//        }, new Realm.Transaction.Callback() {
//            @Override
//            public void onSuccess() {
//
//            }
//
//            @Override
//            public void onError(Exception e) {
//                // transaction is automatically rolled-back, do any cleanup here
//            }
//        });
    }

    public synchronized RTPStackItem getLastPacket() {
        RealmResults<RTPStackItem> results = realm.where(RTPStackItem.class).findAll();
        RTPStackItem item = results.where().equalTo("rtpNumber", lastNumber).findFirst();
        return item;
    }

    public synchronized RTPStackItem getPacket(long number) {
        RealmResults<RTPStackItem> results = realm.where(RTPStackItem.class).findAll();
        RTPStackItem item = results.where().equalTo("rtpNumber", number).findFirst();
        return item;
    }

    public synchronized void deletePacket(RTPStackItem item) {
        realm.beginTransaction();
        item.removeFromRealm();
        realm.commitTransaction();
    }

    public synchronized long getStorageItemCount() {
        RealmResults<RTPStackItem> results = realm.where(RTPStackItem.class).findAll();
        return results.size();
    }

    public long getLastNumber() {
        RealmResults<RTPStackItem> results = realm.where(RTPStackItem.class).findAll();
        long max = 0;
        if(results.max("rtpNumber") != null) {
            max = results.max("rtpNumber").longValue();
        }
//        results.clear();
        return max;
    }

    public long getFirstNumber() {
        RTPStackItem results = realm.where(RTPStackItem.class).findFirst();
        if (results == null)
            return 0;
        return results.getRtpNumber();
    }

    public void deleteRealm(){
        realm.close();
        Realm.deleteRealm(realmConfiguration);
    }

    public boolean hasNext(long prev){
        return lastNumber > prev;
    }

    public void close() {
//        sender.stop();
        realm.close();
    }
}
