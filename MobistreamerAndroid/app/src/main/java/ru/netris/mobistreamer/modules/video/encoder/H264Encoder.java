package ru.netris.mobistreamer.modules.video.encoder;

import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaFormat;
import android.support.annotation.NonNull;
import android.util.Log;
import android.view.Surface;

import java.io.IOException;
import java.util.concurrent.atomic.AtomicReference;

/**
 * Created by ps on 08.09.17.
 */

public class H264Encoder {

    public static final String TAG = "H264Encoder";

    MediaCodec mediaCodec;
    Surface inputSurface = null;

    int width = 1280;
    int heigth = 720;

    public H264Encoder() {



    }

    public void initMediaCodec(Surface surface) throws IOException {
        mediaCodec = MediaCodec.createEncoderByType("video/avc");
        MediaFormat format = MediaFormat.createVideoFormat("video/avc", width, heigth);
        int colorFormat = MediaCodecInfo.CodecCapabilities.COLOR_FormatSurface;
        int videoBitrate = 90000;
        int videoFramePerSecond = 30;
        int iframeInterval = 1;
        format.setInteger(MediaFormat.KEY_COLOR_FORMAT, colorFormat);
        format.setInteger(MediaFormat.KEY_BIT_RATE, videoBitrate);
        format.setInteger(MediaFormat.KEY_FRAME_RATE, videoFramePerSecond);
        format.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, iframeInterval);

        mediaCodec.setCallback(new MediaCodec.Callback() {
            @Override
            public void onInputBufferAvailable(@NonNull MediaCodec mediaCodec, int i) {
                Log.d(TAG, "onInputBufferAvailable");
//                ByteBuffer inputBuffer = mediaCodec.getInputBuffer(inputBufferId);
                // fill inputBuffer with valid data

            }

            @Override
            public void onOutputBufferAvailable(@NonNull MediaCodec mediaCodec, int i, @NonNull MediaCodec.BufferInfo bufferInfo) {
                Log.d(TAG, "onOutputBufferAvailable");
            }

            @Override
            public void onError(@NonNull MediaCodec mediaCodec, @NonNull MediaCodec.CodecException e) {
                Log.d(TAG, "onError: " + e.getDiagnosticInfo());
            }

            @Override
            public void onOutputFormatChanged(@NonNull MediaCodec mediaCodec, @NonNull MediaFormat mediaFormat) {
                Log.d(TAG, "onOutputFormatChanged: " + mediaFormat.toString());
            }
        });


        inputSurface = mediaCodec.createInputSurface();
        mediaCodec.configure(format, surface, null, MediaCodec.CONFIGURE_FLAG_ENCODE);

    }


    private MediaCodec createVideoEncoder(MediaCodecInfo codecInfo, MediaFormat format, AtomicReference<Surface> surfaceReference) throws IOException {
        MediaCodec encoder = MediaCodec.createByCodecName(codecInfo.getName());
        encoder.setCallback(new MediaCodec.Callback() {
            public void onError(MediaCodec codec, MediaCodec.CodecException exception) {
            }
            public void onOutputFormatChanged(MediaCodec codec, MediaFormat format) {
                Log.d(TAG, "video encoder: output format changed");
//                if (mOutputVideoTrack >= 0) {
//                    fail("video encoder changed its output format again?");
//                }
//                mEncoderOutputVideoFormat = codec.getOutputFormat();
//                setupMuxer();
            }
            public void onInputBufferAvailable(MediaCodec codec, int index) {
            }
            public void onOutputBufferAvailable(MediaCodec codec, int index, MediaCodec.BufferInfo info) {

                    Log.d(TAG, "video encoder: returned output buffer: " + index);
                    Log.d(TAG, "video encoder: returned buffer of size " + info.size);

//                muxVideo(index, info);
            }
        });
        encoder.configure(format, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
        // Must be called before start() is.
        surfaceReference.set(encoder.createInputSurface());
        encoder.start();
        return encoder;
    }

    private MediaCodec createAudioEncoder(MediaCodecInfo codecInfo, MediaFormat format) throws IOException {
        MediaCodec encoder = MediaCodec.createByCodecName(codecInfo.getName());
        encoder.setCallback(new MediaCodec.Callback() {
            public void onError(MediaCodec codec, MediaCodec.CodecException exception) {
            }
            public void onOutputFormatChanged(MediaCodec codec, MediaFormat format) {
                Log.d(TAG, "audio encoder: output format changed");
//                if (mOutputAudioTrack >= 0) {
//                    fail("audio encoder changed its output format again?");
//                }

//                mEncoderOutputAudioFormat = codec.getOutputFormat();
//                setupMuxer();
            }
            public void onInputBufferAvailable(MediaCodec codec, int index) {
                Log.d(TAG, "audio encoder: returned input buffer: " + index);

//                mPendingAudioEncoderInputBufferIndices.add(index);
//                tryEncodeAudio();
            }
            public void onOutputBufferAvailable(MediaCodec codec, int index, MediaCodec.BufferInfo info) {
                    Log.d(TAG, "audio encoder: returned output buffer: " + index);
                    Log.d(TAG, "audio encoder: returned buffer of size " + info.size);

//                muxAudio(index, info);
            }
        });
        encoder.configure(format, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
        encoder.start();
        return encoder;
    }

    private void tryEncodeAudio() {
//        if (mPendingAudioEncoderInputBufferIndices.size() == 0 || mPendingAudioDecoderOutputBufferIndices.size() == 0)
//            return;
//        int decoderIndex = mPendingAudioDecoderOutputBufferIndices.poll();
//        int encoderIndex = mPendingAudioEncoderInputBufferIndices.poll();
//        MediaCodec.BufferInfo info = mPendingAudioDecoderOutputBufferInfos.poll();

//        ByteBuffer encoderInputBuffer = mAudioEncoder.getInputBuffer(encoderIndex);
//        int size = info.size;
//        long presentationTime = info.presentationTimeUs;
//        if (VERBOSE) {
//            Log.d(TAG, "audio decoder: processing pending buffer: "
//                    + decoderIndex);
//        }
//        if (VERBOSE) {
//            Log.d(TAG, "audio decoder: pending buffer of size " + size);
//            Log.d(TAG, "audio decoder: pending buffer for time " + presentationTime);
//        }
//        if (size >= 0) {
//            ByteBuffer decoderOutputBuffer = mAudioDecoder.getOutputBuffer(decoderIndex).duplicate();
//            decoderOutputBuffer.position(info.offset);
//            decoderOutputBuffer.limit(info.offset + size);
//            encoderInputBuffer.position(0);
//            encoderInputBuffer.put(decoderOutputBuffer);
//
//            mAudioEncoder.queueInputBuffer(
//                    encoderIndex,
//                    0,
//                    size,
//                    presentationTime,
//                    info.flags);
//        }
//        mAudioDecoder.releaseOutputBuffer(decoderIndex, false);
//        if ((info.flags
//                & MediaCodec.BUFFER_FLAG_END_OF_STREAM) != 0) {
//            if (VERBOSE) Log.d(TAG, "audio decoder: EOS");
//            mAudioDecoderDone = true;
//        }
//        logState();
    }



    public void startCodec() {
        if(null != mediaCodec)
            mediaCodec.start();
    }

    public void stopCodec() {
        if(null != mediaCodec)
            mediaCodec.stop();
    }

    public void resetCodec() {
        if(null != mediaCodec) {
            mediaCodec.reset();
        }
    }

    /*
    public void sync() {
//        mediaCodec.configure(format, …);
        MediaFormat outputFormat = codec.getOutputFormat(); // option B
        mediaCodec.start();
        for (;;) {
            int inputBufferId = mediaCodec.dequeueInputBuffer(timeoutUs);
            if (inputBufferId >= 0) {
                ByteBuffer inputBuffer = mediaCodec.getInputBuffer(…);
                // fill inputBuffer with valid data

//                mediaCodec.queueInputBuffer(inputBufferId, …);
            }
//            int outputBufferId = mediaCodec.dequeueOutputBuffer(…);
            if (outputBufferId >= 0) {
                ByteBuffer outputBuffer = mediaCodec.getOutputBuffer(outputBufferId);
                MediaFormat bufferFormat = mediaCodec.getOutputFormat(outputBufferId); // option A
                // bufferFormat is identical to outputFormat
                // outputBuffer is ready to be processed or rendered.
     …
                mediaCodec.releaseOutputBuffer(outputBufferId, …);
            } else if (outputBufferId == MediaCodec.INFO_OUTPUT_FORMAT_CHANGED) {
                // Subsequent data will conform to new format.
                // Can ignore if using getOutputFormat(outputBufferId)
                outputFormat = mediaCodec.getOutputFormat(); // option B
            }
        }
        mediaCodec.stop();
        mediaCodec.release();
    }
    */

/*
    public void async() {
        MediaFormat mOutputFormat; // member variable
        mediaCodec.setCallback(new MediaCodec.Callback() {
            @Override
            public void onInputBufferAvailable(MediaCodec mc, int inputBufferId) {
                ByteBuffer inputBuffer = codec.getInputBuffer(inputBufferId);
                // fill inputBuffer with valid data

                mediaCodec.queueInputBuffer(inputBufferId, …);
            }

            @Override
            public void onOutputBufferAvailable(@NonNull MediaCodec mediaCodec, int i, @NonNull MediaCodec.BufferInfo bufferInfo) {
                ByteBuffer outputBuffer = codec.getOutputBuffer(outputBufferId);
                MediaFormat bufferFormat = codec.getOutputFormat(outputBufferId); // option A
                // bufferFormat is equivalent to mOutputFormat
                // outputBuffer is ready to be processed or rendered.
                    …
                codec.releaseOutputBuffer(outputBufferId, …);
            }

            @Override
            public void onError(@NonNull MediaCodec mediaCodec, @NonNull MediaCodec.CodecException e) {

            }

            @Override
            public void onOutputFormatChanged(@NonNull MediaCodec mediaCodec, @NonNull MediaFormat mediaFormat) {
                // Subsequent data will conform to new format.
                // Can ignore if using getOutputFormat(outputBufferId)
                mOutputFormat = format; // option B
            }
        });
//        mediaCodec.configure(format, …);
        mOutputFormat = mediaCodec.getOutputFormat(); // option B
        mediaCodec.start();
        // wait for processing to complete
        mediaCodec.stop();
        mediaCodec.release();

    }

*/

    public void processing(Surface surface) {
//        ImageReader imageReader = new ImageReader();
//        surface.
    }

    public byte[] swapYV12toI420(byte[] yv12bytes, int width, int height) {
        byte[] i420bytes = new byte[yv12bytes.length];
        for (int i = 0; i < width*height; i++)
            i420bytes[i] = yv12bytes[i];
        for (int i = width*height; i < width*height + (width/2*height/2); i++)
            i420bytes[i] = yv12bytes[i + (width/2*height/2)];
        for (int i = width*height + (width/2*height/2); i < width*height + 2*(width/2*height/2); i++)
            i420bytes[i] = yv12bytes[i - (width/2*height/2)];
        return i420bytes;
    }
}
