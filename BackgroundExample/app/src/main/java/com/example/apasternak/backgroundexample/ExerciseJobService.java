package com.example.apasternak.backgroundexample;

import android.app.job.JobParameters;
import android.app.job.JobService;
import android.util.Log;

/**
 * Created by apasternak on 30.10.17.
 */

public class ExerciseJobService extends JobService {
    private static final String TAG = ExerciseJobService.class.getSimpleName();

    public ExerciseJobService() {

    }

    @Override
    public boolean onStartJob(JobParameters params) {
        Log.i(TAG, "onStartJob: starting job with id: " + params.getJobId());

        ExerciseIntentService.startActionWriteExercise(getApplicationContext());
        return true;
    }

    @Override
    public boolean onStopJob(JobParameters params) {
        return true;
    }
}
