//
//  AudioEncoder.swift
//  SwiftMobistream
//
//  Created by netris on 31.05.16.
//  Copyright © 2016 netris. All rights reserved.
//
//  http://www.iis.fraunhofer.de/content/dam/iis/de/doc/ame/wp/FraunhoferIIS_Application-Bulletin_AAC-ELD-on-iOS.pdf
//

import UIKit
import AVFoundation
import CoreMedia
import AudioToolbox

protocol AudioEncoderDelegate : class{
    func audioEncode(_ sender: AudioEncoder, data:Data, pts:Double, cmtime:CMTime)
}

class AudioEncoder: NSObject {

    static let sharedInstance = AudioEncoder()
    weak var delegate:AudioEncoderDelegate?

    var aacEncoder:AACEncoder = AACEncoder()

    override init() {
        super.init()
        aacEncoder.delegate = self
    }

    func mute(_ mute:Bool) {
        self.aacEncoder.silence = mute
    }

    func encode(sampleBuffer: CMSampleBuffer) {
        DispatchQueue(label: "ru.netris.mobistream.encoder", attributes: []).async(execute: { ()in
            self.aacEncoder.encode(sampleBuffer)
        })
    }
}

extension AudioEncoder: AVCaptureAudioDataOutputSampleBufferDelegate {

    func captureOutput(_ captureOutput: AVCaptureOutput!, didDropSampleBuffer sampleBuffer: CMSampleBuffer!, fromConnection connection: AVCaptureConnection!) {
        print("sampleBuffer Dropped audio!")
    }

    func captureOutput(_ captureOutput: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        autoreleasepool{
            encode(sampleBuffer: sampleBuffer)
        }
    }
}

extension AudioEncoder: AACEncoderDelegate {

    func gotAACEncodedData(_ data: Data!, timestamp: CMTime, error: Error!) {
//     if let error = error {
//         print("Error: \(error.localizedDescription)")
//     }
        if let data = data {
            delegate?.audioEncode(self, data: data, pts: CMTimeGetSeconds(timestamp), cmtime: timestamp)
//            print("Count: \(data.count)  TS:\(timestamp)")
        }else{
            
        }
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
//- (NSData*) adtsDataForPacketLength:(NSUInteger)packetLength {
//    int adtsLength = 7;
//    char *packet = malloc(sizeof(char) * adtsLength);
//    // Variables Recycled by addADTStoPacket
//    int profile = 2;  //AAC LC
//    //39=MediaCodecInfo.CodecProfileLevel.AACObjectELD;
//    int freqIdx = 4;  //44.1KHz
//    int chanCfg = 1;  //MPEG-4 Audio Channel Configuration. 1 Channel front-center
//    NSUInteger fullLength = adtsLength + packetLength;
//    // fill in ADTS data
//    packet[0] = (char)0xFF;	// 11111111  	= syncword
//    packet[1] = (char)0xF9;	// 1111 1 00 1  = syncword MPEG-2 Layer CRC
//    packet[2] = (char)(((profile-1)<<6) + (freqIdx<<2) +(chanCfg>>2));
//    packet[3] = (char)(((chanCfg&3)<<6) + (fullLength>>11));
//    packet[4] = (char)((fullLength&0x7FF) >> 3);
//    packet[5] = (char)(((fullLength&7)<<5) + 0x1F);
//    packet[6] = (char)0xFC;
//    NSData *data = [NSData dataWithBytesNoCopy:packet length:adtsLength freeWhenDone:YES];
//    return data;
//}

//------------------------------------------------
//buf length: 2048
//audio format: <CMAudioFormatDescription 0x144635400 [0x19f413150]> {
//    mediaType:'soun'
//    mediaSubType:'lpcm'
//    mediaSpecific: {
//        ASBD: {
//            mSampleRate: 44100.000000
//            mFormatID: 'lpcm'
//            mFormatFlags: 0xc
//            mBytesPerPacket: 2
//            mFramesPerPacket: 1
//            mBytesPerFrame: 2
//            mChannelsPerFrame: 1
//            mBitsPerChannel: 16 	}
//        cookie: {(null)}
//        ACL: {(null)}
//    }
//    extensions: {(null)}
//}
//item count: 1024
//absd: AudioStreamBasicDescription(mSampleRate: 44100.0, mFormatID: 1819304813, mFormatFlags: 12, mBytesPerPacket: 2, mFramesPerPacket: 1, mBytesPerFrame: 2, mChannelsPerFrame: 1, mBitsPerChannel: 16, mReserved: 0)
//sample rate:44100.0  channel count:1
//------------------------------------------------


