//
// Created by alexander on 26.01.16.
//

#include "SenderSocket.h"



int SenderSocket::NewTcpSocket(){
    LogMessage("Constructing a new TCP socket...");
    int cs = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == cs) {
        //throw IOException;
        // Throw an exception with error number
        //        ThrowErrnoException(env, "java/io/IOException", errno);
    }
    return cs;
}

bool SenderSocket::ConnectToAddress(int sd, const char* host, unsigned short p){
    // Connecting to given IP address and given port
    LogMessage("Connecting to %s:%d...", host, p);
    
    struct sockaddr_in address;
    
    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    
    // Convert IP address string to Internet address
    if (0 == inet_aton(host, &(address.sin_addr))) {
        // Throw an exception with error number
        //        ThrowErrnoException(env, "java/io/IOException", errno);
        LogMessage("Nod Connected to %s:%d...", host, p);
    }else{
        // Convert port to network byte order
        address.sin_port = htons(p);
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

ssize_t SenderSocket::SendToSocket(int sd, const char* buffer, size_t bufferSize){
    // Send data buffer to the socket
    ssize_t sentSize = send(sd, buffer, bufferSize, 0);
    
    if (-1 == sentSize) {
        // Throw an exception with error number
        //        ThrowErrnoException(env, "java/io/IOException", errno);
        LogMessage("Error: %d", errno);
    }else{
        if (sentSize > 0){
            //    LogMessage("Sent %d bytes: %s", sentSize, buffer);
        }else{
            LogMessage("Client disconnected.");
        }
    }
    return sentSize;
}

void SenderSocket::LogMessage(const char* format, ...){
    char buffer[MAX_LOG_MESSAGE_LENGTH];
    
    va_list ap;
    va_start(ap, format);
    vsnprintf(buffer, MAX_LOG_MESSAGE_LENGTH, format, ap);
    va_end(ap);
    
    //    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", buffer);
}

SenderSocket::SenderSocket(){
    LogMessage("SenderSocket::SenderSocket()");
}

SenderSocket::~SenderSocket(){
    LogMessage("SenderSocket::~SenderSocket()");
    if (connectedSocket > -1){
        closeSocket();
        connectedSocket = -1;
    }
}

bool SenderSocket::connectToHost(const char* host, int p){
    connectedSocket = NewTcpSocket();
    if (NULL == host)
        return false;
    int res = ConnectToAddress(connectedSocket, host, (unsigned short) p);
    return res;
}

bool SenderSocket::closeSocket(){
    LogMessage("bool SenderSocket::closeSocket()");
    if (connectedSocket > -1){
        //        __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "Java_ru_netris_posixsockets_PosixSocketWraper_close2");
        return close(connectedSocket);
    }
    return false;
}

int SenderSocket::sendToHost(const char data[], size_t len){
    //   LogMessage("int SenderSocket::sendToHost(char *data, int size)");
    int sended = SendToSocket(connectedSocket, &data[0],len);
    //  LogMessage("Sended %d bytes",sended);
    return sended;
}

int SenderSocket::readFromHost(char data[], size_t len){

     int bytesRead = 0;
     int result;
     while (bytesRead < len)
     {
         result = read(connectedSocket, data + bytesRead, len - bytesRead);
         if (result < 1 )
         {
            break;
             // Throw your error.
         }

         bytesRead += result;
     }
     return bytesRead;


//    ssize_t sentSize = send(sd, buffer, bufferSize, 0);

//        if (-1 == sentSize) {
            // Throw an exception with error number
            //        ThrowErrnoException(env, "java/io/IOException", errno);
//            LogMessage("Error: %d", errno);
//        }else{
//            if (sentSize > 0){
                //    LogMessage("Sent %d bytes: %s", sentSize, buffer);
//            }else{
//                LogMessage("Client disconnected.");
//            }
//        }
//        return sentSize;



}
