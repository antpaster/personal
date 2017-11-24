package com.example.apasternak.camera2videoapplication;

import android.media.MediaCodec;
import android.media.MediaFormat;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.view.Surface;

import java.io.IOException;
import java.nio.ByteBuffer;

/**
 * Created by apasternak on 24.11.17.
 */

public class Decoder extends Thread {
    private volatile boolean mConfigured;
    private volatile boolean mRunning;
    private MediaCodec mDecoder;
    private final long mTimeoutUs = 10000l;

    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
    synchronized void configure(Surface surface, int width, int height, ByteBuffer csd0) {
        if (mConfigured) { // просто флаг, чтобы знать, что декодер готов
            throw new IllegalStateException();
        }
        // создаем видео формат
        MediaFormat format = MediaFormat.createVideoFormat("video/avc", width, height);
        // передаем наш csd-0
        format.setByteBuffer("csd-0", csd0);

        // создаем декодер
        try {
            mDecoder = MediaCodec.createDecoderByType("video/avc");
        } catch (IOException e) {
            e.printStackTrace();
        }

        // конфигурируем декодер
        mDecoder.configure(format, surface, null, 0);
        mDecoder.start();
        mConfigured = true;
    }

    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
    void decodeSample(byte[] data, int offset, int size, long presentationTimeUs, int flags) {
        if (mConfigured) {
            // вызов блокирующий
            int index = mDecoder.dequeueInputBuffer(mTimeoutUs);
            if (index >= 0) {
                ByteBuffer buffer = mDecoder.getInputBuffers()[index];
                buffer.clear(); // обязательно сбросить позицию и размер буфера
                buffer.put(data, offset, size);
                // сообщаем системе о доступности буфера данных
                mDecoder.queueInputBuffer(index, 0, size, presentationTimeUs, flags);
            }
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
    @Override
    public void run() {
        try {
            MediaCodec.BufferInfo info = new MediaCodec.BufferInfo(); // переиспользуем BufferInfo
            while (mRunning) {
                if (mConfigured) { // если кодек готов
                    int index = mDecoder.dequeueOutputBuffer(info, mTimeoutUs);
                    if (index >= 0) { // буфер с индексом index доступен
                        // info.size > 0: если буфер не нулевого размера, то рендерим на Surface
                        mDecoder.releaseOutputBuffer(index, info.size > 0);
                        // заканчиваем работу декодера если достигнут конец потока данных
                        if ((info.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM)
                                == MediaCodec.BUFFER_FLAG_END_OF_STREAM) {
                            mRunning = false;
                            break;
                        }
                    }
                } else {
                    // просто спим, т.к. кодек не готов
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException ignore) {
                    }
                }
            }
        } finally {
            // освобождение ресурсов
            release();
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
    void release() {
        if (mConfigured) {
            mDecoder.stop();
            mDecoder.release();
        }
    }
}
