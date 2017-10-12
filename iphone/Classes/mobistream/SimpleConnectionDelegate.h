//
//  SimpleConnectionDelegate.h
//  MobiStream
//
//  Created by netris on 22.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SimpleConnectionDelegate

@required

-(void)onConnected:(id)connection isConnected:(BOOL) isConnected withError:(NSError*)error;
-(void)onMessageReceivedString:(NSString*) message fromConnection:(id)connection;

@optional

-(void)onMessageReceived:(NSData*) message;

@end
