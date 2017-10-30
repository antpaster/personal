//
//  UploadOperation.swift
//  Mobistreamer
//
//  Created by Александр on 21.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit

class UploadOperation: NSObject {

    var success:((_ obj:AnyObject?) -> ())?
    var fail:((_ error:Error?) -> ())?
    var progress:((_ sent:Int, _ size:Int) -> ())?

    var socket:SocketConnection?
    var session:StorageSessionTransport?

    let maxSubdataLength = 1000

    var isConnected = false

    init(session:StorageSessionTransport, progress: @escaping (_ sent:Int, _ size:Int) -> (), success:@escaping (_ obj:AnyObject?) -> (), fail:@escaping (_ error:Error?) -> ()) {
        self.fail = fail
        self.success = success
        self.session = session
        self.progress = progress
    }

    func main() {
        self.socket = SocketConnection(host: self.session!.host!, port: self.session!.port, delegate: self)
        self.socket?.connect()
    }

    func cancel() {
        self.fail?(nil)
        self.socket?.close()
    }

    func data(settings:StorageSessionTransport) -> Data? {
        var binData = Data()
        for item in settings.items {
            if let data = item.data() {
                binData.append(data)
            }
        }
        let contentLenght = binData.count
        let postRequestString = "POST http://\(settings.host!):\(settings.port)/mobistream/\(settings.stream!)/\(settings.lastTs)\r\nContent-Length: \(contentLenght)\r\n\r\n"
        var requestData = postRequestString.data(using: .utf8)
        requestData?.append(binData)
        return requestData
    }
}

extension UploadOperation: SocketConnectionDelegate {

    func socketConnection(speed: Double) {
        
    }

    func registerServerQueryString() -> String {
        var result = ""
        if let settings = self.session, let sdpString = settings.sdp {
            var body = ""
            body += "{\"action\":\"register_camera\","
           // body += "\"rtp-padding-has-unixtimestamp\":true,"
            body += "\"parameters\":{"
            body += "\"channelid\":\"\(settings.stream!)\","
            if let ip = NetworkUtil.getIPAddress() {
                body += "\"ip\":\"\(ip)\","
            }else{
                body += "\"ip\":\"0.0.0.0\","
            }
            body += "\"sdp\":\""
            body += sdpString
            body += "\"}}"

            result += "POST /api HTTP/1.1\r\nConnection: keep-alive\r\n"
            result += "Content-Length: \(body.lengthOfBytes(using: String.Encoding.utf8))\r\n"
            result += "Content-Type: application/json\r\n"
            result += "Host: \(settings.host!):\(settings.port)\r\n"
            result += "User-Agent: MobiStreamIOS\r\n\r\n"
            result += body
        }
        return result
    }

    func socketConnection(state: SocketConnectionState) {
        switch state {
        case .connecting:
            isConnected = false
        case .connected:
            print("CONNECTED")
            isConnected = true
            if let settings = self.session {
                DispatchQueue.global(qos: .userInitiated).async {
                    let registerPost = self.registerServerQueryString()
                    let data = registerPost.data(using: .utf8)
                    _ = self.socket?.write(data)
                }
            }
        case .disconnected:
            isConnected = false
            fail?(nil)
        //            delegate?.frameManager(registerCamera: isRegister, error:  nil)
        case .error(let error):
            print("ERROR:\(error)")
            fail?(error)
            isConnected = false
//            isRegister = false
//            delegate?.frameManager(registerCamera: isRegister, error:  error)
            print(error.localizedDescription)
        case .receive(let message):
            if message.contains("{\"action\":\"get_video\",\"success\":true}") {
                if let session = self.session {
                    DispatchQueue.global(qos: .userInitiated).async {
                        if let data = self.data(settings: session) {
                            let towrite = data.count
                            var sumSended = 0
                            
                            print("Start upload data for size: \(data.count)")
                            self.progress?(sumSended, towrite)
                            let sourceData = data
                            var rangeStartByte = 0
                            let dataLength = sourceData.count
                            precondition(self.maxSubdataLength <= dataLength, "maxSubdataLength must be <= to dataLength")
                            while rangeStartByte < dataLength {
                                let subdataLength = min(self.maxSubdataLength, dataLength - rangeStartByte)
                                let subdata = Data(sourceData.subdata(in: rangeStartByte ..< (rangeStartByte + subdataLength)))
                                if let writed = self.socket?.write(subdata) {
                                    sumSended += writed
                                    self.progress?(sumSended, towrite)
                                }
                                rangeStartByte += subdataLength
                            }
                            print("Upload data size: \(sumSended)")
                            self.socket?.close()
                            self.success?(["writed":sumSended, "towrite":towrite, "success":true] as AnyObject)
                        }
                    }
                }
            }
        }
    }
}

