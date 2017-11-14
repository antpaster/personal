//
//  ConnectionManager.swift
//  SwiftMobistream
//
//  Created by netris on 02.06.16.
//  Copyright © 2016 netris. All rights reserved.
//

import UIKit

fileprivate func < <T : Comparable>(lhs: T?, rhs: T?) -> Bool {
  switch (lhs, rhs) {
  case let (l?, r?):
    return l < r
  case (nil, _?):
    return true
  default:
    return false
  }
}

enum SenderState {
    case bad
    case normal
    case good
}

enum BufferState {
    case empty      // 0..100
    case beforeHalf // 100..до половины
    case afterHalf  // от половины..до полного
}

protocol ConnectionManagerDelegate : class{
    func connectionManager(_ sender: ConnectionManager, status:ConnectionManagerStatus)
    func connectionManager(_ sender: ConnectionManager, registerCamera:Bool, error:Error?)
}

enum ConnectionManagerStatus {
    case none
    case connecting
    case connected
    case registering
    case registered
    case disconnected(NSError?)
}

class ConnectionManager: NSObject, ConnectionDelegate {//, SimpleConnectionDelegate

    static let sharedInstance = ConnectionManager()
    var queue:ConcurrentQueque = ConcurrentQueque()

    var status:ConnectionManagerStatus = .none
    var delegate:ConnectionManagerDelegate?

    var host:String?
    var port:Int32?
    var channel:String?

    var sps:String?
    var pps:String?
    var profileLevelId:String?
    var rtpPacketizer:RTPPacketizer = RTPPacketizer()
    var rtpAudioPacketizer:RTPPacketizer = RTPPacketizer()
    var videoConnection:StreamConnection?
    var videoStreamConnected = false

    override init() {
        super.init()
        self.queue = ConcurrentQueque()
        self.queue.serialQueue = self.serialQueue
    }

    func videoSdp() -> String {
        var sdp:String = ""
        let verid = arc4random()

        if let ip = NetworkUtil.getIPAddress() {
            sdp += "v=0\r\no=- \(verid) \(verid) IN IP4 \(ip)\r\ns=Live stream from iOS\r\nc=IN IP4 0.0.0.0\r\nt=0 0\r\n"
        }else{
            sdp += "v=0\r\no=- \(verid) \(verid) IN IP4 0.0.0.0\r\ns=Live stream from iOS\r\nc=IN IP4 0.0.0.0\r\nt=0 0\r\n"
        }
        sdp += "m=video 0 RTP/AVP 96\r\n"
        sdp += "a=rtpmap:96 H264/90000\r\n"
        sdp += "a=fmtp:96 packetization-mode=0;profile-level-id=\(profileLevelId!);sprop-parameter-sets=\(sps!),\(pps!)\r\n"
        sdp += "i=h264\r\na=control:track=0\r\na=control:trackID=0\r\n"
        return sdp
    }

    func audioSdp() -> String {
        var sdp:String = ""
        sdp += "m=audio 0 RTP/AVP 97\r\n"
        sdp += "a=rtpmap:97 mpeg4-generic/44100\r\n"//
        sdp += "a=fmtp:97 streamtype=5; profile-level-id=15; mode=AAC-hbr; config=1210; SizeLength=13; IndexLength=3; IndexDeltaLength=3\r\n"
        sdp += "a=control:track=2\r\na=control:trackID=2\r\n"
        return sdp//1588
    }

    func connectVideoServer() {
        rtpPacketizer.initValues()
        rtpAudioPacketizer.initValues()
        if let sps = self.sps, let pps = self.pps, let profileLevelId = self.profileLevelId, let host = self.host, let port = self.port, let channel = self.channel {
            var sdp = videoSdp()
//            if SettingsService().getStreamMode() != 0 {
                sdp = videoSdp().appending(audioSdp())
//            }
            print(sdp)
            videoConnection = StreamConnection(host: host, port: port, channel: channel, sdp: sdp, delegate:self)
            self.delegate?.connectionManager(self, status: .connecting)
            videoConnection?.connect()
        }
    }

    func disconnectVideoServer() {
        videoConnection?.disconnect()
    }

    func onMessageReceivedString(_ message: String!, fromConnection connection: Any!) {
        
    }

    func onStatus(_ status: Int32, connection: Any!) {
        
    }

    func onVideoRegistered(_ connection: Any!, connected isRegister: Bool, withError error: Error!) {
        if isRegister {
            print("video registered")
            videoStreamConnected = true
            delegate?.connectionManager(self, registerCamera: true, error: nil)
            self.delegate?.connectionManager(self, status: .registered)
            self.startSenderLoop()
        }else{
            print("video not registered: \(error.localizedDescription)")
            videoStreamConnected = false
            delegate?.connectionManager(self, registerCamera: false, error: error)
            self.delegate?.connectionManager(self, status: .disconnected(error as NSError?))
            self.stopSenderLoop()
        }
    }

    let dispatchQueue = DispatchQueue(label: "ru.netris.queue")

    let uploadDispatchQueue = DispatchQueue(label: "ru.netris.queue.upload")
    let serialQueue:DispatchQueue = DispatchQueue(label: "mySerialQueue")
    let serialGpsQueue:DispatchQueue = DispatchQueue(label: "mySerialQueue")
    let serialQueue2:DispatchQueue = DispatchQueue(label: "mySerialQueue2")

    func writeVideo(_ data:Data, pts:Double, cmtime:CMTime) {
        serialQueue.async(execute: {( ) in
            self.queue.pushVideo((pts, data, true, cmtime))
        })
    }

    func writeAudio(_ data:Data, pts:Double, cmtime:CMTime) {
        serialQueue.async(execute: {( ) in
            self.queue.pushAudio((pts, data, false, cmtime))
        })
    }

    var upload:Bool = false

    func startSenderLoop() {
        uploadDispatchQueue.async(execute: {( ) in
            self.upload = true
            while true {
                autoreleasepool {
                let res = self.queue.pop()
                if res != nil {
                    if (res?.2)! {
                        let arr:NSMutableArray = NSMutableArray()
                        arr.add(res!.1)
                        let result = self.rtpPacketizer.onVideoData(arr as [AnyObject]!, time: (res?.0)!)
                        for item in result! {
                            let dat:Data = item as! Data
                            let resu = InterleavedPacketizer.packetize(dat, channel: 0)
                            _ = self.videoConnection?.write(resu!)
                        }
                    }else{
                        let arr:NSMutableArray = NSMutableArray()
                        arr.add(res!.1)
                        let tt:Int = Int((Float(res!.3.value) / Float(res!.3.timescale) ) * 1000)
                        let result = self.rtpPacketizer.onAudioData(arr as [AnyObject]!, time: Double(tt))
                        for item in result! {
                            let dat:Data = item as! Data
                            let resu = InterleavedPacketizer.packetize(dat, channel: 2)
                            _ = self.videoConnection?.write(resu!)
                        }
                    }
                }else{
                    Thread.sleep(forTimeInterval: 0.02)
                }
            }
            if !self.upload {
                self.serialQueue.async(execute: {( ) in
                    print("clear queue")
                    self.queue.clearAll()
                    return
                })
                return
            }
            }
        })
    }

    func stopSenderLoop() {
        self.upload = false
    }

    struct ConcurrentQueque {
        let max_size = 100
        let bufferSize = 8

        var videoItems = [(Double, Data, Bool, CMTime)]() // bool is true
        var audioItems = [(Double, Data, Bool, CMTime)]() // bool is false

        var serialQueue:DispatchQueue?

        var videoSemaphore = DispatchSemaphore(value: 1)
        var audioSemaphore = DispatchSemaphore(value: 1)

        mutating func pushVideo(_ item: (Double, Data, Bool, CMTime)) {
            videoSemaphore.wait()
            if self.videoItems.count > max_size {
                clearAll()
            }
            self.videoItems.append(item)
            videoSemaphore.signal()
        }

        mutating func pushAudio(_ item: (Double, Data, Bool, CMTime)) {
            audioSemaphore.wait()
            self.audioItems.append(item)
            audioSemaphore.signal()
        }

        mutating func pop() -> (Double, Data, Bool, CMTime)? {
            if videoItems.count < bufferSize {
                return nil
            }

            if topAudioItem == nil {
                if videoItems.count > 0 {
                    videoSemaphore.wait()
                    let ass:(Double,Data,Bool,CMTime) = videoItems.removeFirst()
                    videoSemaphore.signal()
                    return ass
                }
                return nil
            }

            if topVideoItem == nil {
                return nil
            }

            if topAudioItem?.0 < topVideoItem?.0 {
                audioSemaphore.wait()
                let ass:(Double,Data,Bool,CMTime) = audioItems.removeFirst()
                audioSemaphore.signal()
                return ass
            } else {
                videoSemaphore.wait()
                let ass:(Double,Data,Bool,CMTime) = videoItems.removeFirst()
                videoSemaphore.signal()
                return ass
            }
        }

        var topVideoItem: (Double, Data, Bool, CMTime)? {
            return videoItems.isEmpty ? nil : videoItems[0] //videoItems.count - 1
        }

        var topAudioItem: (Double, Data, Bool, CMTime)? {
            return audioItems.isEmpty ? nil : audioItems[0] //videoItems.count - 1
        }

        mutating func clearAll() {
            print("CLEAR ALL!")
            videoItems.removeAll()
            audioSemaphore.wait()
            audioItems.removeAll()
            audioSemaphore.signal()
        }
    }
}

extension Data {

    func hexadecimalString40() -> String {
        var string = ""
        var byte: UInt8 = 0
        
        for i in 0 ..< count {
//        for i in 0 ..< 20 {
            copyBytes(to: &byte, from: i..<i+1)//NSMakeRange(i, 1)
            string += String(format: " %02x", byte)
        }
        
        return string
    }
}
