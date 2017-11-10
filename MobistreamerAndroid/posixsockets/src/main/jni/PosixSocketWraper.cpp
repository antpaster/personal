#include "ru_netris_posixsockets_PosixSocketWraper.h"
#include "PosixSocketWraper.hpp"
#include "PosixSocket.hpp"

#include <jni.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stddef.h>

#include <android/log.h>

#define MAX_BUFFER_SIZE 80
#define MAX_LOG_MESSAGE_LENGTH 256

jobject gObj;

//
//int clientSocket;
//
//void ThrowErrnoException(JNIEnv* env, const char* className, int errnum);
//void ThrowException(JNIEnv* env, const char* className, const char* message);
//void LogAddress(JNIEnv* env, jobject obj, const char* message, const struct sockaddr_in* address);
//void LogMessage(JNIEnv* env, jobject obj,const char* format, ...);
//ssize_t SendToSocket(JNIEnv* env, jobject obj, int sd, const char* buffer, size_t bufferSize);

void LogAddress(JNIEnv* env, jobject obj, const char* message, const struct sockaddr_in* address)
{
    char ip[INET_ADDRSTRLEN];

    // Convert the IP address to string
    if (NULL == inet_ntop(PF_INET, &(address->sin_addr), ip, INET_ADDRSTRLEN))
    {
        // Throw an exception with error number
        ThrowErrnoException(env, "java/io/IOException", errno);
    }else{
        // Convert port to host byte order
        unsigned short port = ntohs(address->sin_port);
        // Log address
        LogMessage(env, obj, "%s %s:%hu.", message, ip, port);
    }
}

void LogMessage(JNIEnv* env, jobject obj,const char* format, ...)
{
    char buffer[MAX_LOG_MESSAGE_LENGTH];

    va_list ap;
    va_start(ap, format);
    vsnprintf(buffer, MAX_LOG_MESSAGE_LENGTH, format, ap);
    va_end(ap);

    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", buffer);
}

//void ThrowException(JNIEnv* env, const char* className, const char* message)
//{
    // Get the exception class
//    jclass clazz = env->FindClass(env, className);
//
//    // If exception class is found
//    if (NULL != clazz){
//        // Throw exception
//        env->ThrowNew(env, clazz, message);
//        // Release local class reference
//        env->DeleteLocalRef(env, clazz);
//    }
//}

//void ThrowErrnoException(JNIEnv* env, const char* className, int errnum) {
//    char buffer[MAX_LOG_MESSAGE_LENGTH];
//
//    // Get message for the error number
//    if (-1 == strerror_r(errnum, buffer, MAX_LOG_MESSAGE_LENGTH)) {
//        strerror_r(errno, buffer, MAX_LOG_MESSAGE_LENGTH);
//    }
//
//    // Throw exception
//    ThrowException(env, className, buffer);
//
//    //???
//}
extern "C"{
//JNIEXPORT jstring JNICALL Java_ru_netris_posixsockets_PosixSocketWraper_test1(JNIEnv *env, jobject obj)
jstring Java_ru_netris_posixsockets_PosixSocketWraper_test1(JNIEnv *env, jobject obj)
{
    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "test1");
    return env->NewStringUTF("test1");
}

//JNIEXPORT jstring JNICALL Java_ru_netris_posixsockets_PosixSocketWraper_test2(JNIEnv *env, jobject obj, jint i)
jstring Java_ru_netris_posixsockets_PosixSocketWraper_test2(JNIEnv *env, jobject obj, jint i)
{
    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "test2");
    return env->NewStringUTF("test2");
}

//JNIEXPORT jstring JNICALL Java_ru_netris_posixsockets_PosixSocketWraper_test3(JNIEnv *env, jobject obj, jbyteArray ba)
jstring Java_ru_netris_posixsockets_PosixSocketWraper_test3(JNIEnv *env, jobject obj, jbyteArray ba)
{
    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "test3");
    return env->NewStringUTF("test3");
}
};

extern "C"{

JNIEXPORT jboolean JNICALL Java_ru_netris_posixsockets_PosixSocketWraper_connect(JNIEnv *env, jobject obj, jstring str, jint i)
{
    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "Java_ru_netris_posixsockets_PosixSocketWraper_connect");


    return JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_ru_netris_posixsockets_PosixSocketWraper_close(JNIEnv *env, jobject obj)
{
    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "Java_ru_netris_posixsockets_PosixSocketWraper_close");
//    if (clientSocket > -1){
//        __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "Java_ru_netris_posixsockets_PosixSocketWraper_close2");
//        close(clientSocket);
//        return 1;
//    }
    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "Java_ru_netris_posixsockets_PosixSocketWraper_close3");
    return 0;
}

JNIEXPORT jint JNICALL Java_ru_netris_posixsockets_PosixSocketWraper_send(JNIEnv *env, jobject obj, jbyteArray data, jint size)
{
    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "Java_ru_netris_posixsockets_PosixSocketWraper_send");

    LogMessage(env, obj, "FROM JNI", "CLIENT SOCKET send: %d", clientSocket);
//    int res = SendToSocket(env, obj, clientSocket, (const char *)data, size);
    __android_log_write(ANDROID_LOG_ERROR, "FROM JNI", "Java_ru_netris_posixsockets_PosixSocketWraper_send is SENT!!!");
//    return res;
    return 0;
}
    
};
