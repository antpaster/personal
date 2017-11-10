package net.majorkernelpanic.streaming.realm;

import io.realm.RealmObject;

/**
 * Created by alexander on 21.01.16.
 */
public class RTPStackSessionSettings extends RealmObject {

    private int id;
    private String host;
    private int port;
    private String sdp;
    private String channel;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getHost() {
        return host;
    }

    public void setHost(String host) {
        this.host = host;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public String getSdp() {
        return sdp;
    }

    public void setSdp(String sdp) {
        this.sdp = sdp;
    }

    public String getChannel() {
        return channel;
    }

    public void setChannel(String channel) {
        this.channel = channel;
    }
}
