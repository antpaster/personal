package ru.netris.mobistreamer.modules.video.network;

import android.util.Log;

import net.majorkernelpanic.streaming.network.MySemafor;

import java.io.UnsupportedEncodingException;

import ru.netris.posixsocket.NativeSocketClient;

//import ru.netris.nativesocket.java.NativeSocketClient;

/**
 * Created by ps on 29.08.17.
 */

public class IStreamConnection {

    public static final String TAG = "IStreamConnection";
    public static final String STATIC_HOST = "194.135.112.71";
    public static final int STATIC_PORT = 2021;
    public static final String STATIC_STREAM = "67";

    public interface Callback {
        void onConnected();
        void onDisconnected();
    }

    public Callback callback = null;

    public NativeSocketClient socketClient = null;

    public String host = "0.0.0.0";
    public int port = 0;
    public String stream = "0";

    public String sdp = "";

    public IStreamConnection(String host, int port, Callback callback) {
        this.host = host;
        this.port = port;
        this.stream = stream;
        this.callback = callback;
    }

    public void connect() {
        NativeSocketClient.HOST = this.host;
        NativeSocketClient.PORT = this.port;
        NativeSocketClient.getInstance().connect(new NativeSocketClient.CallbackConnection() {
            @Override
            public void connectedStream(boolean isConnect) {

            }
        });
    }

    public void registerCamera(String sdp) {
        this.sdp = sdp;


        String tempSdp = "v=0\\\\r\\\\no=- 1265171593 1265171593 IN IP4 172.17.1.20\\\\r\\\\ns=Live stream from iOS\\\\r\\\\nc=IN IP4 0.0.0.0\\\\r\\\\nt=0 0\\\\r\\\\nm=video 0 RTP/AVP 96\\\\r\\\\na=rtpmap:96 H264/90000\\\\r\\\\na=fmtp:96 packetization-mode=0;profile-level-id=303041;sprop-parameter-sets=J00AHqtAUB7TUCAgKkCA,KO48MA==\\\\r\\\\ni=h264\\\\r\\\\na=control:track=0\\\\r\\\\na=control:trackID=0\\\\r\\\\nm=audio 0 RTP/AVP 97\\\\r\\\\na=rtpmap:97 mpeg4-generic/44100\\\\r\\\\na=fmtp:97 streamtype=5; profile-level-id=15; mode=AAC-hbr; config=1210; SizeLength=13; IndexLength=3; IndexDeltaLength=3\\\\r\\\\na=control:track=2\\\\r\\\\na=control:trackID=2\\\\r\\\\n";


        String request = getRequestString(tempSdp);

        synchronized (MySemafor.semafor) {
            try {
                int res = NativeSocketClient.getInstance().writeToBuffer(request.getBytes("UTF-8"));
                Log.d(TAG,"Register camera:" + res);
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
            }
//            int res = TCPNativeClient.getInstance().writeToBuffer(request.getBytes("UTF-8"));
//            Log.e(TAG,"RTSP POST:" + res);

        }



        byte []a = new byte[2048];
        int answerCount = NativeSocketClient.getInstance().readFromBuffer(a);

        byte []answer = new byte[answerCount];
        System.arraycopy(a, 0, answer, 0, answerCount);

        if(answerCount > 0) {
            String answ = new String(answer);
            Log.d(TAG,"Server answer:" + answ);
        }else{
            Log.e(TAG,"Server answer: 0");
        }

    }

    public String getRequestString(String sdp) {
        this.stream = IStreamConnection.STATIC_STREAM;


        String reqStart = "{\"action\":\"register_camera\","
                + "\"parameters\":{"
                + "\"channelid\":\""+this.stream+"\","
                + "\"ip\":\"172.0.0.1\", "
                + "\"sdp\":\"";
        String reqEnd = "\"}}";
//        String body = mParameters.session.getSessionDescription();
        String str = reqStart +
                sdp +  //.replaceAll("\r\n", "\\\\r\\\\n")
                reqEnd;

        String request = "POST /api HTTP/1.1\r\n" +
                "Connection: keep-alive\r\n" +
                "Content-Length: " + str.length() + "\r\n" +
                "Content-Type: application/json \r\n" +
                "Host: pnp.netris.ru:2032 \r\n" +
                "User-Agent: AndroidVideo \r\n\r\n" +
                str
                ;

        return request;
    }

    public String readAnswer() {
        return "";
    }

    public void disconnect() {

    }

    public void send() {

    }


}
