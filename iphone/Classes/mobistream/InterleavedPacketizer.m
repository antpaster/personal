//
//  InterleavedPacketizer.m
//  MobiStream
//
//  Created by netris on 03.12.14.
//  Copyright (c) 2014 netris. All rights reserved.
//

#import "InterleavedPacketizer.h"

/*
0x24 | 0x00    | 0x00 0x00
 $   | channel | packet size
*/
// 0 - video
// 2 - audio

@implementation InterleavedPacketizer

+ (NSData *) packetize: (NSData *) data channel:(uint8_t) channel
{
    uint8_t header[4] = {0x24, 0x00, 0x00, 0x00};
    header[1] = (uint8_t)channel;
    unsigned int dataSize = (unsigned int)[data length];

    header[2] = (dataSize >> 8);
    header[3] = (dataSize & 0xFF);
    
    NSMutableData *packet = [[NSMutableData alloc] initWithBytes:header length:4];
    [packet appendData:data];
    return packet;
}

/**
 *  Add ADTS header at the beginning of each and every AAC packet.
 *  This is needed as MediaCodec encoder generates a packet of raw
 *  AAC data.
 *
 *  Note the packetLen must count in the ADTS header itself.
 *  See: http://wiki.multimedia.cx/index.php?title=ADTS
 *  Also: http://wiki.multimedia.cx/index.php?title=MPEG-4_Audio#Channel_Configurations
 **/
+ (NSData *) adtsDataForPacketLength:(NSInteger)packetLength {
    int adtsLength = 7;
    char *packet = malloc(sizeof(char) * adtsLength);
    // Variables Recycled by addADTStoPacket
    int profile = 2;  //AAC LC
    //39=MediaCodecInfo.CodecProfileLevel.AACObjectELD;
    int freqIdx = 4;  //44.1KHz
    int chanCfg = 1;  //MPEG-4 Audio Channel Configuration. 1 Channel front-center
    NSUInteger fullLength = adtsLength + packetLength;
    // fill in ADTS data
    packet[0] = (char)0xFF;	// 11111111  	= syncword
    packet[1] = (char)0xF9;	// 1111 1 00 1  = syncword MPEG-2 Layer CRC
    packet[2] = (char)(((profile-1)<<6) + (freqIdx<<2) +(chanCfg>>2));
    packet[3] = (char)(((chanCfg&3)<<6) + (fullLength>>11));
    packet[4] = (char)((fullLength&0x7FF) >> 3);
    packet[5] = (char)(((fullLength&7)<<5) + 0x1F);
    packet[6] = (char)0xFC;
    NSData *data = [NSData dataWithBytesNoCopy:packet length:adtsLength freeWhenDone:YES];
    return data;
}

@end
