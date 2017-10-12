//
//  RTPPacketizer.h
//  MobiStream
//
//  Created by netris on 04.12.14.
//  Copyright (c) 2014 netris. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@protocol RTPPacketizerDelegate <NSObject>

- (void) startingAtFirstIDR;

@end

@interface RTPPacketizer : NSObject

@property long lastPacketTs;

@property (weak, nonatomic) id<RTPPacketizerDelegate> delegate;

- (NSMutableArray *) onAudioData:(NSArray*) data time:(double) pts;
- (NSMutableArray *) onVideoData:(NSArray*) data time:(double) pts;
- (void) initValues;

@end
