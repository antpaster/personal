//
//  ServerSettings.swift
//  SwiftMobistream
//
//  Created by netris on 24.05.16.
//  Copyright © 2016 netris. All rights reserved.
//

import UIKit

class ServerSettings: NSObject {
    var id:Int?
    var name:String?
    var host:String?
    var port:Int?
    var channel:String?
    var pnp:Bool = false
    var hostGeoServer:String?
    var portGeoServer:Int?
    var userId:Int?
    var streamWatchUrl:String?
}
//{
// geoServerHost = "";
// geoServerPort = 0;
// host = "195.208.65.189";
// id = 3;
// name = echd;
// pnp = 0;
// port = 2021;
// streamChannel = 51;
// streamWatchUrl = "";
// userId = 3;
//}