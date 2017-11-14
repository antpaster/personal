//
//  RTPPacketizer.m
//  MobiStream
//
//  Created by netris on 04.12.14.
//  Copyright (c) 2014 netris. All rights reserved.
//

#import "RTPPacketizer.h"
#import "NALUnit.h"
//#import "arpa/inet.h"

static const int MTU = 1300;
//static const int RTP_HEADER_LENGTH = 12;
static const int MAX_PACKET_SIZE = MTU - 28;
static const char* Base64Mapping = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const int max_packet_size = MAX_PACKET_SIZE;

static void tonet_short(uint8_t* p, unsigned short s)
{
    p[0] = (s >> 8) & 0xff;
    p[1] = s & 0xff;
}

static void tonet_long(uint8_t* p, unsigned long l)
{
    p[0] = (l >> 24) & 0xff;
    p[1] = (l >> 16) & 0xff;
    p[2] = (l >> 8) & 0xff;
    p[3] = l & 0xff;
}

static NSString* encodeLong(unsigned long val, int nPad)
{
    char ch[4];
    int cch = 4 - nPad;
    for (int i = 0; i < cch; i++)
    {
        int shift = 6 * (cch - (i+1));
        int bits = (val >> shift) & 0x3f;
        ch[i] = Base64Mapping[bits];
    }
    for (int i = 0; i < nPad; i++)
    {
        ch[cch + i] = '=';
    }
    NSString* s = [[NSString alloc] initWithBytes:ch length:4 encoding:NSUTF8StringEncoding];
    return s;
}

static NSString* encodeToBase64(NSData* data)
{
    NSString* s = @"";

    const uint8_t* p = (const uint8_t*) [data bytes];
    int cBytes = (int)[data length];
    while (cBytes >= 3)
    {
        unsigned long val = (p[0] << 16) + (p[1] << 8) + p[2];
        p += 3;
        cBytes -= 3;

        s = [s stringByAppendingString:encodeLong(val, 0)];
    }
    if (cBytes > 0)
    {
        int nPad;
        unsigned long val;
        if (cBytes == 1)
        {
            // pad 8 bits to 2 x 6 and add 2 ==
            nPad = 2;
            val = p[0] << 4;
        }
        else
        {
            // must be two bytes -- pad 16 bits to 3 x 6 and add one =
            nPad = 1;
            val = (p[0] << 8) + p[1];
            val = val << 2;
        }
        s = [s stringByAppendingString:encodeLong(val, nPad)];
    }
    return s;
}

enum ServerState
{
    ServerIdle,
    Setup,
    Playing,
};


@implementation RTPPacketizer
{
    long _packets;
    long _bytesSent;
    long _ssrc;
    BOOL _bFirst;

    // time mapping using NTP
    uint64_t _ntpBase;
    uint64_t _rtpBase;
    double _ptsBase;
    
    long _apackets;
    long _abytesSent;
    long _assrc;
    BOOL _abFirst;
    
    // time mapping using NTP
    uint64_t _antpBase;
    uint64_t _artpBase;
    double _aptsBase;
    
    uint64_t audioSize;
}

/*
 // Byte 0         -> 10000000(0x80) version(2 bits), padding(1 bit), extension 1 bit, source identifier
 // Byte 1         -> 96
 // Byte 2,3       -> Sequence Number
 // Byte 4,5,6,7   -> Timestamp
 // Byte 8,9,10,11 -> Sync Source Identifier
 //
 */
//+ (NSMutableArray *) packetize:(NSData *)data pts:(double)pts
//{
//    uint8_t header[RTP_HEADER_LENGTH];
//    memset(header, RTP_HEADER_LENGTH, RTP_HEADER_LENGTH * sizeof(uint8_t));
//    header[0] = 0x80;
//    header[1] = 96;
//    
//    //Sequence number
//    header[2] = 0;
//    header[3] = 0;
//    
//    //Timestamp
//    header[4] = 0;
//    header[5] = 0;
//    header[6] = 0;
//    header[7] = 0;
//    
//    //Sync Source Identifier
//    header[4] = 0;
//    header[5] = 0;
//    header[6] = 0;
//    header[7] = 0;
//    
//    NSUInteger dataSize = [data length];
//    NSMutableArray *packet = [[NSMutableArray alloc] init];
//    return packet;
//}

- (void) initValues
{
    @synchronized(self)
    {
        _ssrc = random();
        _packets = 0;
        _bytesSent = 0;
        _rtpBase = 0;
        _bFirst = YES;
        
        _assrc = random();
        _apackets = 0;
        _abytesSent = 0;
        _artpBase = 0;
        _abFirst = YES;
        
        audioSize = 0;
    }
}

- (NSMutableArray *) onVideoData:(NSArray*) data time:(double) pts
{
    NSMutableArray *packetArray = [[NSMutableArray alloc] init];

    const int rtp_header_size = 12;
    const int max_single_packet = max_packet_size - rtp_header_size;
    const int max_fragment_packet = max_single_packet - 2;
    unsigned char packet[max_packet_size];

    int nNALUs = (int)[data count];
    for (int i = 0; i < nNALUs; i++){

        NSData* nalu = [data objectAtIndex:i];
        int cBytes = (int)[nalu length];
        BOOL bLast = (i == nNALUs-1);

        const unsigned char* pSource = (unsigned char*)[nalu bytes];

        if (_bFirst){
            if ((pSource[0] & 0x1f) != 5){
                continue;
            }
            _bFirst = NO;
            NSLog(@"Playback starting at first IDR");
        }

        
        
        
        
        
        if (cBytes < max_single_packet){
            //
            // вот тут получить ts и присвоить
            //
            
            [self writeHeader:packet marker:bLast time:pts];
            memcpy(packet + rtp_header_size, [nalu bytes], cBytes);

            //[self sendPacket:packet length:(cBytes + rtp_header_size)];
            [packetArray addObject:[NSData dataWithBytes:packet length:(cBytes + rtp_header_size)]];
            _packets++;
            _bytesSent += (cBytes + rtp_header_size);
        }else{
            unsigned char NALU_Header = pSource[0];
            pSource += 1;
            cBytes -= 1;
            BOOL bStart = YES;

            while (cBytes){
                int cThis = (cBytes < max_fragment_packet)? cBytes : max_fragment_packet;
                BOOL bEnd = (cThis == cBytes);
                [self writeHeader:packet marker:(bLast && bEnd) time:pts];
                unsigned char* pDest = packet + rtp_header_size;

                pDest[0] = (NALU_Header & 0xe0) + 28;   // FU_A type
                unsigned char fu_header = (NALU_Header & 0x1f);
                if (bStart){
                    fu_header |= 0x80;
                    bStart = false;
                }else if (bEnd){
                    fu_header |= 0x40;
                }
                pDest[1] = fu_header;
                pDest += 2;
                memcpy(pDest, pSource, cThis);
                pDest += cThis;

                //[self sendPacket:packet length:(int)(pDest - packet)];
                
                //
                // вот тут получить ts и присвоить
                //

                [packetArray addObject:[NSData dataWithBytes:packet length:(int)(pDest - packet)]];
                _packets++;
                _bytesSent += (int)(pDest - packet);

                ///////

                pSource += cThis;
                cBytes -= cThis;
            }
        }
    }
    return packetArray;
}

- (void) writeHeader:(uint8_t*) packet marker:(BOOL) bMarker time:(double) pts
{
//    packet[0] = 0x80;   // v= 2
//    if (bMarker){
//        packet[1] = 96 | 0x80;
//    }else{
//        packet[1] = 96;
//    }
//    unsigned short seq = _packets & 0xffff;
//    tonet_short(packet+2, seq);
//    uint64_t rtp = (uint64_t)(pts);
//    tonet_long(packet + 4, rtp);
//    tonet_long(packet + 8, _ssrc);
    
    
//    packet[0] = 0x80;   // v= 2
    packet[0] = 0xA0;   // v= 2  для padding = 1   10100000
    if (bMarker){
        packet[1] = 96 | 0x80;
    }else{
        packet[1] = 96;
    }
    unsigned short seq = _packets & 0xffff;
    tonet_short(packet+2, seq);

    // map time
    while (_rtpBase == 0){
        _rtpBase = random();
        _ptsBase = pts;
        NSDate* now = [NSDate date];
        // ntp is based on 1900. There's a known fixed offset from 1900 to 1970.
        NSDate* ref = [NSDate dateWithTimeIntervalSince1970:-2208988800L];
        double interval = [now timeIntervalSinceDate:ref];
        _ntpBase = (uint64_t)(interval * (1LL << 32));
    }
    pts -= _ptsBase;
    uint64_t rtp = (uint64_t)(pts * 90000);
    rtp += _rtpBase;
    tonet_long(packet + 4, rtp);
    tonet_long(packet + 8, _ssrc);
}

- (void) writeAudioHeader:(uint8_t*) packet marker:(BOOL) bMarker time:(double) pts size:(int)size
{
    
    //  packet[0] = 0x80;   // v= 2
    if (bMarker){
        packet[1] = 97 | 0x80;
    }else{
        packet[1] = 97;
    }
    unsigned short seq = _apackets & 0xffff;
    tonet_short(packet+2, seq);
    // map time
    pts -= _ptsBase;
    //audioSize += size * 44100;
    //audioSize += size * 23.2199546485;
    audioSize = audioSize + 1024;
    //1/44.1*1024
    
    uint64_t rtp = (uint64_t)(audioSize);//90000 // * 1024 // * 44100 * 1000
//    rtp += _artpBase;
//    NSLog(@"ta:%llu",(uint64_t)rtp);
    tonet_long(packet + 4, rtp);
    tonet_long(packet + 8, _assrc);

    
    
//  //  packet[0] = 0x80;   // v= 2
//    if (bMarker){
//        packet[1] = 96 | 0x80;
//    }else{
//        packet[1] = 96;
//    }
//    unsigned short seq = _apackets & 0xffff;
//    tonet_short(packet+2, seq);
//    // map time
//    while (_artpBase == 0){
//        _artpBase = random();
//        _aptsBase = pts;
////        NSDate* now = [NSDate date];
//        // ntp is based on 1900. There's a known fixed offset from 1900 to 1970.
////        NSDate* ref = [NSDate dateWithTimeIntervalSince1970:-2208988800L];
////        double interval = [now timeIntervalSinceDate:ref];
////        _antpBase = (uint64_t)(interval * (1LL << 32));
//    }
//    pts -= _aptsBase; //_ptsBase;
//    uint64_t rtp = (uint64_t)(pts * 44100);//90000 // * 1024
//    rtp += _artpBase;
////    NSLog(@"ta:%llu",(uint64_t)rtp);
//    tonet_long(packet + 4, rtp);
//    tonet_long(packet + 8, _assrc);
}

- (NSMutableArray *) onAudioData:(NSArray*) data time:(double) pts
{
    NSMutableArray *packetArray = [[NSMutableArray alloc] init];

    const int rtp_header_size = 12;
//    const int max_single_packet = max_packet_size - rtp_header_size;
//    const int max_fragment_packet = max_single_packet - 2;
    unsigned char packet[max_packet_size];

    int nNALUs = (int)[data count];
    for (int i = 0; i < nNALUs; i++){
        NSData* nalu = [data objectAtIndex:i];
        int cBytes = (int)[nalu length];
        BOOL bLast = (i == nNALUs-1);
        const unsigned char* pSource = (unsigned char*)[nalu bytes];

//        if (_bFirst){
//            if ((pSource[0] & 0x1f) != 5){
//                continue;
//            }
//            _bFirst = NO;
//            NSLog(@"Playback starting at first IDR");
//        }

//        if (cBytes < max_single_packet){
            [self writeAudioHeader:packet marker:bLast time:pts size:cBytes - 4];
            memcpy(packet + rtp_header_size, [nalu bytes], cBytes);

            //[self sendPacket:packet length:(cBytes + rtp_header_size)];
            [packetArray addObject:[NSData dataWithBytes:packet length:(cBytes + rtp_header_size)]];
            _apackets++;
      //      _bytesSent += (cBytes + rtp_header_size);
/*        }else{
            unsigned char NALU_Header = pSource[0];
            pSource += 1;
            cBytes -= 1;
            BOOL bStart = YES;

            while (cBytes){
                int cThis = (cBytes < max_fragment_packet)? cBytes : max_fragment_packet;
                BOOL bEnd = (cThis == cBytes);
                [self writeHeader:packet marker:(bLast && bEnd) time:pts];
                unsigned char* pDest = packet + rtp_header_size;

                pDest[0] = (NALU_Header & 0xe0) + 28;   // FU_A type
                unsigned char fu_header = (NALU_Header & 0x1f);
                if (bStart){
                    fu_header |= 0x80;
                    bStart = false;
                }else if (bEnd){
                    fu_header |= 0x40;
                }
                pDest[1] = fu_header;
                pDest += 2;
                memcpy(pDest, pSource, cThis);
                pDest += cThis;

                //[self sendPacket:packet length:(int)(pDest - packet)];
                [packetArray addObject:[NSData dataWithBytes:packet length:(int)(pDest - packet)]];
                _packets++;
                _bytesSent += (int)(pDest - packet);

                ///////

                pSource += cThis;
                cBytes -= cThis;
            }
        } */
    }
    return packetArray;
}

@end
