//
//  FrameEntity.swift
//  Mobistreamer
//
//  Created by Александр on 05.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import CoreFoundation

enum NetrisFrameType:Int{
    case unknownStreamType = 0
    case h264 = 1                     // поток h264
    case g711 = 2                     // поток g711
    case aac = 3                      // поток aac
    case archive_config = 4           // конфигурация архива
    case mjpeg = 5                    // поток mjpeg
}

enum FrameEntityType:String {
    case audio = "audio"
    case video = "video"
}

class FrameEntity: Comparable {
    var ts:Double = 0
    var time:Int = 0
    var type:FrameEntityType?
    var value:Data?
}

func < (lhs: FrameEntity, rhs: FrameEntity) -> Bool {
    return lhs.ts < rhs.ts
}

func == (lhs: FrameEntity, rhs: FrameEntity) -> Bool {
    return lhs.ts == rhs.ts
}
