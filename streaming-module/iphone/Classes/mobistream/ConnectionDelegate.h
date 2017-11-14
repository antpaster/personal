//
//  ConnectionDelegate.h
//  MobiStream
//
//  Created by netris on 02.12.14.
//  Copyright (c) 2014 netris. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ConnectionDelegate

@required

- (void) onStatus:(int)status connection:(id) connection;

@optional

- (void) onVideoRegistered:(id)connection connected:(BOOL)isRegister withError:(NSError *)error;
- (void) onPnpRegisteredGetActions:(id)connection data:(id)data error:(NSError *)error; // если data равна nil то нешмагла соединиться

- (void) onReconnected:(id)connection reconnected:(BOOL)reconnected;
- (void) onVideoDataNotSended;

- (void) registeringCamera;
- (void) registeringCamera:(id)connection;

- (void) connectingCamera;
- (void) connectedCamera:(BOOL)isConnected;
- (void) connectedCamera;
- (void) registeredCamera;
- (void) openedVideoStream;
- (void) connectingCamera:(id)connection;
- (void) connectedCamera:(id)connection connected:(BOOL)isConnected;
- (void) openingVideoStream:(id)connection;
- (void) openingVideoStream;
- (void) openedVideoStream:(id)connection connected:(BOOL)isConnected;

@end

