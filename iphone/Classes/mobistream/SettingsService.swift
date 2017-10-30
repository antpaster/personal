//
//  SettingsService.swift
//  Mobistreamer
//
//  Created by Александр on 21.05.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import Foundation

public enum StreamMode:Int {
    case audioOnly = 0
    case videoOnly = 1
    case audioVideo = 2
}

///
// streamMode = "a|v|av" - строка
// videoSize = "640x480|1280x720" - строка с размерами, посредине латинская x
// bitrate = 2000000|700000 - int без сокращений
// framerate = 25|30 - int
///
// добавить еще поле showGpsInVideo

struct Server {
    var host:String?
    var port:Int?
    var stream:String?
    var reconnect:Bool?
    var gpsEnabled:Bool?
    var gpsHost:String?
    var gpsPort:Int?
    var showGpsInVideo:Bool?

    var camera:CameraSettings?
}

class CameraSettings: NSObject {
    var frameRate:Int?
    var bitRate:Int?
    var streamMode:Int?
    var presetSize:String?
}

class LoginSettings: NSObject {
    var save:Bool = false
    var login:String?
    var password:String?
}

class CameraSettingList: NSObject {

    var list:[String:Server] = [String:Server]()
    var current:String?

    func count() -> Int {
        return list.count
    }

    func add(_ server:Server, name:String) {
        list[name] = server
    }

    func remove(_ name:String) {
        list.removeValue(forKey: name)
    }

    func names() -> [String] {
        return Array(list.keys)
    }

    func getServer(_ name:String) -> Server? {
        return list[name]
    }
}

class SettingsService {
    var defaults = UserDefaults.standard

    let BITRATE_STRING = "CameraBitrate"
    let STREAM_MODE_STRING = "CameraStreamMode"
    let FRAMERATE_STRING = "CameraFramerate"
    let VIDEO_SIZE_STRING = "CameraVideoSize"
    let TITLE_TEXT_STRING = "CameraTitleText"
    
    let LOGIN_STRING = "login"
    let PASSWORD_STRING = "password"
    let IS_SAVE_STRING = "save"

    func setSettings(_ settings:CameraSettingList) {
        defaults.set(settings, forKey: "settings")
    }

    func getSettings() -> CameraSettingList? {
        let def = defaults.object(forKey: "settings") as? CameraSettingList
        if nil != def {
            return def
        }
        defaults.set(CameraSettingList(), forKey: "settings")
        return defaults.object(forKey: "settings") as? CameraSettingList
    }

    func getCameraSettings() -> CameraSettings {
        let defaultSettings = CameraSettings()
        defaultSettings.bitRate = getBitrate()
        defaultSettings.streamMode = getStreamMode()
        defaultSettings.frameRate = getFramerate()
        defaultSettings.presetSize = getVideoSize()
        return defaultSettings
    }

    func setCameraSettings(_ settings:CameraSettings) {
        if let bitrate = settings.bitRate {
            setBitrate(bitrate)
        }
        if let frameRate = settings.frameRate {
            setFramerate(frameRate)
        }
        if let presetSize = settings.presetSize {
            setVideoSize(presetSize)
        }
        if let streamMode = settings.streamMode {
            setStreamMode(streamMode)
        }
    }

    func getLoginSettings() -> LoginSettings {
        let defaultSettings = LoginSettings()
        defaultSettings.login = defaults.object(forKey: LOGIN_STRING) as? String
        defaultSettings.password = defaults.object(forKey: PASSWORD_STRING) as? String
        if let save = defaults.object(forKey: IS_SAVE_STRING) as? Bool {
            defaultSettings.save = save
        }
        return defaultSettings
    }
    
    func setLoginSettings(_ settings:LoginSettings) {
        defaults.set(settings.login, forKey: LOGIN_STRING)
        defaults.set(settings.password, forKey: PASSWORD_STRING)
        defaults.set(settings.save, forKey: IS_SAVE_STRING)
    }

    func setBitrate(_ bitrate: Int) {
        defaults.set(bitrate, forKey: BITRATE_STRING)
    }

    func getBitrate() -> Int {
        let def = defaults.object(forKey: BITRATE_STRING) as? Int
        if let def = def {
            return def
        }
        defaults.set(0, forKey: BITRATE_STRING)
        return 0
    }

    func setStreamMode(_ mode: Int) {
        defaults.set(mode, forKey: STREAM_MODE_STRING)
    }

    func getStreamMode() -> Int {
        let def = defaults.object(forKey: STREAM_MODE_STRING) as? Int
        if let def = def {
            return def
        }
        defaults.set(1, forKey: STREAM_MODE_STRING)
        return 1
    }

    func setFramerate(_ framerate: Int) {
        defaults.set(framerate, forKey: FRAMERATE_STRING)
    }

    func getFramerate() -> Int {
        let def = defaults.object(forKey: FRAMERATE_STRING) as? Int
        if let def = def {
            return def
        }
        defaults.set(30, forKey:FRAMERATE_STRING)
        return 30
    }

    func setVideoSize(_ size: String) {
        defaults.set(size, forKey: VIDEO_SIZE_STRING)
    }

    func getVideoSize() -> String {
        let def = defaults.object(forKey: VIDEO_SIZE_STRING) as? String
        if let def = def, def != "" {
            return def
        }
        defaults.set("640x480", forKey: VIDEO_SIZE_STRING)
        return "640x480"
    }

    func setTitleText(_ text: String) {
        defaults.set(text, forKey: TITLE_TEXT_STRING)
    }

    func getTitleText() -> String {
        let def = defaults.object(forKey: TITLE_TEXT_STRING) as? String
        if let def = def {
            return def
        }
        defaults.set("Mobistream", forKey: TITLE_TEXT_STRING)
        return "Mobistream"
    }

}
