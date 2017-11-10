package net.majorkernelpanic.streaming.realm;

import java.io.IOException;

/**
 * Created by alexander on 15.01.16.
 */
public interface DataSenderInterface {

    void writeToBuffer(byte[] head, byte[] buffer, int offset, int count);
    void writeToBuffer(byte[] buffer);

}
