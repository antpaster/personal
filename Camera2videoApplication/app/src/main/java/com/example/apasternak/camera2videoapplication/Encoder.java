package com.example.apasternak.camera2videoapplication;

import android.annotation.TargetApi;
import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaFormat;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.view.Surface;

import java.io.IOException;
import java.nio.ByteBuffer;

import static android.media.tv.TvContract.Programs.Genres.encode;
import static android.os.Looper.prepare;

/**
 * Created by apasternak on 24.11.17.
 */

public class Encoder extends Thread {
    MediaCodec.BufferInfo mBufferInfo; // хранит информацию о текущем буфере
    MediaCodec mEncoder; // кодер
    Surface mSurface; // Surface как вход данных для кодера
    volatile boolean mRunning;
    final long mTimeoutUsec; // блокировка в ожидании доступного буфера

    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
    public Encoder() {
        mBufferInfo = new MediaCodec.BufferInfo();
        mTimeoutUsec = 10000l;
    }

    public void setRunning(boolean running) {
        mRunning = running;
    }

    @RequiresApi(Build.VERSION_CODES.JELLY_BEAN_MR2)
    @Override
    public void run() {
        prepare();
        try {
            while (mRunning) {
                encode();
            }
        } finally {
            release();
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN_MR2)
    void prepare() {
        int width = 1280; // ширина видео
        int height = 720; // высота видео
        int colorFormat = MediaCodecInfo.CodecCapabilities.COLOR_FormatSurface; // формат ввода цвета
        int videoBitrate = 3000000; // битрейт видео в bps (бит в секунду)
        int videoFramePerSecond = 30; // FPS
        int iframeInterval = 2; // I-Frame интервал в секундах

        MediaFormat format = MediaFormat.createVideoFormat("video/avc", width, height);
        format.setInteger(MediaFormat.KEY_COLOR_FORMAT, colorFormat);
        format.setInteger(MediaFormat.KEY_BIT_RATE, videoBitrate);
        format.setInteger(MediaFormat.KEY_FRAME_RATE, videoFramePerSecond);
        format.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, iframeInterval);

        try {
            mEncoder = MediaCodec.createEncoderByType("video/avc"); // H264 кодек
        } catch (IOException e) {
            e.printStackTrace();
        }

        mEncoder.configure(format, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE); // конфигурируем кодек как кодер
        mSurface = mEncoder.createInputSurface(); // получаем Surface кодера
        mEncoder.start(); // запускаем кодер
    }

    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN_MR2)
    void encode() {
        if (!mRunning) {
            mEncoder.signalEndOfInputStream(); // сообщить кодеку о конце потока данных
        }
        // получаем массив буферов кодека
        ByteBuffer[] outputBuffers = mEncoder.getOutputBuffers();
        for (;;) {
            // статус является кодом возврата или же, если 0 и позитивное число, индексом буфера в массиве
            int status = mEncoder.dequeueOutputBuffer(mBufferInfo, mTimeoutUsec);
            if (status == MediaCodec.INFO_TRY_AGAIN_LATER) {
                // нет доступного буфера, пробуем позже
                if (!mRunning) break; // выходим если поток закончен
            } else if (status == MediaCodec.INFO_OUTPUT_BUFFERS_CHANGED) {
                // на случай если кодек меняет буфера
                outputBuffers = mEncoder.getOutputBuffers();
            } else if (status < 0) {
                // просто ничего не делаем
            } else {
                // статус является индексом буфера кодированных данных
                ByteBuffer data = outputBuffers[status];
                data.position(mBufferInfo.offset);
                data.limit(mBufferInfo.offset + mBufferInfo.size);
                // ограничиваем кодированные данные



                // делаем что-то с данными...
                mEncoder.releaseOutputBuffer(status, false);
                if ((mBufferInfo.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM)
                        == MediaCodec.BUFFER_FLAG_END_OF_STREAM) {
                    break;
                }
            }
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
    void release() {
        mEncoder.stop();
        mEncoder.release();
        mSurface.release();
    }
}
