package com.example.apasternak.backgroundexample;

import android.content.Context;
import android.content.Intent;
import android.support.test.InstrumentationRegistry;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() throws Exception {
        assertEquals(4, 2 + 2);
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