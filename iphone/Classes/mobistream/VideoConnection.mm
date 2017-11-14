//
//  VideoConnection.m
//  MobiStream
//
//  Created by netris on 22.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import "VideoConnection.h"

@implementation VideoConnection
{
    id<ConnectionDelegate> delegate;

    BOOL isConnectionConnected;
    BOOL isRegisteringProcess;

    dispatch_queue_t uploadQueue;
    
    SimpleConnection *videoconnection;
}

- (id) initWithHost:(NSString *)shost andPort:(int) sport andChannel:(NSString *)schannel andSdp:(NSString *)ssdp
{
    self.host = shost;
    self.port = sport;
    self.channel = schannel;
    self.sdp = ssdp;
    self = [super init];
    if(nil != self){
        [delegate onStatus:CONNECTION_STATUS_OPENING_VIDEO_STREAM connection:self];
        videoconnection = [[SimpleConnection alloc] initWithHost:shost andPort:sport];
        [videoconnection setDelegate:self];
    }

    uploadQueue = dispatch_queue_create("ru.netris.upload", NULL);
    return self;
}

- (void) registerCamera
{
    NSString* registerQueryString = [self makeRegisterServerQueryString];
    isRegisteringProcess = YES;
    [videoconnection write:[registerQueryString dataUsingEncoding:NSUTF8StringEncoding]];
}

- (NSString *) makeRegisterServerQueryString
{
    NSMutableString *body = [[NSMutableString alloc] initWithString:@""];
    [body appendString:@"{\"action\":\"register_camera\","];
    [body appendString:@"\"parameters\":{"];
    [body appendFormat:@"\"channelid\":\"%@\",", self.channel];
    [body appendFormat:@"\"ip\":\"%@\",", [NetworkUtil getIPAddress]];
    [body appendString:@"\"sdp\":\""];
    NSMutableString *sdpString = [[NSMutableString alloc] initWithString:self.sdp];
    NSString *sdp_repl = [sdpString stringByReplacingOccurrencesOfString:@"\r\n" withString:@"\\\\r\\\\n"];
    [body appendString:sdp_repl];
    [body appendString:@"\"}}"];

    NSString *strLen = [NSString stringWithFormat:@"%lu",(unsigned long)[body length]];

    NSMutableString *str = [[NSMutableString alloc] initWithString:@""];
    [str appendString:@"POST /api HTTP/1.1\r\nConnection: keep-alive\r\n"];
    [str appendFormat:@"Content-Length: %@\r\n",strLen];
    [str appendString:@"Content-Type: application/json\r\n"];
    [str appendFormat:@"Host: %@:%d\r\n", self.host, self.port];
    [str appendString:@"User-Agent: iOSVideo\r\n\r\n"];
    [str appendString:body];
    return str;
}

-(BOOL) isMessageRegisterCameraOk:(NSString *)message
{
    NSLog(@"%@", message);
    if([message containsString:@"\"action\":\"get_video\""] && [message containsString:@"\"success\":true"]){
        return YES;
    }
    return NO;
}

-(void)onConnected:(id)connection isConnected:(BOOL) isConnected withError:(NSError *)error
{
    if (videoconnection == connection) {
        isConnectionConnected = isConnected;
        if(isConnected){
            [self registerCamera];
        }else{
            NSLog(@"VideoConnection disconnected");
            isConnectionConnected = NO;
            [delegate onVideoRegistered:self connected:NO withError:error];
        }
    }
}

-(void)onMessageReceivedString:(NSString*) message fromConnection:(id)connection
{
    if(isRegisteringProcess){
        isRegisteringProcess = NO;
        if([self isMessageRegisterCameraOk:message]){
            [delegate onVideoRegistered:self connected:YES withError:nil];
        }else{
            NSError *error = nil;
            if(nil != message){
                NSString *str = [message substringFromIndex:[message rangeOfString:@"\r\n\r\n"].location + [message rangeOfString:@"\r\n\r\n"].length];
                NSLog(@"VideoConnection recieve: %@", str);
                error = [ApplicationErrors createErrorInDomain:@"VideoConnection" code:1000 reason: [NSString stringWithFormat:@"Server not registered camera. Answer from server: %@", str] description:[NSString stringWithFormat:@"Server not registered camera. Answer from server: %@", str]];
            }
            [delegate onVideoRegistered:self connected:NO withError:error];
        }
    }
}

- (NSString *) getHost
{
    return self.host;
}

- (int) getPort
{
    return self.port;
}

- (void) setDelegate:(id<ConnectionDelegate>) sdelegate
{
    delegate = sdelegate;
}

- (void) connect
{
    [videoconnection connect];
}

- (void) connectWithSdp:(NSString *)_sdp
{
    [videoconnection connect];
}

- (void) disconnect
{
    isRegisteringProcess = NO;
    [videoconnection disconnect];
}

- (NSInteger) write:(NSData *)data
{
    return [videoconnection write:data];
}

@end
