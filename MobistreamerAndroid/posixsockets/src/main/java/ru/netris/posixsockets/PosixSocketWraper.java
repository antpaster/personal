package ru.netris.posixsockets;

/**
 * Created by alexander on 11.01.16.
 */
public class PosixSocketWraper {


    static {
        System.loadLibrary("PosixSocketWraper");
    }
    public native String test1();
    public native String test2(int val);
    public native String test3(byte [] arr);


    public native boolean connect(String host, int port);
    public native boolean close();
    public native int send(byte[] data, int size);
    public native int read(byte[] data, int size);

}
