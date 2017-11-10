//
// Created by alexander on 26.01.16.
//

#ifndef MOBISTREAM_SENDERSOCKET_H
#define MOBISTREAM_SENDERSOCKET_H

#include <jni.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stddef.h>

#include <android/log.h>
#include <stdexcept>

#define MAX_BUFFER_SIZE 80
#define MAX_LOG_MESSAGE_LENGTH 256

class SenderSocket {
private:

    int connectedSocket;
    int NewTcpSocket();
    bool ConnectToAddress(int sd, const char* ip, unsigned short port);
    ssize_t SendToSocket(int sd, const char* buffer, size_t bufferSize);
    void LogMessage(const char* format, ...);

public:

    SenderSocket();
    ~SenderSocket();

    bool connectToHost(const char* host, int port);
    bool closeSocket();
    int sendToHost(char *data, size_t len);
    int readFromHost(char *data, size_t len);
};

#endif //MOBISTREAM_SENDERSOCKET_H
