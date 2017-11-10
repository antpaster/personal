package net.majorkernelpanic.streaming.realm;

import android.content.Context;
import android.os.Looper;
import android.util.Log;
import android.util.Pair;

import java.util.LinkedList;
import java.util.List;

import io.realm.Realm;
import io.realm.RealmResults;
//import ru.netris.posixsockets.TCPNativeClient;

/**
 * Created by alexander on 20.01.16.
 */
public class RTPStackUploaderThread extends Thread {

    public static String TAG = "RTPStackUploaderThread";
    private final Context context;
    RealmResults<RTPStackItem> results;

    public RTPStackUploaderThread(Context context) {
        this.context = context;
    }

    public void run() {
        Looper.prepare();
        Realm realm = null;
        try {
            realm = Realm.getInstance(context);

            results = realm.where(RTPStackItem.class).findAll();

            List<Long> numberList = new LinkedList<Long>();

            for (int i = 0; i < results.size(); i++) {
                RTPStackItem item = results.get(i);
                numberList.add(Long.valueOf(item.getRtpNumber()));
            }

            List<Pair<Long, Long>> pairList = getIntevals(numberList);

            for (Pair<Long, Long> p:pairList ) {
                int min = p.first.intValue();
                int max = p.second.intValue();

                long minTimestamp = results.get(min).getRtpTimeStamp();
                long maxTimestamp = results.get(max).getRtpTimeStamp();

                for(int i = min; i <= max; i++){
                    RTPStackItem item = results.get(i);
                    item.getRtpTimeStamp();
                    item.getRtpData();

                    // устанавливаем соединение и хуячим, затем разрываем соединение


//                    TCPNativeClient.getInstance().connect(new TCPNativeClient.CallbackConnection() {
//                        @Override
//                        public void connectedStream(boolean isConnect) {
//                            if (isConnect) {
//
//                                // сначала отправляем sdp и т.д. а потом запускаем поток с данными
//
//
//
//                            }
//                        }
//                    });



                }
            }



            //... Setup the handlers using the Realm instance
            Looper.loop();
        } finally {
            if (realm != null) {
                realm.close();
            }
        }
    }

    public List<Pair<Long, Long>> getIntevals(List<Long> l){
        List<Pair<Long, Long>> pairList = new LinkedList<Pair<Long, Long>>();
        long min = -1;
        long max = -1;
        for (int i = 0; i < l.size() - 1; i++) {
            long current = l.get(i).longValue();
            long next = l.get(i+1).longValue();
            if(min == -1){
                //min = current;
                min = i;
            }else{
                if(current+1 != next){
                    //max = current;
                    max = i;
                    Log.d(TAG, "min:" + min + " max:" + max);
                    pairList.add(new Pair<Long, Long>(min, max));
                    min = -1;
                    max = -1;
                }
            }
        }
        Log.d(TAG, "Pair list size: " + pairList.size());
        return pairList;
    }
}
