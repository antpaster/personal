//
//  StorageSessionTransport.swift
//  Mobistreamer
//
//  Created by Александр on 21.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit

class StorageSessionTransport: NSObject {
    var host:String? = nil
    var port:Int = 0
    var stream:String? = nil
    var sdp:String? = nil
    var lastTs:Int = 0
    
    var items = [StorageFrameItemTransport]()
    
    init(item:StorageRTPSession) {
        self.host = item.host
        self.port = item.port
        self.stream = item.stream
        self.sdp = item.sdp
        self.lastTs = item.lastTs

        for it in item.items {
            items.append(StorageFrameItemTransport(item: it))
        }
    }
}
