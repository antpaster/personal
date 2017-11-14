//
//  FrameStorage.swift
//  Mobistreamer
//
//  Created by Александр on 06.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit
import RealmSwift

class FrameStorage: NSObject {

    let storageDispatchQueue = DispatchQueue(label: "ru.netris.queue.storage")
    var sessionSettings:FrameManagerSessionSettings = FrameManagerSessionSettings()

    func allStorageData() -> String {
        var resultString = "\n======================================"
        autoreleasepool{
            let realm = try! Realm()
            let results:Results<StorageRTPSession> = realm.objects(StorageRTPSession.self)
            for item in results {
                resultString += "host: \(item.host)"
                resultString += "port: \(item.port)"
                resultString += "stream: \(item.stream)"
                resultString += "lastTs: \(item.lastTs)"
                resultString += "frame count: \(item.items.count)"
                resultString += "sdp: \(String(describing: item.sdp))"
            }
        }
        resultString += "======================================\n"
        return resultString
    }

}

extension FrameStorage: FrameQueueStorage {

    func bufferFlush(video: [FrameEntity], audio: [FrameEntity], ts:Int) {

        // проверяем если есть такая херня, то дописываем  список кадров в базу
        // если нет, то создаем новую запись в базе

        let concurrent = ConcurrentQueque()
        concurrent.videoItems = video
        concurrent.audioItems = audio

        var multiplexQueue = [FrameEntity]()
        var frame:FrameEntity? = concurrent.pop()
        var list:[StorageFrameItem] = [StorageFrameItem]()

        while  frame != nil {
            let item = StorageFrameItem()
            item.ts = (frame?.ts)!
            item.rawType = frame?.type?.rawValue
            item.value = frame?.value
            item.time = (frame?.time)!

            list.append(item)
            multiplexQueue.append(frame!)
            frame = concurrent.pop()
        }

        DispatchQueue(label: "background").async {
            autoreleasepool {
                let realm = try! Realm()
                if let session = realm.objects(StorageRTPSession.self).filter("lastTs == \(ts)").first {
                    // дописываем и сохраняем
                    try! realm.write {
                        for item in list {
                            session.items.append(item)
                        }
                    }
                }else{
                    // создаем и и хуярим в базу
                    let session = StorageRTPSession()
                    session.host = self.sessionSettings.host
                    session.port = (self.sessionSettings.port)!
                    session.sdp = self.sessionSettings.sdp
                    session.stream = self.sessionSettings.stream
                    session.login = self.sessionSettings.settings?.login
                    session.lastTs = ts

                    for item in list {
                        session.items.append(item)
                    }

                    try! realm.write {
                        realm.add(session)
                    }
                }
            }
        }
    }

    func saveSettings(session:StorageRTPSession) {
    }
}
