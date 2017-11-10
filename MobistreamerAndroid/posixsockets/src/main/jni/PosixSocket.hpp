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

class PosixSocket{

private:

    static PosixSocket* sInstance;

    int connectedSocket;

    int NewTcpSocket();
    bool ConnectToAddress(int sd, const char* ip, unsigned short port);
    ssize_t SendToSocket(int sd, const char* buffer, size_t bufferSize);
    void LogMessage(const char* format, ...);

public:

    PosixSocket();
    ~PosixSocket();

    PosixSocket* getInstance();

    bool connectToHost(const char* host, int port);
    bool closeSocket();
    int sendToHost(char *data, int size);
};

/*

static int NewTcpSocket(JNIEnv* env, jobject obj)
{
    // Construct socket
    LogMessage(env, obj, "Constructing a new TCP socket...");
    int cs = socket(PF_INET, SOCK_STREAM, 0);

    // Check if socket is properly constructed
    if (-1 == cs)
    {
        // Throw an exception with error number
        ThrowErrnoException(env, "java/io/IOException", errno);
    }
    return cs;
}

static int ConnectToAddress(JNIEnv* env, jobject obj, int sd, const char* ip, unsigned short port)
{
    // Connecting to given IP address and given port
    LogMessage(env, obj, "Connecting to %s:%uh...", ip, port);

    struct sockaddr_in address;

    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;

    // Convert IP address string to Internet address
    if (0 == inet_aton(ip, &(address.sin_addr))) {
        // Throw an exception with error number
        ThrowErrnoException(env, "java/io/IOException", errno);
    }else{
        // Convert port to network byte order
        address.sin_port = htons(port);
        // Connect to address
        if (-1 == connect(sd, (const struct sockaddr*) &address, sizeof(address))){
            // Throw an exception with error number
            ThrowErrnoException(env, "java/io/IOException", errno);
        }else{
            LogMessage(env, obj, "Connected.");
            return 1;
        }
    }
    return 0;
}

static void BindSocketToPort(JNIEnv* env, jobject obj, int sd, unsigned short port)
{
    struct sockaddr_in address;

    // Address to bind socket
    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;

    // Bind to all addresses
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    // Convert port to network byte order
    address.sin_port = htons(port);

    // Bind socket
    LogMessage(env, obj, "Binding to port %hu.", port);
    if (-1 == bind(sd, (struct sockaddr*) &address, sizeof(address)))
    {
        // Throw an exception with error number
        ThrowErrnoException(env, "java/io/IOException", errno);
    }
}

int nativeStartTcpClient(JNIEnv* env, jobject obj, jstring ip, jint port, jstring message)
{
////////////////
    int cs = NewTcpSocket(env, obj);

//    jclass cls = env->FindClass( "java/lang/Integer");
//    // Get the Method ID of the constructor which takes an int
//    jmethodID midInit = env->GetMethodID( cls, "<init>", "(I)V");
//    if (NULL == midInit) return NULL;
//    // Call back constructor to allocate a new instance, with an int argument
//    jobject newObj = env->NewObject( cls, midInit, cs);
//    clientSocket = env->NewGlobalRef(newObj);

////////////////

    if (NULL == env->ExceptionOccurred()) {
        // Get IP address as C string
        const char *ipAddress = env->GetStringUTFChars( ip, NULL);
        if (NULL == ipAddress)
            //goto exit;
            return 0;

        // Connect to IP address and port
        int res = ConnectToAddress(env, obj, clientSocket, ipAddress, (unsigned short) port);

        // Release the IP address
        env->ReleaseStringUTFChars( ip, ipAddress);

        // If connection was successful
        //    if (NULL != (*env)->ExceptionOccurred(env)) {
        //goto exit;
        //        return 1;
        //    }

        return res;
        //return 0;
        // Get message as C string
//        const char* messageText = env->GetStringUTFChars(message, NULL);
//        if (NULL == messageText)
//            goto exit;

        // Get the message size
//        jsize messageSize = env->GetStringUTFLength(message);
        // Send message to socket
//        SendToSocket(env, obj, clientSocket, messageText, messageSize);
        // Release the message text
//        env->ReleaseStringUTFChars(message, messageText);
        // If send was not successful
//        if (NULL != env->ExceptionOccurred())
//            goto exit;
//        char buffer[MAX_BUFFER_SIZE];
        // Receive from the socket
//        ReceiveFromSocket(env, obj, clientSocket, buffer, MAX_BUFFER_SIZE);
    }

//exit:
//    if (clientSocket > -1){
//        close(clientSocket);
//    }
}

ssize_t SendToSocket(JNIEnv* env, jobject obj, int sd, const char* buffer, size_t bufferSize)
{
    // Send data buffer to the socket
    LogMessage(env, obj, "Sending to the socket...");
    LogMessage(env, obj, "SD: %d", sd);
    ssize_t sentSize = send(sd, buffer, bufferSize, 0);

    LogMessage(env, obj, "Sent %d bytes: %s", sentSize, buffer);

    if (-1 == sentSize) {
        // Throw an exception with error number
        ThrowErrnoException(env, "java/io/IOException", errno);
    }else{
        if (sentSize > 0){
            LogMessage(env, obj, "Sent %d bytes: %s", sentSize, buffer);
        }else{
            LogMessage(env, obj, "Client disconnected.");
        }
    }
    return sentSize;
}

*/