package com.example.apasternak.videotoserver;

import android.provider.MediaStore;
import android.util.Size;

/**
 * Created by apasternak on 07.11.17.
 */

public interface MobiServiceable {

    enum VideoSize {
        SIZE_1280_720,
        SIZE_640_480,
        SIZE_352_288
    }

    enum VideoBitrate {
        KBPS_140,
        KBPS_280,
        KBPS_560,
        KBPS_700,
        KBPS_1000,
        KBPS_1500,
        KBPS_2500,
        KBPS_3500,
        KBPS_3750,
        KBPS_5000
    }

    enum StreamMode {
        VIDEO_MODE,
        AUDIO_VIDEO_MODE,
        AUDIO_MODE
    }

    enum MobiOrientation {
        LANDSCAPE_LEFT,
        PORTRAIT,
        LANDSCAPE_RIGHT,
        PORTRAIT_UPSIDE_DOWN
    }

    enum StateEvent {
        NONE_STATE,
        CONNECTING_STATE,
        RUNNING_STATE,
        STOP_STATE,
        ERROR_STATE
    }

    enum SignalStateEvent {
        FIRST_IDR_SIGNAL,
        BUFFER_OVERFLOW_SIGNAL
    }

    enum TestEvent {
        NONE_TEST_STATUS,
        ONGOING_TEST_STATUS,
        DONE_TEST_STATUS
    }

//    VideoSize mVideoSize = VideoSize.SIZE_352_288;
//    VideoBitrate mVideoBitrate = VideoBitrate.KBPS_140;
//    int mVideoFramerate = 25;
//    StreamMode mStreamMode = StreamMode.AUDIO_VIDEO_MODE;
//    MobiOrientation mOrientation = MobiOrientation.LANDSCAPE_LEFT;

    void initVideoServiceWithHost(String hostPort, int streamNumber);

    void configureCamera();
    void startCamera();
    void stopCamera();
    void switchCamera();
    void updateFrame();

    boolean hasTorch();
    void toggleTorch();

    void onStateEvent(StateEvent stateEvent);
    void onSignalStateEvent(SignalStateEvent signalStateEvent);
    void onTestEvent(TestEvent testEvent);
}
