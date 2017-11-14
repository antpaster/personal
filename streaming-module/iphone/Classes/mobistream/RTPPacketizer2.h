//
//  RTPPacketizer.h
//  MobiStream
//
//  Created by netris on 04.12.14.
//  Copyright (c) 2014 netris. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface RTPPacketizer : NSObject

- (NSMutableArray *) onAudioData:(NSArray*) data time:(double) pts;
- (NSMutableArray *) onVideoData:(NSArray*) data time:(double) pts;
- (void) initValues;

@end
