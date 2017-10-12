//
//  SimpleConnection.m
//  MobiStream
//
//  Created by netris on 22.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import "SimpleConnection.h"

@implementation SimpleConnection
{
    id<SimpleConnectionDelegate> delegate;
    CFWriteStreamRef writeStream;
    CFReadStreamRef readStream;
    BOOL isConnectedOutput;
    BOOL isConnectedInput;
    NSString *host;
    int port;

    NSOutputStream *outputStream;
    NSInputStream *inputStream;
}

- (id) initWithHost:(NSString*) lhost andPort:(int) lport
{
    self = [super init];
    if(nil != self){
        host = lhost;
        port = lport;
        isConnectedOutput = NO;
        isConnectedInput = NO;
    }
    return self;
}

- (void) connect
{
    if(![host isEqualToString:@""] && port > 0){
        NSURL *urlAddress = [NSURL URLWithString:host];
        if(!urlAddress){
            [delegate onConnected:self isConnected:NO withError:[ApplicationErrors createErrorInDomain:@"SimpleConnection" code:1000 reason: [NSString stringWithFormat:@"Url is not valid:%@", host]description:[NSString stringWithFormat:@"Url is not valid:%@", host]]];
            return;
        }

        CFStreamCreatePairWithSocketToHost(NULL, (__bridge CFStringRef)host, port, &readStream, &writeStream);
        outputStream = (__bridge_transfer NSOutputStream *) writeStream;

        [outputStream setDelegate:self];
        [outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        [outputStream open];

        inputStream = (__bridge NSInputStream *)(readStream);

        [inputStream setDelegate:self];
        [inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        [inputStream open];
    }
}

- (void) stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode
{
    dispatch_async(dispatch_get_main_queue(), ^(void){
        if(aStream == inputStream){
            [self inputStreamHandleEvent:eventCode];
        }else if(aStream == outputStream){
            [self outputStreamHandleEvent:eventCode];
        }
    });
}

- (NSInteger) write:(NSData *)data
{
    if (outputStream != nil) {
        return [outputStream write:(uint8_t *)[data bytes] maxLength:[data length]];
    }
    return 0;
}

// inputStream
- (void) inputStreamHandleEvent:(NSStreamEvent) eventCode{
    switch (eventCode) {
        case NSStreamEventNone:
            break;
        case NSStreamEventOpenCompleted:
            isConnectedInput = YES;
            [self streamConnected];
            //send message to server

            break;
        case NSStreamEventErrorOccurred:
            isConnectedInput = NO;
            [self streamConnectionLost];
            //reconnect
            break;
        case NSStreamEventEndEncountered:
            break;
        case NSStreamEventHasBytesAvailable:
            uint8_t *input_buffer = (uint8_t *)malloc(2048);
            NSUInteger readCount = 0;
            readCount = [inputStream read:input_buffer maxLength:1024];
            if (0 < readCount) {
                NSString *res = [[NSString alloc] initWithBytes:input_buffer length:readCount encoding:NSUTF8StringEncoding];//swift 2
                [delegate onMessageReceivedString:res fromConnection:self];
            }
            if(NULL != input_buffer){
                free(input_buffer);
            }
            break;
    }
}

// outputStream
- (void) outputStreamHandleEvent:(NSStreamEvent) eventCode{
    switch (eventCode) {
        case NSStreamEventNone:
            break;
        case NSStreamEventOpenCompleted:
            isConnectedOutput = YES;
            [self streamConnected];
            break;
        case NSStreamEventHasSpaceAvailable:
            break;
        case NSStreamEventErrorOccurred:
            isConnectedOutput = NO;
            [self streamConnectionLost];
            //reconnecting
            break;
        case NSStreamEventEndEncountered:
            break;
        default:
            break;
    }
}

- (void) streamConnectionLost
{
    if(!isConnectedOutput || !isConnectedInput){
        [self disconnect];
    }
}

- (void) streamConnected
{
    if (isConnectedInput && isConnectedOutput) {
        [delegate onConnected:self isConnected:YES withError:nil];
    }
}

- (void) disconnect
{
    isConnectedInput = NO;
    isConnectedOutput = NO;
    [outputStream close];
    [inputStream close];
    if (writeStream != nil) {
        CFWriteStreamClose(writeStream);
    }
    if (readStream != nil) {
        CFReadStreamClose(readStream);
    }
    outputStream = nil;
    inputStream = nil;
    writeStream = nil;
    readStream = nil;
    [delegate onConnected:self isConnected:NO withError:[ApplicationErrors createErrorInDomain:@"SimpleConnection" code:1000 reason: [NSString stringWithFormat:@"Disconnected from %@:%d", host, port]description:[NSString stringWithFormat:@"Disconnected from %@:%d", host, port]]];
}

-(void) setDelegate:(id<SimpleConnectionDelegate>)ldelegate
{
    delegate = ldelegate;
}

- (BOOL) isConnected
{
    return (isConnectedInput && isConnectedOutput);
}

@end
