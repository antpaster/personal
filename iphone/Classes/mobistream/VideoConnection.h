//
//  pnpConnection.h
//  MobiStream
//
//  Created by netris on 22.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SimpleConnection.h"
#import "ConnectionDelegate.h"
#import "NetworkUtil.h"
#import "ApplicationErrors.h"
#import "NetworkUtil.h"

@interface VideoConnection : NSObject <SimpleConnectionDelegate>

//@property (nonatomic, strong) SimpleConnection *videoconnection;
@property (nonatomic, strong) NSString *host;
@property (nonatomic) int port;
@property (nonatomic, strong) NSString *channel;
@property (nonatomic, strong) NSString *sdp;

- (id) initWithHost:(NSString *)shost andPort:(int) sport andChannel:(NSString *)schannel andSdp:(NSString *)ssdp;

- (void) setDelegate:(id<ConnectionDelegate>) sdelegate;
- (void) connect;
- (void) disconnect;
- (NSInteger) write:(NSData *)data;
- (NSString *) getHost;
- (int) getPort;

@end
