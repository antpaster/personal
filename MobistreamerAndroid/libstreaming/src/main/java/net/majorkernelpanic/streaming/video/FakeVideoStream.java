package net.majorkernelpanic.streaming.video;

import android.annotation.SuppressLint;
import android.content.SharedPreferences;
import android.graphics.ImageFormat;
import android.media.MediaRecorder;
import android.os.Environment;
import android.util.Base64;
import android.util.Log;

import net.majorkernelpanic.streaming.exceptions.ConfNotSupportedException;
import net.majorkernelpanic.streaming.exceptions.StorageUnavailableException;
import net.majorkernelpanic.streaming.hw.EncoderDebugger;
import net.majorkernelpanic.streaming.mp4.MP4Config;
import net.majorkernelpanic.streaming.rtp.H264Packetizer;

import java.io.File;
import java.io.IOException;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

/**
 * Created by alexander on 22.12.15.
 */
public class FakeVideoStream extends VideoStream {

    public final static String TAG = "FakeVideoStream";

    private Semaphore mLock = new Semaphore(0);
    private MP4Config mConfig;

    public static byte spsByte[];
    public static byte ppsByte[];

    public FakeVideoStream() {
        super(0);
        mConfig = new MP4Config(spsByte, ppsByte);
        mMimeType = "video/avc";
        mCameraImageFormat = ImageFormat.NV21;
        mVideoEncoder = MediaRecorder.VideoEncoder.H264;
        mPacketizer = new H264Packetizer();
        mMode = MODE_FAKE_API;

    }

    @Override
    public synchronized String getSessionDescription() throws IllegalStateException {
        mConfig = new MP4Config(spsByte, ppsByte);
        return "m=video "+String.valueOf(getDestinationPorts()[0])+" RTP/AVP 96\r\n" +
               "a=rtpmap:96 H264/90000\r\n" +
               "a=fmtp:96 packetization-mode=0;profile-level-id="+mConfig.getProfileLevel()+";sprop-parameter-sets="+mConfig.getB64SPS()+","+mConfig.getB64PPS()+";\r\n";
    }

    public synchronized void start() throws IllegalStateException, IOException {
        if (!mStreaming) {
            configure();
            byte[] pps = Base64.decode(mConfig.getB64PPS(), Base64.NO_WRAP);
            byte[] sps = Base64.decode(mConfig.getB64SPS(), Base64.NO_WRAP);
            ((H264Packetizer)mPacketizer).setStreamParameters(pps, sps);
            super.start();
        }
    }

    public synchronized void configure() throws IllegalStateException, IOException {
        super.configure();
        mConfig = new MP4Config(spsByte, ppsByte);
    }
}
