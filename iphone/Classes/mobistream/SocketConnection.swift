//
//  CDNConnection.swift
//  AreaSight
//
//  Created by Александр on 05.05.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import CoreFoundation

enum SocketConnectionState {
    case connecting
    case connected
    case disconnected
    case error(error:Error)
    case receive(message:String)
}

protocol SocketConnectionDelegate {
    func socketConnection(state:SocketConnectionState)
    func socketConnection(speed:Double)
}

class SocketConnection: NSObject, StreamDelegate {

    var delegate:SocketConnectionDelegate?
    
    var lock : NSRecursiveLock = NSRecursiveLock.init()
    var semaphore = DispatchSemaphore(value: 1)
    var state:SocketConnectionState = .disconnected
    
    var host:String?
    var port:Int?

    var readStream : Unmanaged<CFReadStream>?
    var writeStream : Unmanaged<CFWriteStream>?

    var outputStream:OutputStream?
    var inputStream:InputStream?
    
    var isInputConnected = false
    var isOutputConnected = false
    
    var isConnected:Bool {
        get{
            if inputStream == nil {
                return false
            }
            return false
        }
    }

    init(host:String, port:Int, delegate:SocketConnectionDelegate) {
        self.host = host
        self.port = port
        self.delegate = delegate
    }

    func connect() {
        guard nil != self.host else { return }
        
//        lock.lock()
//        autoreleasepool {
        let host : CFString = NSString(string: self.host!)
        let port : UInt32 = UInt32(self.port!)

//            var inp :InputStream?
//            var out :OutputStream?
//            Stream.getStreamsToHost(withName: host as String, port: Int(port), inputStream: &inp, outputStream: &out)

//            inputStream = inp!
//            outputStream = out!
        CFStreamCreatePairWithSocketToHost(kCFAllocatorDefault, host, port, &readStream, &writeStream)

        inputStream = readStream!.takeRetainedValue()
        outputStream = writeStream!.takeRetainedValue()

        print("CONNECT START")
        inputStream!.delegate = self
        outputStream!.delegate = self

        self.inputStream!.schedule(in: .main, forMode: RunLoopMode.defaultRunLoopMode)
        self.outputStream!.schedule(in: .main, forMode: RunLoopMode.defaultRunLoopMode)
        
        inputStream!.open()
        outputStream!.open()

        print("CONNECT END")
//        }
//        lock.unlock()
        
        /*
        var buffer = [UInt8](repeating: 0, count: 59)
        let readed = self.inputStream?.read(&buffer, maxLength: buffer.count)
        print("readed: \(String(describing: readed))")
        let str = String(bytes: buffer, encoding: String.Encoding.ascii)
        print(str)
        var buffer4 = [UInt8](repeating: 0, count: 100)
        let readed4 = self.inputStream?.read(&buffer4, maxLength: buffer4.count)
        let ss = Data(buffer4).hexadecimalString()
        print(ss)
         */
    }

    func cancel(){
        
    }

    func write(message:String) -> Int? {
        let data = message.data(using: .utf8, allowLossyConversion: false)
        let bytesWritten = data?.withUnsafeBytes { outputStream?.write($0, maxLength: (data?.count)!) }
        return bytesWritten
    }

    var sumSpeed:Double = 0
    var sumCount:Int = 0

    func write(_ data:Data?) -> Int? {
//        NSTimeInterval start = [NSDate timeIntervalSinceReferenceDate];
        let start = Date().timeIntervalSinceReferenceDate
        self.semaphore.wait()
        let bytesWritten = data?.withUnsafeBytes { outputStream?.write($0, maxLength: (data?.count)!) }
        self.semaphore.signal()
        var speed:Double = 0
        if let bytesWritten = bytesWritten {
            speed = Double(bytesWritten) / Double((Date().timeIntervalSinceReferenceDate - start))

            sumSpeed = sumSpeed + speed
            sumCount = sumCount + 1

            if sumCount > 200 {
                let res = sumSpeed / Double(sumCount)
                delegate?.socketConnection(speed: res)
                sumSpeed = 0
                sumCount = 0
            }
        }
        return bytesWritten
    }

    func close() {
        print("CLOSE")
        self.semaphore.wait()
        isInputConnected = false
        isOutputConnected = false
        outputStream?.close()
        inputStream?.close()

        writeStream = nil
        readStream = nil
        
        outputStream = nil
        inputStream = nil
        writeStream = nil
        readStream = nil
        self.semaphore.signal()
    }

    func stream(_ aStream: Stream, handle eventCode: Stream.Event) {
        if aStream == inputStream {
            inputStream(eventCode: eventCode)
        }
        if aStream == outputStream {
            outputStream(eventCode: eventCode)
        }
    }

    func inputStream(eventCode: Stream.Event) {
        switch eventCode {
        case Stream.Event.openCompleted:
            self.isInputConnected = true
            connected()
            print("inputStream openCompleted")
        case Stream.Event.hasBytesAvailable:
            print("inputStream hasBytesAvailable")
            var buffer = [UInt8](repeating: 0, count: 4096)
            let readed = self.inputStream?.read(&buffer, maxLength: buffer.count)
            if let readed = readed {
                let data = NSData(bytes: buffer, length: Int(readed))
                if let message = String(data: data as Data, encoding: .utf8) {
                    delegate?.socketConnection(state: .receive(message: message))
                }
            }
        case Stream.Event.hasSpaceAvailable:
            print("inputStream hasSpaceAvailable")
        case Stream.Event.errorOccurred:
//            inputStream?.streamError
            self.isInputConnected = false
            connectionLost()
            print("inputStream errorOccurred")
        case Stream.Event.endEncountered:
            print("inputStream endEncountered")
            inputStream?.close()
            inputStream?.remove(from: .main, forMode: RunLoopMode.defaultRunLoopMode)
        default:
            print("inputStream default")
        }
    }
    
    func outputStream(eventCode: Stream.Event) {
        switch eventCode {
        case Stream.Event.openCompleted:
            print("outputStream openCompleted")
            self.isOutputConnected = true
            connected()
        case Stream.Event.hasBytesAvailable:
            print("outputStream hasBytesAvailable")
        case Stream.Event.hasSpaceAvailable:
//            print("outputStream hasSpaceAvailable")
            break
        case Stream.Event.errorOccurred:
            self.isOutputConnected = false
            connectionLost()
            print("outputStream errorOccurred")
        case Stream.Event.endEncountered:
            print("outputStream endEncountered")
            outputStream?.close()
            outputStream?.remove(from: .main, forMode: RunLoopMode.defaultRunLoopMode)
        default:
            print("outputStream default")
        }
    }

    func connected() {
        if isInputConnected && isOutputConnected {
            delegate?.socketConnection(state: .connected)
        }
    }

    func connectionLost() {
        if !isInputConnected && !isOutputConnected {
            delegate?.socketConnection(state: .disconnected)
        }
    }
}
