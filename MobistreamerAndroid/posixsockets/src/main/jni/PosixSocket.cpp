#include "PosixSocket.hpp"

#define MAX_BUFFER_SIZE 80
#define MAX_LOG_MESSAGE_LENGTH 256

PosixSocket* PosixSocket::sInstance;

PosixSocket* PosixSocket::getInstance(){
    if(sInstance == nullptr){
        sInstance = new PosixSocket();
    }
    return sInstance;
}

PosixSocket::PosixSocket(){

}

PosixSocket::~PosixSocket(){
    if (connectedSocket > -1){
        closeSocket();
        connectedSocket = -1;
    }
}

bool PosixSocket::connectToHost(const char* host, int port){
    int cs = NewTcpSocket();
    if (NULL == host)
        return false;
    int res = ConnectToAddress(connectedSocket, host, (unsigned short) port);
    return res;
}

bool PosixSocket::closeSocket(){
    if (connectedSocket > -1){
        __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "Java_ru_netris_posixsockets_PosixSocketWraper_close2");
        return close(connectedSocket);
        //return true;
    }
    return false;
}

int PosixSocket::sendToHost(char *data, int size){
    int sended = SendToSocket(data,size);
    LogMessage("Sended %d bytes",sended);
    return sended;
}

int PosixSocket::NewTcpSocket()
{
    LogMessage("Constructing a new TCP socket...");
    int cs = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == cs) {
        //throw IOException;
        // Throw an exception with error number
//        ThrowErrnoException(env, "java/io/IOException", errno);
    }
    return cs;
}

bool PosixSocket::ConnectToAddress(int sd, const char* host, unsigned short port)
{
    // Connecting to given IP address and given port
    LogMessage("Connecting to %s:%uh...", host, port);

    struct sockaddr_in address;

    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;

    // Convert IP address string to Internet address
    if (0 == inet_aton(host, &(address.sin_addr))) {
        // Throw an exception with error number
//        ThrowErrnoException(env, "java/io/IOException", errno);
    }else{
        // Convert port to network byte order
        address.sin_port = htons(port);
        // Connect to address
        if (-1 == connect(sd, (const struct sockaddr*) &address, sizeof(address))){
            // Throw an exception with error number
//            ThrowErrnoException(env, "java/io/IOException", errno);
        }else{
            LogMessage("Connected.");
            return true;
        }
    }
    return false;
}

ssize_t PosixSocket::SendToSocket(int sd, const char* buffer, size_t bufferSize)
{
    // Send data buffer to the socket
    LogMessage("Sending to the socket...");
    LogMessage("SD: %d", sd);
    ssize_t sentSize = send(sd, buffer, bufferSize, 0);

    LogMessage("Sent %d bytes: %s", sentSize, buffer);

    if (-1 == sentSize) {
        // Throw an exception with error number
//        ThrowErrnoException(env, "java/io/IOException", errno);
    }else{
        if (sentSize > 0){
            LogMessage("Sent %d bytes: %s", sentSize, buffer);
        }else{
            LogMessage("Client disconnected.");
        }
    }
    return sentSize;
}

void PosixSocket::LogMessage(const char* format, ...)
{
    char buffer[MAX_LOG_MESSAGE_LENGTH];
    va_list ap;
    va_start(ap, format);
    vsnprintf(buffer, MAX_LOG_MESSAGE_LENGTH, format, ap);
    va_end(ap);
    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", buffer);
}


