//
//  GpsServerConnection.h
//  MobiStream
//
//  Created by netris on 24.11.15.
//  Copyright © 2015 netris. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SimpleConnection.h"

@interface GpsServerConnection : NSObject<SimpleConnectionDelegate>

@property (nonatomic, strong) NSString *host;
@property (nonatomic) int port;
@property (nonatomic, strong) NSString *channel;
@property (nonatomic, strong) NSString *sdp;

- (id) initWithHost:(NSString *)shost andPort:(int) sport;

- (void) connect;
- (void) disconnect;
- (NSInteger) write:(NSData *)data;
//- (NSString *) getHost;
//- (int) getPort;


@end
