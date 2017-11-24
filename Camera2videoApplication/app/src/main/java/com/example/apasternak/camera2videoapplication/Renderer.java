package com.example.apasternak.camera2videoapplication;

import android.graphics.Canvas;
import android.view.Surface;

/**
 * Created by apasternak on 24.11.17.
 */

public class Renderer extends Thread {
    volatile boolean mRunning;
    Surface mSurface;

    public void setRunning(boolean running) {
        mRunning = running;
    }

    boolean draw() {
        Canvas canvas = mSurface.lockCanvas(null);
        if (canvas != null) {
            try {
//                draw(canvas); // рисуем на нашем канвасе
                return true;
            } finally {
                if (mSurface.isValid() && mRunning) {
                    mSurface.unlockCanvasAndPost(canvas);
                }
            }
        }
        return false;
    }

    @Override
    public void run() {
        while (mRunning && draw()) {
        }
    }
}
