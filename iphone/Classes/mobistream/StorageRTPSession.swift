//
//  StorageRTPSessionSettings.swift
//  Mobistreamer
//
//  Created by Александр on 02.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import Foundation
import RealmSwift

class StorageRTPSession: Object {
//    dynamic var id:Int = 0
    @objc dynamic var host:String? = nil
    @objc dynamic var port:Int = 0
    @objc dynamic var stream:String? = nil
    @objc dynamic var login:String? = nil
    @objc dynamic var sdp:String? = nil
    @objc dynamic var lastTs:Int = 0

    let items = List<StorageFrameItem>()

}
