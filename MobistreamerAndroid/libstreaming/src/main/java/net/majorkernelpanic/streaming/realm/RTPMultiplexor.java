package net.majorkernelpanic.streaming.realm;

import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import java.util.concurrent.ConcurrentLinkedQueue;


/**
 * Created by alexander on 15.01.16.
 *
 *
 * Класс пример, нельзя исползовать для RTPStackItem т.к. это ртп пакеты.
 *
 * только для видео и аудио!
 *
 * ртп нелья перемешивать
 *
 *
 *
 */
public class RTPMultiplexor {

    public PriorityQueue<RTPStackItem> queue;
    public final int MAX_BUFFER_SIZE = 1000;
    public Callback callback;

    public interface Callback{
        boolean bufferOverflow(RTPStackItem item);
    }

    public RTPMultiplexor(){
        Comparator<RTPStackItem> comparator = new StringLengthComparator();
        queue = new PriorityQueue<RTPStackItem>(MAX_BUFFER_SIZE + 100, comparator);
    }

    public synchronized void add(RTPStackItem item){
        queue.add(item);

        if(queue.size() > MAX_BUFFER_SIZE){
            if(callback.bufferOverflow(queue.peek())){
                queue.poll(); // нахуй из очереди
            }
        }

    }

    public void deleteTopItem(){
        queue.poll(); // нахуй из очереди
    }

    public class StringLengthComparator implements Comparator<RTPStackItem> {
        @Override
        public int compare(RTPStackItem lhs, RTPStackItem rhs) {
            if (lhs.getRtpTimeStamp() < rhs.getRtpTimeStamp()) {
                return -1;
            }
            if (lhs.getRtpTimeStamp() > rhs.getRtpTimeStamp()){
                return 1;
            }
            return 0;
        }
    }
}
