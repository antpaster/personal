package com.github.ihandy.jobschedulerdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    private Button mJobStartButton;

    private ExerciseIntentService mExerciseIntentService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mJobStartButton = (Button) findViewById(R.id.button);
        mJobStartButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                ExerciseIntentService.startActionWriteExercise(getApplicationContext());
            }
        });
    }
}
