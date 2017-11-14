//
//  AACEncoder.m
//  HTTPLiveStreaming
//
//  Created by Byeongwook Park on 2016. 1. 8..
//  Copyright © 2016년 . All rights reserved.
//
//  http://stackoverflow.com/questions/10817036/can-i-use-avcapturesession-to-encode-an-aac-stream-to-memory

#import "AACEncoder.h"
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

@interface AACEncoder()

@property (nonatomic) AudioConverterRef audioConverter;
@property (nonatomic) uint8_t *aacBuffer;
@property (nonatomic) NSUInteger aacBufferSize;
@property (nonatomic) char *pcmBuffer;
@property (nonatomic) size_t pcmBufferSize;

@end

@implementation AACEncoder

- (void) dealloc {
    AudioConverterDispose(_audioConverter);
    free(_aacBuffer);
}

- (id) init {
    if (self = [super init]) {
        _silence = false;
        _encoderQueue = dispatch_queue_create("AAC Encoder Queue", DISPATCH_QUEUE_SERIAL);
        _callbackQueue = dispatch_queue_create("AAC Encoder Callback Queue", DISPATCH_QUEUE_SERIAL);
        _audioConverter = NULL;
        _pcmBufferSize = 0;
        _pcmBuffer = NULL;
        _aacBufferSize = 1024 * 2;
        _aacBuffer = malloc(_aacBufferSize * sizeof(uint8_t));
        memset(_aacBuffer, 0, _aacBufferSize);
        self.delegate = nil;
    }
    return self;
}

- (void) setupEncoderFromSampleBuffer:(CMSampleBufferRef)sampleBuffer {
    AudioStreamBasicDescription inAudioStreamBasicDescription = *CMAudioFormatDescriptionGetStreamBasicDescription((CMAudioFormatDescriptionRef)CMSampleBufferGetFormatDescription(sampleBuffer));

    AudioStreamBasicDescription outAudioStreamBasicDescription = {0};
    outAudioStreamBasicDescription.mSampleRate = 44100.000000;
    outAudioStreamBasicDescription.mFormatID = kAudioFormatMPEG4AAC;
    outAudioStreamBasicDescription.mFormatFlags = kMPEG4Object_AAC_LC;
    outAudioStreamBasicDescription.mBytesPerPacket = 0;// The number of bytes in a packet of audio data. To indicate variable packet size, set this field to 0. For a format that uses variable packet size, specify the size of each packet using an AudioStreamPacketDescription structure.
    outAudioStreamBasicDescription.mFramesPerPacket = 1024;// The number of frames in a packet of audio data. For uncompressed audio, the value is 1. For variable bit-rate formats, the value is a larger fixed number, such as 1024 for AAC. For formats with a variable number of frames per packet, such as Ogg Vorbis, set this field to 0.
    outAudioStreamBasicDescription.mBytesPerFrame = 0;
    outAudioStreamBasicDescription.mChannelsPerFrame = 1;
    outAudioStreamBasicDescription.mBitsPerChannel = 0;
    outAudioStreamBasicDescription.mReserved = 0;
    AudioClassDescription *description = [self
                                          getAudioClassDescriptionWithType:kAudioFormatMPEG4AAC
                                          fromManufacturer:kAppleSoftwareAudioCodecManufacturer];

    OSStatus status = AudioConverterNewSpecific(&inAudioStreamBasicDescription, &outAudioStreamBasicDescription, 1, description, &_audioConverter);
    if (status != 0) {
        NSLog(@"setup converter: %d", (int)status);
    }
}

- (AudioClassDescription *)getAudioClassDescriptionWithType:(UInt32)type
                                           fromManufacturer:(UInt32)manufacturer
{
    static AudioClassDescription desc;

    UInt32 encoderSpecifier = type;
    OSStatus st;

    UInt32 size;
    st = AudioFormatGetPropertyInfo(kAudioFormatProperty_Encoders,
                                    sizeof(encoderSpecifier),
                                    &encoderSpecifier,
                                    &size);
    if (st) {
        NSLog(@"error getting audio format propery info: %d", (int)(st));
        return nil;
    }

    unsigned int count = size / sizeof(AudioClassDescription);
    AudioClassDescription descriptions[count];
    st = AudioFormatGetProperty(kAudioFormatProperty_Encoders,
                                sizeof(encoderSpecifier),
                                &encoderSpecifier,
                                &size,
                                descriptions);
    if (st) {
//      NSLog(@"error getting audio format propery: %d", (int)(st));
        return nil;
    }

    for (unsigned int i = 0; i < count; i++) {
        if ((type == descriptions[i].mSubType) &&
            (manufacturer == descriptions[i].mManufacturer)) {
            memcpy(&desc, &(descriptions[i]), sizeof(desc));
            return &desc;
        }
    }
    return nil;
}

static OSStatus inInputDataProc(AudioConverterRef inAudioConverter, UInt32 *ioNumberDataPackets, AudioBufferList *ioData, AudioStreamPacketDescription **outDataPacketDescription, void *inUserData)
{
    AACEncoder *encoder = (__bridge AACEncoder *)(inUserData);
    UInt32 requestedPackets = *ioNumberDataPackets;
    //NSLog(@"Number of packets requested: %d", (unsigned int)requestedPackets);
    size_t copiedSamples = [encoder copyPCMSamplesIntoBuffer:ioData];
    if (copiedSamples < requestedPackets) {
        //NSLog(@"PCM buffer isn't full enough!");
        *ioNumberDataPackets = 0;
        return -1;
    }
    *ioNumberDataPackets = 1;
  //  NSLog(@"Copied %zu samples into ioData", copiedSamples);
    return noErr;
}

- (size_t) copyPCMSamplesIntoBuffer:(AudioBufferList*)ioData {
    size_t originalBufferSize = _pcmBufferSize;
    if (!originalBufferSize) {
        return 0;
    }
    ioData->mBuffers[0].mData = _pcmBuffer;
    ioData->mBuffers[0].mDataByteSize = (UInt32)_pcmBufferSize;
    _pcmBuffer = NULL;
    _pcmBufferSize = 0;

    if(self.silence) {
//        NSLog(@"SILENSE IS TRUE");
        memset(ioData->mBuffers[0].mData, 0, ioData->mBuffers[0].mDataByteSize);
    }else{
//        NSLog(@"SILENSE IS FALSE");
    }

    return originalBufferSize;
}

- (void) encode:(CMSampleBufferRef)sampleBuffer {
    CFRetain(sampleBuffer);
    CMTime timestamp = CMSampleBufferGetPresentationTimeStamp(sampleBuffer);
    dispatch_async(_encoderQueue, ^{
        if (!_audioConverter) {
            [self setupEncoderFromSampleBuffer:sampleBuffer];
        }
        CMBlockBufferRef blockBuffer = CMSampleBufferGetDataBuffer(sampleBuffer);
        CFRetain(blockBuffer);
        OSStatus status = CMBlockBufferGetDataPointer(blockBuffer, 0, NULL, &_pcmBufferSize, &_pcmBuffer);
        NSError *error = nil;
        if (status != kCMBlockBufferNoErr) {
            error = [NSError errorWithDomain:NSOSStatusErrorDomain code:status userInfo:nil];
        }
//        NSLog(@"PCM Buffer Size: %zu", _pcmBufferSize);
//        _aacBufferSize = CMBlockBufferGetDataLength(blockBuffer);
//        if(_aacBuffer != nil) {
//            free(_aacBuffer);
//            _aacBuffer = nil;
//        }
      //  NSLog(@"aac Buffer Size: %zu", _aacBufferSize);
//        _aacBuffer = malloc(_aacBufferSize);
        
        memset(_aacBuffer, 0, _aacBufferSize);
        AudioBufferList outAudioBufferList = {0};
        outAudioBufferList.mNumberBuffers = 1;
        outAudioBufferList.mBuffers[0].mNumberChannels = 1;
        outAudioBufferList.mBuffers[0].mDataByteSize = (UInt32)_aacBufferSize;
        outAudioBufferList.mBuffers[0].mData = _aacBuffer;
        AudioStreamPacketDescription *outPacketDescription = NULL;
        UInt32 ioOutputDataPacketSize = 1;
        status = AudioConverterFillComplexBuffer(_audioConverter, inInputDataProc, (__bridge void *)(self), &ioOutputDataPacketSize, &outAudioBufferList, outPacketDescription);
     //   NSLog(@"ioOutputDataPacketSize: %d", (unsigned int)ioOutputDataPacketSize);
        NSData *data = nil;
        if (status == 0) {
            NSData *rawAAC = [NSData dataWithBytes:outAudioBufferList.mBuffers[0].mData length:outAudioBufferList.mBuffers[0].mDataByteSize];
            //NSData *adtsHeader = [self adtsDataForPacketLength:rawAAC.length];
            NSData *adtsHeader = [self latmDataForPacketLength: (int)rawAAC.length];
            
            NSMutableData *fullData = [NSMutableData dataWithData:adtsHeader];
            
            [fullData appendData:rawAAC];
            
            data = fullData;
        } else {
            [self errCheck:status];
            error = [NSError errorWithDomain:NSOSStatusErrorDomain code:status userInfo:nil];
        }
        if (self.delegate != nil ) {//&& [data length] > 0
            dispatch_async(_callbackQueue, ^{
                [self.delegate gotAACEncodedData:data timestamp:timestamp error:error];
            });
        }
        CFRelease(sampleBuffer);
        CFRelease(blockBuffer);
    });
}

-(void) errCheck:(OSStatus)err {
    switch(err) {
        case kAudioConverterErr_FormatNotSupported:
            NSLog(@"kAudioConverterErr_FormatNotSupported");
            break;
        case kAudioConverterErr_OperationNotSupported:
            NSLog(@"kAudioConverterErr_OperationNotSupported");
            
            break;
        case kAudioConverterErr_PropertyNotSupported:
            NSLog(@"kAudioConverterErr_PropertyNotSupported");
            
            break;
        case kAudioConverterErr_InvalidInputSize:
            NSLog(@"kAudioConverterErr_InvalidInputSize");
            
            break;
        case kAudioConverterErr_InvalidOutputSize:
            NSLog(@"kAudioConverterErr_InvalidOutputSize");
            
            break;
        case kAudioConverterErr_UnspecifiedError:
            NSLog(@"kAudioConverterErr_UnspecifiedError");
            
            break;
        case kAudioConverterErr_BadPropertySizeError:
            NSLog(@"kAudioConverterErr_BadPropertySizeError");
            
            break;
        case kAudioConverterErr_RequiresPacketDescriptionsError:
            NSLog(@"kAudioConverterErr_RequiresPacketDescriptionsError");
            
            break;
        case kAudioConverterErr_InputSampleRateOutOfRange:
            NSLog(@"kAudioConverterErr_InputSampleRateOutOfRange");
            
            break;
        case kAudioConverterErr_OutputSampleRateOutOfRange:
            NSLog(@"kAudioConverterErr_OutputSampleRateOutOfRange");
            
            break;
    }
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
- (NSData*) adtsDataForPacketLength:(NSUInteger)packetLength {
    int adtsLength = 7;
    char *packet = malloc(sizeof(char) * adtsLength);
    // Variables Recycled by addADTStoPacket
    int profile = 2;  //AAC LC
    //39=MediaCodecInfo.CodecProfileLevel.AACObjectELD;
//    int freqIdx = 4;  //44.1KHz - 4  // 8000 - 11 //
    int freqIdx = 4;  //44.1KHz - 4  // 8000 - 11 //
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

- (NSData*) latmDataForPacketLength:(int)packetLength {
    int length = packetLength;
    int latmLength = 4;
    char *buffer = malloc(sizeof(char) * latmLength);
    
    // AU-headers-length field: contains the size in bits of a AU-header
    // 13+3 = 16 bits -> 13bits for AU-size and 3bits for AU-Index / AU-Index-delta
    // 13 bits will be enough because ADTS uses 13 bits for frame length
    buffer[0] = 0;
    buffer[1] = 0x10;
    
    // AU-size
    buffer[2] = (char) (length>>5);
    buffer[3] = (char) (length<<3);
    
    // AU-Index
    buffer[3] &= 0xF8;
    buffer[3] |= 0x00;

    NSData *data = [NSData dataWithBytesNoCopy:buffer length:latmLength freeWhenDone:YES];
    return data;
}

@end
