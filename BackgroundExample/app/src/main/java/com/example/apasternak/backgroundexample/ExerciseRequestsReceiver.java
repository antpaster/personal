package com.example.apasternak.backgroundexample;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.icu.lang.UCharacter;
import android.widget.Toast;

/**
 * Created by apasternak on 30.10.17.
 */

public class ExerciseRequestsReceiver extends BroadcastReceiver {
    public static final String ACTION_PERFORM_EXERCISE = "ACTION_PERFORM_EXERCISE";

    private static int sJobId = 1;

    @Override
    public void onReceive(Context context, Intent intent) {
        switch (intent.getAction()) {
            case ACTION_PERFORM_EXERCISE:
                scheduleJob(context);
                break;
            default:
                throw new IllegalArgumentException("Unknown action.");
        }
    }

    /** Dummy for now */
    private void scheduleJob(Context context) {
        Toast.makeText(context, "Job is scheduled!", Toast.LENGTH_LONG).show();
    }
}
