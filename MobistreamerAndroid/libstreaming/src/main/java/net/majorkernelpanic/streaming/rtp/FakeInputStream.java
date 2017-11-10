package net.majorkernelpanic.streaming.rtp;

import android.media.MediaCodec;
import android.media.MediaCodec.BufferInfo;
import android.os.Build;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;

/**
 * Created by alexander on 17.12.15.
 */
public class FakeInputStream extends MediaCodecInputStream {

    public static byte[] fakeBuffer;
    private ByteBuffer mBuffer = null;
    private BufferInfo mBufferInfo;

    private boolean mClosed = false;

    int counter = 0;
    public static byte [] spsByte = null;
    public static byte [] ppsByte = null;
    public static byte [] frameByte = null;

    private ByteBuffer spsBuffer = null;
    private ByteBuffer ppsBuffer = null;
    private ByteBuffer frameBuffer = null;

    public FakeInputStream(MediaCodec mediaCodec) {
        super(mediaCodec);

        mClosed = false;

        spsBuffer = ByteBuffer.wrap(spsByte);
        ppsBuffer = ByteBuffer.wrap(ppsByte);
        frameBuffer = ByteBuffer.wrap(frameByte);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN) {
            mBufferInfo = new BufferInfo();
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN) {
            mBufferInfo.presentationTimeUs = 100000;
        }
    }

    @Override
    public int read() throws IOException {
        int res = 0;
        try {
            if (mBuffer == null) {
                if (!Thread.interrupted() && !mClosed) {
                    switch (counter) {
                        case 0:
                            mBuffer = spsBuffer;
                            break;
                        case 1:
                            mBuffer = ppsBuffer;
                            break;
                        case 2:
                            mBuffer = frameBuffer;
                            break;
                    }
                    mBuffer.position(0);
                }
            }
            res = mBuffer.get();
            int size = 0;
            switch (counter) {
                case 0:
                    size = spsByte.length;
                    break;
                case 1:
                    size = ppsByte.length;
                    break;
                case 2:
                    size = frameByte.length;
                    break;
            }
            if (mBuffer.position() >= size) {
                mBuffer = null;
                if (counter >= 2) {
                    counter = 0;
                } else {
                    counter++;
                }
            }
        } catch (RuntimeException e) {
            e.printStackTrace();
        }

//      Log.w("FakeInputStream", "" + res);
        return res;
    }

    @Override
    public int read(byte[] buffer, int offset, int length) throws IOException {
        int min = 0;

        try {
            if (mBuffer == null) {
                if (!Thread.interrupted() && !mClosed) {
                    switch (counter) {
                        case 0:
                            mBuffer = ByteBuffer.wrap(spsByte);
                            break;
                        case 1:
                            mBuffer = ByteBuffer.wrap(ppsByte);
                            break;
                        case 2:
                            mBuffer = ByteBuffer.wrap(frameByte);
                            break;
                    }
                    mBuffer.position(0);
                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN) {
                        mBufferInfo.presentationTimeUs = mBufferInfo.presentationTimeUs + 1000;
                    }
                }
            }
            if (mClosed) throw new IOException("This InputStream was closed");
                try {
                    if(!Thread.interrupted())
                        Thread.sleep(10);
                } catch (InterruptedException e) {
//                    e.printStackTrace();
                   // return 0;
                }
                switch (counter){
                    case 0:
                        min = length < spsByte.length - mBuffer.position() ? length : spsByte.length - mBuffer.position();
                        break;
                    case 1:
                        min = length < ppsByte.length - mBuffer.position() ? length : ppsByte.length - mBuffer.position();
                        break;
                    case 2:
                        min = length < frameByte.length - mBuffer.position() ? length : frameByte.length - mBuffer.position();
                        break;
                }

                mBuffer.get(buffer, offset, min);

                int size = 0;
                switch (counter){
                    case 0:
                        size =spsByte.length;
                        break;
                    case 1:
                        size =ppsByte.length;
                        break;
                    case 2:
                        size =frameByte.length;
                        break;
                }
                if (mBuffer.position() >= size) {
                    mBuffer = null;
                    if(counter >= 2 ){
                        counter = 0;
                    }else{
                        counter++;
                    }
                }
            } catch (RuntimeException e) {
                e.printStackTrace();
            }

        return min;
    }

    public static String byteArrayToHex(byte[] a) {
        StringBuilder sb = new StringBuilder(a.length * 2);
        for(byte b: a)
            sb.append(String.format("%02x ", b & 0xff));
        return sb.toString();
    }

    @Override
    public void close() {
        mClosed = true;
    }

    public int available() {
        if (mBuffer != null) {
            int size = 0;
            switch (counter){
                case 0:
                    size =spsByte.length;
                    break;
                case 1:
                    size =ppsByte.length;
                    break;
                case 2:
                    size =frameByte.length;
                    break;
            }
            return size - mBuffer.position();
        }else {
            return 0;
        }
    }

    public BufferInfo getLastBufferInfo() {
        return mBufferInfo;
    }
}
