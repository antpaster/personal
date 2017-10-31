package com.example.apasternak.backgroundexample;

import android.app.IntentService;
import android.content.Context;
import android.content.Intent;

import java.io.FileWriter;
import java.io.IOException;

/**
 * Created by apasternak on 30.10.17.
 */

public class ExerciseIntentService extends IntentService {
    private static final String ACTION_WRITE_EXERCISE =
        "com.example.apasternak.backgroundexample.ACTION_WRITE_EXERCISE";

    public ExerciseIntentService() {
        super("com.example.apasternak.backgroundexample.ExerciseIntentService");
    }

    public static void startActionWriteExercise(Context context) {
        Intent intent = new Intent(context, ExerciseIntentService.class);
        intent.setAction(ACTION_WRITE_EXERCISE);
        context.startService(intent);
    }

    @Override
    protected void onHandleIntent(Intent intent) {
        if (intent != null) {
            final String action = intent.getAction();
            if (ACTION_WRITE_EXERCISE.equals(action)) {
                handleActionWriteExercise();
            }
        }
    }

    private void handleActionWriteExercise() {
        try {
            FileWriter fileWriter =
                new FileWriter(getFilesDir().getPath() + "exercise.txt");
            fileWriter.write("Exercise");
            fileWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

//    @Test
//    public void sendDemoBroadcast() throws Exception {
//        Context appContext = InstrumentationRegistry.getTargetContext();
//
//        Intent demoIntentForBroadcast =
//                new Intent(appContext, ExerciseRequestsReceiver.class);
//
//        demoIntentForBroadcast
//                .setAction(ExerciseRequestsReceiver.ACTION_PERFORM_EXERCISE);
//
//        appContext.sendBroadcast(demoIntentForBroadcast);
//    }
}
