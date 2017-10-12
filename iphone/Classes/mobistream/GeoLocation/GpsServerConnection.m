//
//  GpsServerConnection.m
//  MobiStream
//
//  Created by netris on 24.11.15.
//  Copyright © 2015 netris. All rights reserved.
//

#import "GpsServerConnection.h"

@implementation GpsServerConnection
{
    dispatch_queue_t uploadQueue;
    SimpleConnection *gpsconnection;
    BOOL isConnectionConnected;
}

- (id) initWithHost:(NSString *)shost andPort:(int) sport
{
    self = [super init];
    if(nil != self){
        gpsconnection = [[SimpleConnection alloc] initWithHost:shost andPort:sport];
        [gpsconnection setDelegate:self];
    }
    uploadQueue = dispatch_queue_create("ru.netris.upload.gps", NULL);
    return self;
}

-(void)onConnected:(id)connection isConnected:(BOOL) isConnected withError:(NSError *)error
{
    if (gpsconnection == connection) {
        isConnectionConnected = isConnected;
        if(isConnected){
//            [self registerCamera];
        }else{
//            NSLog(@"VideoConnection disconnected");
//            isConnectionConnected = NO;
//            [delegate onVideoRegistered:self is:NO withError:error];
        }
    }
}

-(void)onMessageReceivedString:(NSString*) message fromConnection:(id)connection
{
    
}

- (void) connect
{
    [gpsconnection connect];
}

- (void) disconnect
{
    isConnectionConnected = NO;
    [gpsconnection disconnect];
}

- (NSInteger) write:(NSData *)data
{
    NSLog(@"%@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
    if (isConnectionConnected) {
        return [gpsconnection write:data];
    }
    return 0;
}

@end
