//
//  FrameItemTransport.swift
//  Mobistreamer
//
//  Created by Александр on 21.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit

class StorageFrameItemTransport: NSObject {

    var rawType:String?
    var ts:Double = 0
    var time:Int = 0
    var value:Data? = nil

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

    init(item:StorageFrameItem) {
        self.rawType = item.rawType
        self.ts = item.ts
        self.time = item.time
        self.value = item.value
    }

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

