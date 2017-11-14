//
//  FrameManager.swift
//  Mobistreamer
//
//  Created by Александр on 06.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit

struct FrameManagerSessionSettings {
    var host:String?
    var port:Int?
    var stream:String?
    var sdp:String?
    var sps:String?
    var pps:String?
    var profileLevelId:String?
    var lastTs:Int?
    var settings:ServerSettingsEntity?
}

protocol FrameManagerDelegate {
    func frameManager(registerCamera: Bool, error: Error?)
    func frameManager(uploadSpeed: Double)
    func bufferOverFlow()
    func startingAtFirstIDR()
}

class FrameManager: NSObject {

    var rtpPacketizer:RTPPacketizer = RTPPacketizer()
    var rtpAudioPacketizer:RTPPacketizer = RTPPacketizer()

    var delegate:FrameManagerDelegate?

    var queue:Queue
    var storage:FrameStorage
    var socket:SocketConnection?

    var isConnected = false
    var isRegister = false

    let uploadDispatchQueue = DispatchQueue(label: "ru.netris.queue.upload")
    let serialQueue:DispatchQueue = DispatchQueue(label: "mySerialQueue")
    let uploadDispatchQueue2 = DispatchQueue(label: "ru.netris.queue.upload")

    var upload = false
    var sessionSettings:FrameManagerSessionSettings?

    static var lastTs:Int = 0

    override init() {
        self.storage = FrameStorage()
//        self.queue = FrameQueue()
        self.queue = ConcurrentQueque()
        self.queue.storage = storage
        
    }

    func configPaketizers() {
        rtpPacketizer = RTPPacketizer()
        rtpPacketizer.delegate = self
        rtpAudioPacketizer = RTPPacketizer()
    }

    func push(_ frame:FrameEntity) {
        serialQueue.async{
            self.queue.push(frame)
        }
    }

    // вызывать когда разрывается соединение
    func flush() {
        self.queue.flush()
    }

    func cancel() {
        self.socket?.cancel()
    }

    // стопает соединение очищает буфер
    func stop() {
        isConnected = false
        isRegister = false
        self.queue.clear()
        self.socket?.close()
        self.socket = nil
    }

    func start() {
        self.queue.queueSignalDelegate = self
        if let sessionSettings = self.sessionSettings {
            if let host = sessionSettings.host, let port = sessionSettings.port {
                rtpPacketizer = RTPPacketizer()
                rtpPacketizer.delegate = self
                rtpAudioPacketizer = RTPPacketizer()
                rtpPacketizer.initValues()
                rtpAudioPacketizer.initValues()
                self.socket = SocketConnection(host: host, port: port, delegate: self)
                self.socket?.connect()
            }
        }
    }

    static var notUpload = false

    func startLoop() {
//        uploadDispatchQueue.async{
//        let asd = DispatchQueue.global(qos: DispatchQoS.userInitiated)
        
//        uploadDispatchQueue.async{
        DispatchQueue.global(qos: .userInitiated).async{
            guard !self.upload else {
                return
            }
            self.upload = true
            while true {
                autoreleasepool {
                    
                    if FrameManager.notUpload {
                        Thread.sleep(forTimeInterval: 0.06)
//                        print("not upload")
                    }else{
                    
                    if let frame = self.queue.pop() {
                        if frame.type == .video {
                            let arr:NSMutableArray = NSMutableArray()
                            arr.add(frame.value!)
                            let result = self.rtpPacketizer.onVideoData(arr as [AnyObject]!, time: frame.ts)

                            var isError = false
                            for item in result! {
                                let dat:Data = item as! Data
                                let resu = InterleavedPacketizer.packetize(dat, channel: 0)
                                let uploaded = self.socket?.write(resu)
                                if uploaded == -1 {
                                    isError = true
                                }
                            }
                            if !isError {
                                FrameManager.lastTs = self.rtpPacketizer.lastPacketTs
                            }
                        }
                        if frame.type == .audio {
                            let arr:NSMutableArray = NSMutableArray()
                            arr.add(frame.value!)
//                            let tt:Int = Int((Float(frame.time.value) / Float(frame.time.timescale) ) * 1000)
                            let result = self.rtpPacketizer.onAudioData(arr as [AnyObject]!, time: Double(frame.time))

                            var isError = false
                            for item in result! {
                                let dat:Data = item as! Data
                                let resu = InterleavedPacketizer.packetize(dat, channel: 2)
                                let uploaded = self.socket?.write(resu)
                                if uploaded == -1 {
                                    isError = true
                                }
                            }
                            if !isError {
                                FrameManager.lastTs = self.rtpPacketizer.lastPacketTs
                            }
                        }
                    }else{
                        Thread.sleep(forTimeInterval: 0.02)
                    }
                }

                if !self.upload {
                    self.serialQueue.async(execute: {( ) in
                        print("flush queue")
                        self.queue.flush()
                        return
                    })
                }
            }
                
                
            }
        }
    }

    func stopLoop() {
        uploadDispatchQueue.async{
            self.upload = false
        }
    }

    func generateSdp() -> String {
        var sdp:String = ""
        let verid = arc4random()
        if let ip = NetworkUtil.getIPAddress() {
            sdp += "v=0\r\no=- \(verid) \(verid) IN IP4 \(ip)\r\ns=Live stream from iOS\r\nc=IN IP4 0.0.0.0\r\nt=0 0\r\n"
        }else{
            sdp += "v=0\r\no=- \(verid) \(verid) IN IP4 0.0.0.0\r\ns=Live stream from iOS\r\nc=IN IP4 0.0.0.0\r\nt=0 0\r\n"
        }
        sdp += "m=video 0 RTP/AVP 96\r\n"
        sdp += "a=rtpmap:96 H264/90000\r\n"
        sdp += "a=fmtp:96 packetization-mode=0;profile-level-id=\(sessionSettings!.profileLevelId!);sprop-parameter-sets=\(sessionSettings!.sps!),\(sessionSettings!.pps!)\r\n"
        sdp += "i=h264\r\na=control:track=0\r\na=control:trackID=0\r\n"
        sdp += "m=audio 0 RTP/AVP 97\r\n"
        sdp += "a=rtpmap:97 mpeg4-generic/44100\r\n"//
        sdp += "a=fmtp:97 streamtype=5; profile-level-id=15; mode=AAC-hbr; config=1210; SizeLength=13; IndexLength=3; IndexDeltaLength=3\r\n"
        sdp += "a=control:track=2\r\na=control:trackID=2\r\n"
        return sdp//1588
    }

    func registerServerQueryString() -> String {
        let sdpString = self.generateSdp().replacingOccurrences(of: "\r\n", with: "\\\\r\\\\n")
        self.sessionSettings?.sdp = sdpString

        var body = ""
        body += "{\"action\":\"register_camera\","
        body += "\"rtp-padding-has-unixtimestamp\":true,"
        body += "\"parameters\":{"
        body += "\"channelid\":\"\(self.sessionSettings!.stream!)\","
        body += "\"token\":\"\(EchdSessionContext.shared.token!)\","
        if let ip = NetworkUtil.getIPAddress() {
            body += "\"ip\":\"\(ip)\","
        }else{
            body += "\"ip\":\"0.0.0.0\","
        }
        body += "\"sdp\":\""
        
        print(sdpString)
        
        body += sdpString
        body += "\"}}"

        var result = ""
        result += "POST /api HTTP/1.1\r\nConnection: keep-alive\r\n"
        result += "Content-Length: \(body.lengthOfBytes(using: String.Encoding.utf8))\r\n"
        result += "Content-Type: application/json\r\n"
        result += "Host: \(self.sessionSettings!.host!):\(self.sessionSettings!.port!)\r\n"
        result += "User-Agent: MobiStreamIOS\r\n\r\n"
        result += body
        
        print(result)
        
        return result
    }
}

extension FrameManager: RTPPacketizerDelegate {

    func startingAtFirstIDR() {
        delegate?.startingAtFirstIDR()
    }
}

extension FrameManager: FrameQueueSignal {
    func bufferFlush() {
        delegate?.bufferOverFlow()
    }
}

extension FrameManager: SocketConnectionDelegate {

    func socketConnection(speed: Double) {
        delegate?.frameManager(uploadSpeed: speed)
    }

    func socketConnection(state: SocketConnectionState) {
        switch state {
        case .connecting:
            isConnected = false
            isRegister = false
        case .connected:
            print("CONNECTED")
            isConnected = true
            DispatchQueue.main.async {
                let str = self.registerServerQueryString()
//                print(str)
                _ = self.socket?.write(message:str)
            }
//            delegate?.frameManager(registerCamera: isRegister, error: <#T##Error?#>)
            break
        case .disconnected:
            isConnected = false
            isRegister = false
            delegate?.frameManager(registerCamera: isRegister, error:  nil)
        case .error(let error):
            isConnected = false
            isRegister = false
            delegate?.frameManager(registerCamera: isRegister, error:  error)
            print(error.localizedDescription)
        case .receive(let message):
//            print(message)
            if message.contains("{\"action\":\"get_video\",\"success\":true}") {
                isRegister = true
                if let sessionSettings = self.sessionSettings {
                    storage.sessionSettings = sessionSettings
                }
                delegate?.frameManager(registerCamera: isRegister, error:  nil)
                print("VIDEO REGISTERED")
            }else{
                if message.contains("HTTP/1.1 200 OK") {
                    let arr = message.components(separatedBy: "\r\n\r\n")
                    if arr.count > 1 {
                        if let str = arr.last {
                            if let data = str.data(using: .utf8) {
                                do{
                                    if let json = try JSONSerialization.jsonObject(with: data, options: .allowFragments) as? [String:AnyObject] {
                                        if let response = json["response"] as? [String:AnyObject]  {
                                            if let suc = response["success"] as? Bool, !suc, let reason = response["reason"] as? String {
                                                var mess = reason
                                                if reason == "pnp channel is still busy, try again later" {
                                                    mess = "Трансляция под вашей учетной записью уже запущена."
                                                }

                                                let userInfo: [AnyHashable: Any] = [
                                                    NSLocalizedDescriptionKey :  mess,
                                                    NSLocalizedFailureReasonErrorKey : ""
                                                ]
                                                delegate?.frameManager(registerCamera: false, error: NSError(domain: "EchdAuthService", code: 100, userInfo: userInfo as! [String : Any]) as Error)
                                            }
                                        }
                                    }
                                }catch let error {
                                    print("error serializing JSON: \(error)")
                                }
                            }else{
                                
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
enum ElementaryStreamEncodingType {
    unknownStreamType,
    h264,                     // поток h264
    g711,                     // поток g711
    aac,                      // поток aac
    archive_config,           // конфигурация архива
    mjpeg,                    // поток mjpeg
};

*/
