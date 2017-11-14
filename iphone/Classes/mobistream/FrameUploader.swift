//
//  FrameUploader.swift
//  Mobistreamer
//
//  Created by Александр on 16.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit
import RealmSwift

protocol FrameUploaderDelegate {
    func progress(state: ProgressState)
    func status(status:UploadOperationQueueStatus)
}

class FrameUploader: NSObject {

    var socket:SocketConnection?
    var isConnected = false
    var delegate:FrameUploaderDelegate?

    var settings:StorageRTPSession?
    let uploadDispatchQueue = DispatchQueue(label: "ru.netris.queue.uploader")

    var operationsQueue:OperationQueue = OperationQueue()
    var transportArray = [StorageSessionTransport]()
    var currentIndex = 0

    var uploadOperationQueue = UploadOperationQueue()

    var view:StorageViewInput?

    func uploadFrames() {
        if currentIndex < transportArray.count {
            let ti = transportArray[currentIndex]
            self.socket = SocketConnection(host: ti.host!, port: ti.port, delegate: self)
            self.socket?.connect()
        }
    }

    func data(settings:StorageRTPSession) -> Data? {
        var binData = Data()
        for item in settings.items {
            if let data = item.data() {
                binData.append(data)
            }
        }
        let contentLenght = binData.count
        let postRequestString = "POST \(settings.host!):\(settings.port)/mobistream/\(settings.stream!)/\(settings.lastTs)\r\nContent-Length: \(contentLenght)\r\n\r\n"
        var requestData = postRequestString.data(using: .utf8)
        requestData?.append(binData)
        return requestData
    }

    func data(session:StorageSessionTransport) -> Data? {
        var binData = Data()
        for item in session.items {
            if let data = item.data() {
                binData.append(data)
            }
        }
        let contentLenght = binData.count
        let postRequestString = "POST \(session.host!):\(session.port)/mobistream/\(session.stream!)/\(session.lastTs)\r\nContent-Length: \(contentLenght)\r\n\r\n"
        var requestData = postRequestString.data(using: .utf8)
        requestData?.append(binData)
        return requestData
    }

    func getStreamsName() -> String {
        var names:Set = Set<String>()
        autoreleasepool{
            let realm = try! Realm()
            let results:Results<StorageRTPSession> = realm.objects(StorageRTPSession.self)
            for item in results {
                if let stream = item.login {
                    names.insert(stream)
                }
            }
        }
        var result = ""
        for item in names {
            result += item + " "
        }
        return result
    }

    func getPartsCount() -> Int {
        var count = 0
        autoreleasepool{
            let realm = try! Realm()
            let results:Results<StorageRTPSession> = realm.objects(StorageRTPSession.self)
            count = results.count
        }
        return count
    }

    func getDataSize() -> Int {
        var size = 0
        autoreleasepool{
            let realm = try! Realm()
            let results:Results<StorageRTPSession> = realm.objects(StorageRTPSession.self)
            for item in results {
                for it in item.items {
                    if let v = it.value {
                        size += v.count
                    }
                }
            }
        }
        return size
    }

    func removeAll() {
        autoreleasepool{
            let realm = try! Realm()
            try! realm.write {
                realm.deleteAll()
            }
        }
    }

    func isDataExist() -> Bool {
        var exist = false
        autoreleasepool{
            let realm = try! Realm()
            let results:Results<StorageRTPSession> = realm.objects(StorageRTPSession.self)
            if results.count > 0 {
                exist = true
            }
        }
        return exist
    }

    func cancelUpload() {
        self.uploadOperationQueue.cancel()
        self.operationsQueue.cancelAllOperations()
    }

    func firstTs() -> Int? {
        var res:Int?
        autoreleasepool{
            let realm = try! Realm()
            if let result:StorageRTPSession = realm.objects(StorageRTPSession.self).sorted(byKeyPath: "lastTs").first {
                res = result.lastTs
            }
        }
        return res
    }

    func uploadAll() {
        self.operationsQueue.maxConcurrentOperationCount = 1
        autoreleasepool{
            let realm = try! Realm()
            let results:Results<StorageRTPSession> = realm.objects(StorageRTPSession.self).sorted(byKeyPath: "lastTs")
            self.transportArray.removeAll()
            for item in results {
                let transportItem = StorageSessionTransport(item: item)
                self.transportArray.append(transportItem)
            }
        }

        self.uploadOperationQueue = UploadOperationQueue()
        self.uploadOperationQueue.output = self
        for item in transportArray {
            self.uploadOperationQueue.addSession(session: item)
        }
        self.uploadOperationQueue.run()
    }

    func allStorageData() -> String {
        var resultString = "\n======================================\n"
        autoreleasepool{
            let realm = try! Realm()
            let results:Results<StorageRTPSession> = realm.objects(StorageRTPSession.self)
            
            resultString += "Всего частей: \(results.count)\n"
            
            resultString += "======================================\n"
            for item in results {
                resultString += "host: \(String(describing: item.host))\n"
                resultString += "port: \(item.port)\n"
                resultString += "stream: \(String(describing: item.stream))\n"
                resultString += "lastTs: \(item.lastTs)\n"
                resultString += "frame count: \(item.items.count)\n"
                resultString += "sdp: \(String(describing: item.sdp))\n"
            }
        }
        resultString += "======================================\n"
        return resultString
    }
}

extension FrameUploader:UploadOperationQueueOutput {
    
    func status(status: UploadOperationQueueStatus) {
        self.delegate?.status(status: status)
    }

    func progress(state: ProgressState) {
        self.delegate?.progress(state: state)
    }

    func message(text: String) {
        view?.writeLog(message: text)
    }
}

extension FrameUploader: SocketConnectionDelegate {

    func socketConnection(speed: Double) {
        
    }

    func socketConnection(state: SocketConnectionState) {
        switch state {
        case .connecting:
            isConnected = false
        case .connected:
            print("CONNECTED")
            isConnected = true
            if currentIndex < transportArray.count {
                self.uploadDispatchQueue.async {
                    let ti = self.transportArray[self.currentIndex]
                    let data = self.data(session: ti)
                    print("Start upload data for size: \(String(describing: data?.count))")
                    let writed = self.socket?.write(data)
                    print("UPLOADER SENDED:\(String(describing: writed))")
                }
            }
        case .disconnected:
            print("DISCONNECTED")
            isConnected = false
//            delegate?.frameManager(registerCamera: isRegister, error:  nil)
        case .error(let error):
            isConnected = false
//            isRegister = false
//            delegate?.frameManager(registerCamera: isRegister, error:  error)
            print(error.localizedDescription)
        case .receive(let message):
            print(message)
        }
    }
}

//        Докачка будет осуществлятся также пост запросом, в след виде
//
//        POST http://<server>:<port>/mobistream/<channel>/<timestamp>
//        Content-Length: <...>
//
//        <bin data>
//        <bin data> - это данные video/audio состоит из следующих пакетов:
//
//        <8 бит> - тип фрейма (h264,aac,pcm,g711 и т.д.)
//        <32 бита> - длина фрейма (в случае h264 - будет полный NALU)
//        <данные фрейма>
//
//        ....
//
//        <8 бит> <32 бита> <data> ....
