package com.example.apasternak.videotoserver;

import android.graphics.Canvas;
import android.view.Surface;

/**
 * Created by apasternak on 27.10.17.
 */

public class Renderer extends Thread {

    private volatile boolean mRunning;

    private Worker mWorker = new Worker();
    // The entry point for the encoder
    private Surface mSurface = mWorker.getSurface();

    public void setRunning(boolean running) {
        mRunning = running;
    }

    boolean draw() {
        Canvas canvas = mSurface.lockCanvas(null);
        if (canvas != null) {
            try {
                draw();
//                draw(canvas); // рисуем на нашем канвасе
                return true;
            } finally {
                if (mSurface.isValid() && mRunning) {
                    mSurface.unlockCanvasAndPost(canvas);
                    mWorker.setSurface(mSurface);
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