package ru.netris.mobistreamer;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Binder;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.support.annotation.Nullable;
import android.support.v4.app.NotificationCompat;
import android.util.Log;
import android.util.Size;

import java.util.LinkedList;

import ru.netris.mobistreamer.modules.video.activity.AutoFitTextureView;
import ru.netris.mobistreamer.modules.video.activity.Camera2Activity;
import ru.netris.mobistreamer.modules.video.camera.CameraService;

/**
 * Created by ps on 09.08.17.
 */

public class MobistreamService extends Service {

    public final static String TAG = "MobistreamService";

    public CameraService cameraService = null;


    public static String SERVER_NAME = "MajorKernelPanic RTSP Server";
    public static final int DEFAULT_RTSP_PORT = 8086;

    public final static int ERROR_BIND_FAILED = 0x00;
    public final static int ERROR_START_FAILED = 0x01;
    public final static int MESSAGE_STREAMING_STARTED = 0X00;
    public final static int MESSAGE_STREAMING_STOPPED = 0X01;

//    private RequestListener mListenerThread;
    private final IBinder mBinder = new LocalBinder();
    private boolean mRestart = false;
    private final LinkedList<MobistreamService.CallbackListener> mListeners = new LinkedList<CallbackListener>();

    /** Be careful: those callbacks won't necessarily be called from the ui thread ! */
    public interface CallbackListener {
        void onError(MobistreamService service, Exception e, int error);
        void onMessage(MobistreamService service, int message);
        void onDeviceOpen();
        void onRecording(boolean recording);
    }

    public void addCallbackListener(CallbackListener listener) {
        synchronized (mListeners) {
            if (mListeners.size() > 0) {
                for (CallbackListener cl : mListeners) {
                    if (cl == listener) return;
                }
            }
            mListeners.add(listener);
        }
    }

    public void removeCallbackListener(CallbackListener listener) {
        synchronized (mListeners) {
            mListeners.remove(listener);
        }
    }

    private Looper mServiceLooper;
    private ServiceHandler mServiceHandler;

    // Handler that receives messages from the thread
    private final class ServiceHandler extends Handler {
        public ServiceHandler(Looper looper) {
            super(looper);
        }
        @Override
        public void handleMessage(Message msg) {
            // Normally we would do some work here, like download a file.
            // For our sample, we just sleep for 5 seconds.
//            long endTime = System.currentTimeMillis() + 5*1000;
//            while (System.currentTimeMillis() < endTime) {
//                synchronized (this) {
//                    try {
//                        wait(endTime - System.currentTimeMillis());
//                    } catch (Exception e) {
//                    }
//                }
//            }
            // Stop the service using the startId, so that we don't stop
            // the service in the middle of handling another job
//            stopSelf(msg.arg1);
        }
    }

    private  CameraService.Callback serviceCallback = new CameraService.Callback() {
        @Override
        public void onDeviceOpened() {

//            if (mobistreamService != null) {
//                mBinder.setPreview(mTextureView);
//
//                mobistreamService.cameraService.updatePreview();
//                mobistreamService.cameraService.configureTransform(mTextureView.getWidth(),mTextureView.getHeight());
//                mBinder.startPreview();
//            }

            synchronized (mListeners) {
                if (mListeners.size() > 0) {
                    for (CallbackListener cl : mListeners) {
                        cl.onDeviceOpen();
                    }
                }
            }

//            if(cameraService != null) {
//                if(!cameraService.isPreviewed()) {
//                    startPreview();
//                }
//            }
        }

        @Override
        public void onDeviceDisconnected() {
//            stopSelf();
            Log.d(TAG, "onDeviceDisconnected()");
        }

        @Override
        public void onRecording(boolean recording) {
            synchronized (mListeners) {
                if (mListeners.size() > 0) {
                    for (CallbackListener cl : mListeners) {
                        cl.onRecording(recording);
                    }
                }
            }
        }
    };

    @Override
    public void onCreate() {
        super.onCreate();
        Log.e(TAG, "onCreate");

        cameraService = new CameraService();
        cameraService.callback = serviceCallback;
        cameraService.setVideoSize(new Size(1280, 720));
        cameraService.openCamera();

        // Start up the thread running the service.  Note that we create a
        // separate thread because the service normally runs in the process's
        // main thread, which we don't want to block.  We also make it
        // background priority so CPU-intensive work will not disrupt our UI.
        HandlerThread thread = new HandlerThread("ServiceStartArguments",
                android.os.Process.THREAD_PRIORITY_BACKGROUND);
        thread.start();
//
//        // Get the HandlerThread's Looper and use it for our Handler
        mServiceLooper = thread.getLooper();
        mServiceHandler = new ServiceHandler(mServiceLooper);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
//        Toast.makeText(this, "service starting", Toast.LENGTH_SHORT).show();
        Log.e(TAG, "onStartCommand");
        // For each start request, send a message to start a job and deliver the
        // start ID so we know which request we're stopping when we finish the job
//        Message msg = mServiceHandler.obtainMessage();
//        msg.arg1 = startId;
//        mServiceHandler.sendMessage(msg);

        addNotification();

        if(cameraService != null && !cameraService.isConnected()) {
            cameraService = new CameraService();
            cameraService.callback = serviceCallback;
            cameraService.setVideoSize(new Size(1280, 720));
            cameraService.openCamera();
        }
        return START_STICKY;
    }

    public void setPreviewView(AutoFitTextureView textureView) {
        cameraService.setPreviewSize(new Size(textureView.getWidth(), textureView.getHeight()));
        cameraService.setPreview(textureView);
    }

    public void startPreview() {
        cameraService.startPreview();
    }

    public void stopPreview() {
        cameraService.stopPreview();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.e(TAG, "onDestroy");
        removeNotification();
    }

    @Override
    public void onLowMemory() {
        super.onLowMemory();
    }

    protected void postMessage(int id) {
        synchronized (mListeners) {
            if (mListeners.size() > 0) {
                for (CallbackListener cl : mListeners) {
                    cl.onMessage(this, id);
                }
            }
        }
    }

    protected void postError(Exception exception, int id) {
        synchronized (mListeners) {
            if (mListeners.size() > 0) {
                for (CallbackListener cl : mListeners) {
                    cl.onError(this, exception, id);
                }
            }
        }
    }

    private void addNotification() {
        Intent notificationIntent = new Intent(getApplication(), Camera2Activity.class);
        PendingIntent pendingIntent = PendingIntent.getActivity(getApplication(), 0, notificationIntent, PendingIntent.FLAG_CANCEL_CURRENT);

        NotificationCompat.Builder builder = new NotificationCompat.Builder(getApplication());
        Notification notification = builder.setContentIntent(pendingIntent)
                .setWhen(System.currentTimeMillis())
                .setTicker("Mobistreamer")
                .setSmallIcon(R.mipmap.ic_launcher)
                .setContentTitle("Mobistreamer")
                .setContentText("Запущено вещание").build();
        notification.flags |= Notification.FLAG_ONGOING_EVENT;
        ((NotificationManager)getApplication().getSystemService(Context.NOTIFICATION_SERVICE)).notify(0,notification);
    }

    private void removeNotification() {
        getApplication().stopService(new Intent(getApplication(), MobistreamService.class));
        ((NotificationManager)getApplication().getSystemService(Context.NOTIFICATION_SERVICE)).cancel(0);
    }

    // BIND

    @Override
    public boolean onUnbind(Intent intent) {
        stopPreview();
        return super.onUnbind(intent);
    }

    @Override
    public void onRebind(Intent intent) {
        super.onRebind(intent);
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    public class LocalBinder extends Binder {

        public MobistreamService getService() {
            return MobistreamService.this;
        }

        public void setPreview(AutoFitTextureView textureView) {
            cameraService.setPreview(textureView);
            cameraService.updatePreview();
        }

        public void startPreview() {
            cameraService.startPreview();
            cameraService.updatePreview();
        }
    }

    //Process
/*
    class WorkerThread extends Thread implements Runnable {

        public WorkerThread() {

        }

        @Override
        public void run() {
            super.run();
        }
    }
    */
}
