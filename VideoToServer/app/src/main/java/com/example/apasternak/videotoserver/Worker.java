package com.example.apasternak.videotoserver;

import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaFormat;
import android.view.Surface;

import java.io.IOException;
import java.nio.ByteBuffer;

/**
 * Created by apasternak on 27.10.17.
 */

public class Worker extends Thread {

    // Stores the information about the current buffer
    private MediaCodec.BufferInfo mBufferInfo;

    // Encoder
    private MediaCodec mEncoder;

    public Surface getSurface() {
        return mSurface;
    }

    public void setSurface(Surface surface) {
        mSurface = surface;
    }

    // The entry point for the encoder
    private Surface mSurface;

    private volatile boolean mRunning;

    // Lock during waiting for the available buffer
    final long mTimeoutUs;

    public Worker() {
        mBufferInfo = new MediaCodec.BufferInfo();
        mTimeoutUs = 10000l;
    }

    public void setRunning(boolean running) {
        mRunning = running;
    }

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

    /**! Setting prerequisites before the encoding */
    private void prepare() {
        int width = 1280;
        int height = 720;
        int colorFormat = MediaCodecInfo.CodecCapabilities.COLOR_FormatSurface;
        int videoBitrate = 3000000;
        int videoFramePerSecond = 30;
        int iFrameInterval = 2;

        MediaFormat format = MediaFormat.createVideoFormat("video/avc", width, height);
        format.setInteger(MediaFormat.KEY_COLOR_FORMAT, colorFormat);
        format.setInteger(MediaFormat.KEY_BIT_RATE, videoBitrate);
        format.setInteger(MediaFormat.KEY_FRAME_RATE, videoFramePerSecond);
        format.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, iFrameInterval);

        try {
            mEncoder = MediaCodec.createEncoderByType("video/avc"); // H264 кодек
        } catch (IOException e) {
            e.printStackTrace();
        }

        mEncoder.configure(format, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
        mSurface = mEncoder.createInputSurface();
        mEncoder.start();
    }

    /**! Encoding itself */
    private void encode() {
        if (!mRunning) {
            mEncoder.signalEndOfInputStream(); // сообщить кодеку о конце потока данных
        }

        // получаем массив буферов кодека
        ByteBuffer[] outputBuffers = mEncoder.getOutputBuffers();
        for (;;) {
            // статус является кодом возврата или же, если 0 и позитивное число, индексом буфера в массиве
            int status = mEncoder.dequeueOutputBuffer(mBufferInfo, mTimeoutUs);
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

    /**! Resources releasing */
    private void release() {
        mEncoder.stop();
        mEncoder.release();
        mSurface.release();
    }
}
