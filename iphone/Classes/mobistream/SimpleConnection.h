//
//  SimpleConnection.h
//  MobiStream
//
//  Created by netris on 22.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SimpleConnectionDelegate.h"
#import "ApplicationErrors.h"

@interface SimpleConnection : NSObject <NSStreamDelegate>

- (id) initWithHost:(NSString*) lhost andPort:(int) lport;
- (void) setDelegate:(id<SimpleConnectionDelegate>)ldelegate;
- (void) connect;
- (void) disconnect;
- (BOOL) isConnected;
- (NSInteger) write:(NSData *)data;

@end
