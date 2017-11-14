//
//  VideoService.swift
//  Mobistreamer
//
//  Created by Александр on 22.05.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit

enum NetworkQualityStatus {
    case none
    case bad
    case normal
    case good
}

protocol VideoServiceOut {
    func videoServiceStatus(status:MobistreamManagerState)
    func videoService(error:Error)
    func videoService(signal:NetworkQualityStatus)
    func bufferOverFlow()
    func videoService(test:StreamCameraManagerTestStatus)
    func startingAtFirstIDR()
}

class VideoService: NSObject {

    var videoServiceOut:VideoServiceOut?
    var serverSettings:ServerSettingsEntity?
    var mobistreamManager:MobistreamManager?
    var state:MobistreamManagerState = .none

    var networkQualityStatus:NetworkQualityStatus = .none

    private override init() {
        
    }

    init(settings:ServerSettingsEntity, videoView:UIView) {
        super.init()
        serverSettings = settings
        guard let host = serverSettings?.host, let port = serverSettings?.port, let stream = serverSettings?.stream else {
            videoServiceOut?.videoService(error: EchdError.notValidUserData)
            return
        }

        mobistreamManager = MobistreamManager(host: host, port: Int32(port), stream: stream)
        mobistreamManager?.serverSettings = settings
        mobistreamManager?.delegate = self
        if let title = serverSettings?.live {
            VideoEncoder.titleText = title
        }
        mobistreamManager?.addPreviewLayerToView(videoView)
        mobistreamManager?.setCameraDevice(.back)

//        mobistreamManager?.setStreamMode(.videoWithMic)
        
//        let streamMode = SettingsService().getStreamMode()
//        switch streamMode {
//        case 0:
//            mobistreamManager?.setStreamMode(.micOnly)
//        case 1:
//            mobistreamManager?.setStreamMode(.videoOnly)
//        case 2:
//            mobistreamManager?.setStreamMode(.videoWithMic)
//        default:
//            break
//        }
        
        
        
        mobistreamManager?.testVideo()
        mobistreamManager?.setVideoOrientation(.portrait)
        
        networkQualityStatus = .none
        videoServiceOut?.videoService(signal: networkQualityStatus)

        
//        if let host = serverSettings?.host, let port = serverSettings?.port, let stream = serverSettings?.stream {
//            mobistreamManager = MobistreamManager(host: host, port: Int32(port), stream: stream)
//            mobistreamManager?.serverSettings = settings
//            mobistreamManager?.delegate = self
//            if let title = serverSettings?.live {
//                VideoEncoder.titleText = title
//            }
//            mobistreamManager?.addPreviewLayerToView(videoView)
//            mobistreamManager?.setCameraDevice(.back)
//            mobistreamManager?.setStreamMode(.videoWithMic)
//            mobistreamManager?.testVideo()
//            mobistreamManager?.setVideoOrientation(.portrait)
//
//            networkQualityStatus = .none
//            videoServiceOut?.videoService(signal: networkQualityStatus)
//        }else{
//            let userInfo: [AnyHashable: Any] = [
//                NSLocalizedDescriptionKey :  "Во время авторизации Сервер прислал не валидные данные.",
//                NSLocalizedFailureReasonErrorKey : ""
//            ]
//            videoServiceOut?.videoService(error: NSError(domain: "EchdAuthService", code: 100, userInfo: userInfo as! [String : Any]) as Error)
//        }
    }
    
    func configure() {
        print("configure()")

        let streamMode = SettingsService().getStreamMode()
        switch streamMode {
        case 0:
            mobistreamManager?.setStreamMode(.videoOnly)
        case 1:
            mobistreamManager?.setStreamMode(.videoWithMic)
        case 2:
            mobistreamManager?.setStreamMode(.micOnly)
        default:
            break
        }
//        switch streamMode {
//        case 0:
//            mobistreamManager?.setStreamMode(.micOnly)
//        case 1:
//            mobistreamManager?.setStreamMode(.videoOnly)
//        case 2:
//            mobistreamManager?.setStreamMode(.videoWithMic)
//        default:
//            break
//        }

        VideoEncoder.sharedInstance.reloadEncoder()
        mobistreamManager?.update()
        mobistreamManager?.testVideo()

//        MobistreamManager.sharedInstance.delegate = self
//        MobistreamManager.sharedInstance.addPreviewLayerToView(self.previewView)
//        MobistreamManager.sharedInstance.setCameraDevice(.back)
//        MobistreamManager.sharedInstance.setStreamMode(.videoWithMic)
//        MobistreamManager.sharedInstance.testVideo()
//        self.updateButtons()
//        MobistreamManager.sharedInstance.setVideoOrientation(.portrait)
//        _ = self.shouldAutorotate
    }

    func hasTorch() -> Bool {
        if let manager = self.mobistreamManager {
            return manager.hasTorch()
        }
        return false
    }

    func switchTorch() {
        if hasTorch() {
            if let manager = mobistreamManager {
                switch manager.torchMode() {
                case .on:
                    mobistreamManager?.setTorchMode(.off)
                case .off:
                    mobistreamManager?.setTorchMode(.on)
                case .auto:
                    mobistreamManager?.setTorchMode(.off)
                }
            }
        }
    }

    func switchCamera() {
        if let manager = mobistreamManager {
            switch manager.cameraDevice() {
            case .back:
                mobistreamManager?.setCameraDevice(.front)
            case .front:
                mobistreamManager?.setCameraDevice(.back)
            }
        }
    }

    func start() {
        switch SettingsService().getStreamMode() {
        case 0:
            AudioEncoder.sharedInstance.mute(true)
        case 1:
            AudioEncoder.sharedInstance.mute(false)
        case 2:
            AudioEncoder.sharedInstance.mute(false)
        default:
            break
        }
        mobistreamManager?.start()
        UIApplication.shared.isIdleTimerDisabled = true
    }

    func stop() {
        UIApplication.shared.isIdleTimerDisabled = false
        stopGpsServer()
        mobistreamManager?.stop()

        networkQualityStatus = .none
        videoServiceOut?.videoService(signal: networkQualityStatus)
    }

    func startGpsServer() {
//        EchdLocationService.shared.start()
    }

    func stopGpsServer() {
//        EchdLocationService.shared.stop()
    }

    var orientation:Int = 1 {
        didSet{
            VideoEncoder.sharedInstance.orientation = Int32(orientation)
            switch orientation {
            case 0:
                mobistreamManager?.setVideoOrientation(.landscapeLeft)
            case 1:
                mobistreamManager?.setVideoOrientation(.portrait)
            case 2:
                mobistreamManager?.setVideoOrientation(.landscapeRight)
            case 3:
                mobistreamManager?.setVideoOrientation(.portraitUpsideDown)
            default:
                mobistreamManager?.setVideoOrientation(.portrait)
            }
        }
    }
}

extension VideoService: MobistreamManagerDelegate {

    func startingAtFirstIDR() {
        videoServiceOut?.startingAtFirstIDR()
    }

    func mobistreamManager(_ sender: MobistreamManager, testStatus: StreamCameraManagerTestStatus) {
        videoServiceOut?.videoService(test: testStatus)
    }

    func bufferOverFlow() {
        networkQualityStatus = .bad
        videoServiceOut?.videoService(signal: networkQualityStatus)
        videoServiceOut?.bufferOverFlow()
    }

    func mobistreamManager(_ sender: MobistreamManager, speed: Double) {
//        print("speed: \(Int(speed)) bitrate: \(VideoEncoder.sharedInstance.averageBitRate)")
        
        if Int(VideoEncoder.sharedInstance.averageBitRate) < Int(speed) {
            networkQualityStatus = .good
        } else if Int(VideoEncoder.sharedInstance.averageBitRate) / 2 < Int(speed) && Int(speed) <= Int(VideoEncoder.sharedInstance.averageBitRate) {
            networkQualityStatus = .normal
        } else {
            networkQualityStatus = .bad
        }
        
        videoServiceOut?.videoService(signal: networkQualityStatus)
        
//        speed: 4187782.48699254 bitrate: 3670016
//        speed: 3872597.07194521 bitrate: 3670016
//        speed: 4883862.60873456 bitrate: 3670016
//        speed: 4100605.14493618 bitrate: 3670016
//        speed: 3679350.33743315 bitrate: 3670016
//        speed: 4781176.14557861 bitrate: 3670016
//        speed: 3701000.63031256 bitrate: 3670016
//        speed: 4137670.7607462 bitrate: 3670016
//        speed: 3814238.06872499 bitrate: 3670016
//        speed: 3687320.44786472 bitrate: 3670016
    }

    func mobistreamManager(_ sender: MobistreamManager, state: MobistreamManagerState) {
        self.state = state
        videoServiceOut?.videoServiceStatus(status: state)
        switch state {
        case .connecting:
            print(".connecting")
        case .run:
            print(".run")
            startGpsServer()
        case .stop(let error):
            if let error = error {
                self.videoServiceOut?.videoService(error: error)
            }
            print("stop: \(String(describing: error))")
        case .none:
            print(".none")
        }
    }
}
