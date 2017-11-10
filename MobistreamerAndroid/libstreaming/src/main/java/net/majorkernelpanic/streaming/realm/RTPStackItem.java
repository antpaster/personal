package net.majorkernelpanic.streaming.realm;

import io.realm.RealmObject;
import io.realm.annotations.Ignore;
import io.realm.annotations.Required;

/**
 * Created by alexander on 13.01.16.
 */
public class RTPStackItem extends RealmObject {

    private RTPStackSessionSettings rtpSession;
    private long rtpNumber;
    private long rtpTimeStamp;
    private byte[] rtpData;

    public RTPStackSessionSettings getRtpSession() {
        return rtpSession;
    }

    public void setRtpSession(RTPStackSessionSettings rtpSession) {
        this.rtpSession = rtpSession;
    }

    public long getRtpNumber() {
        return rtpNumber;
    }

    public void setRtpNumber(long rtpNumber) {
        this.rtpNumber = rtpNumber;
    }

    public long getRtpTimeStamp() {
        return rtpTimeStamp;
    }

    public void setRtpTimeStamp(long rtpTimeStamp) {
        this.rtpTimeStamp = rtpTimeStamp;
    }

    public byte[] getRtpData() {
        return rtpData;
    }

    public void setRtpData(byte[] rtpData) {
        this.rtpData = rtpData;
    }
}
