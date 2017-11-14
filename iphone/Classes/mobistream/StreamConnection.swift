//
//  StreamConnection.swift
//  SwiftMobistream
//
//  Created by netris on 03.06.16.
//  Copyright © 2016 netris. All rights reserved.
//

import UIKit

enum StreamConnectionError: Error {
    case none
    case error(String)
}

class StreamConnection: NSObject, SimpleConnectionDelegate {

    var host:String?
    var port:Int32?
    var channel:String?
    var sdp:String?

    var delegate:ConnectionDelegate?

    var simpleConnection:SimpleConnection?
    
    var registerInProgress = false
    var connected = false

    init(host:String, port:Int32, channel:String, sdp:String, delegate: ConnectionDelegate) {
        self.delegate = delegate
        self.host = host
        self.port = port
        self.channel = channel
        self.sdp = sdp

        self.simpleConnection = SimpleConnection(host: host, andPort: port)
    }
    
    func connect() {
        self.simpleConnection?.setDelegate(self)
        registerInProgress = false
        connected = false
        simpleConnection?.connect()
    }
    
    func disconnect() {
        simpleConnection?.disconnect()
    }

    func write(_ data: Data) -> Int {
        if let count = simpleConnection?.write(data) {
            return count
        }
        return -1
    }

    func onMessageReceived(_ message: Data!) {
        
    }

    func onMessageReceivedString(_ message: String!, fromConnection connection: Any!) {
        print(message);
        if registerInProgress {
            registerInProgress = false
            if isMessageRegisterCameraOk(message) {
//                delegate?.onVideoRegistered!(self, connected: true, withError: NSError(domain: "", code: 0, userInfo: nil))
                //delegate?.onVideoRegistered!(self, connected: true, withError: Error(domain: "", code: 0, userInfo: nil))

                delegate?.onVideoRegistered!(self, connected: true, withError: StreamConnectionError.none)
            }else{
                print("error onMessagerecive")
                delegate?.onVideoRegistered!(self, connected: false, withError: StreamConnectionError.error(message))
            }
        }
    }

    func onConnected(_ connection: Any!, isConnected: Bool, withError error: Error!) {
        connected = isConnected
        if isConnected {
            print("CONNECTED!")
            requestRegisterCamera()
        } else {
            print(error)
            delegate?.onVideoRegistered?(self, connected: false, withError: error)
        }
    }

    func registerServerQueryString() -> String {
        var body = ""
        body += "{\"action\":\"register_camera\","
        body += "\"parameters\":{"
        body += "\"channelid\":\"\(self.channel!)\","
        
        if let ip = NetworkUtil.getIPAddress() {
            body += "\"ip\":\"\(ip)\","
        }else{
            body += "\"ip\":\"0.0.0.0\","
        }
        
        body += "\"sdp\":\""
        body += self.sdp!.replacingOccurrences(of: "\r\n", with: "\\\\r\\\\n")
        body += "\"}}"
        
        var result = ""
        result += "POST /api HTTP/1.1\r\nConnection: keep-alive\r\n"
        result += "Content-Length: \(body.lengthOfBytes(using: String.Encoding.utf8))\r\n"
        result += "Content-Type: application/json\r\n"
        result += "Host: \(self.host!):\(self.port!)\r\n"
        result += "User-Agent: MobiStreamIOS\r\n\r\n"
        result += body
        return result
    }

    func requestRegisterCamera() {
        registerInProgress = true
        print("requestRegisterCamera: \(registerServerQueryString())")
        simpleConnection?.write(registerServerQueryString().data(using: String.Encoding.utf8))
    }
    
    func isMessageRegisterCameraOk(_ answer:String) -> Bool {
        if answer.contains("\"action\":\"get_video\"") && answer.contains("\"success\":true") {
            return true
        }
        return false
    }
}



