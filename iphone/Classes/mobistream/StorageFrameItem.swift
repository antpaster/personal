//
//  StorageFrameItem.swift
//  Mobistreamer
//
//  Created by Александр on 06.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit
import RealmSwift

class StorageFrameItem: Object {
    @objc dynamic var rawType:String?
    @objc dynamic var ts:Double = 0
    @objc dynamic var time:Int = 0
    @objc dynamic var value:Data? = nil
//    dynamic var lastId:Int = 0

    var type:FrameEntityType? {
        get {
            if let rawType = rawType {
                return FrameEntityType(rawValue:rawType)
            }
            return nil
        }
        set {
            rawType = newValue?.rawValue
        }
    }
}

extension StorageFrameItem {

    func data() -> Data? {
        guard let type = self.type, let value = self.value else {
            return nil
        }
        var byteType:UInt8 = 1
        if type == .audio {
            byteType = 3
        }
        let typeData = Data(bytes: &byteType, count: MemoryLayout.size(ofValue: byteType))
        var size:Int32 = Int32(value.count)
        let sizeData = Data(bytes: &size, count: MemoryLayout.size(ofValue: size))

        var resultData = Data()
        resultData.append(typeData)
        resultData.append(sizeData)
        resultData.append(value)

        return resultData
    }
}
