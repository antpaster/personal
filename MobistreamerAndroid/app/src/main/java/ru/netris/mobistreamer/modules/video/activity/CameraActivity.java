/*
 * Copyright 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package ru.netris.mobistreamer.modules.video.activity;

import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.NotificationCompat;
import android.util.Log;

import ru.netris.mobistreamer.MobistreamService;
import ru.netris.mobistreamer.R;

public class CameraActivity extends Activity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera);

        startService(new Intent(this, MobistreamService.class));

        if (null == savedInstanceState) {
            getFragmentManager().beginTransaction()
                    .replace(R.id.container, Camera2VideoFragment.newInstance())
                    .commit();
        }



    }

    private void addNotification() {
        Intent notificationIntent = new Intent(this, CameraActivity.class);
        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, notificationIntent, PendingIntent.FLAG_CANCEL_CURRENT);

        NotificationCompat.Builder builder = new NotificationCompat.Builder(this);
        Notification notification = builder.setContentIntent(pendingIntent)
                .setWhen(System.currentTimeMillis())
                .setTicker("Test 1")
                .setSmallIcon(R.drawable._mobistream_settings_icon_on)
                .setContentTitle("Test title")
                .setContentText("Test content text").build();
        notification.flags |= Notification.FLAG_ONGOING_EVENT;
        ((NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE)).notify(0,notification);

    }

    private void removeNotification() {
        ((NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE)).cancel(0);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d("11111111111","onDestroy");
    }
}
