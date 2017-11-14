//
//  InterleavedPacketizer.h
//  MobiStream
//
//  Created by netris on 03.12.14.
//  Copyright (c) 2014 netris. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface InterleavedPacketizer : NSObject

+ (NSData *) packetize: (NSData *) data channel:(uint8_t) channel;
+ (NSData *) adtsDataForPacketLength:(NSInteger)packetLength;

@end
