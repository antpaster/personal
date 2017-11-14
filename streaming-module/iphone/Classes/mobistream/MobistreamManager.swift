//
//  MobistreamManager.swift
//  SwiftMobistream
//
//  Created by netris on 06.06.16.
//  Copyright © 2016 netris. All rights reserved.
//

import UIKit
import AVFoundation

public enum MobistreamManagerState {
    case none
    case connecting
    case run
    case stop(Error?)
}

protocol MobistreamManagerDelegate : class{
    func mobistreamManager(_ sender: MobistreamManager, state:MobistreamManagerState)
    func mobistreamManager(_ sender: MobistreamManager, testStatus:StreamCameraManagerTestStatus)
    func mobistreamManager(_ sender: MobistreamManager, speed:Double)
    func bufferOverFlow()
    func startingAtFirstIDR()
}

class MobistreamManager: NSObject {

    var delegate:MobistreamManagerDelegate?

    var cameraManager:StreamCameraManager = StreamCameraManager()
    var frameManager = FrameManager()
    var serverSettings:ServerSettingsEntity?

    let serialQueue:DispatchQueue = DispatchQueue(label: "ru.netris.mySerialQueueqwe")

    var host:String?
    var port:Int32?
    var stream:String?

    var sps:String?
    var pps:String?
    var profileLevelId:String?

    var state:MobistreamManagerState = .none
    
    var connected:Bool = false
    var record:Bool = false

    var supportedPresets:[String:[Int]] {
        get{
            return self.cameraManager.supportedPresets
        }
    }

    init(host:String, port:Int32, stream:String) {
        self.host = host
        self.port = port
        self.stream = stream
    }

    func start() {
        if let sps = self.sps, let pps = self.pps, let profileLevelId = self.profileLevelId, let host = self.host, let port = self.port, let stream = stream {
//record = true
            state = .connecting

            self.delegate?.mobistreamManager(self, state: self.state)
            
            
            //            ConnectionManager.sharedInstance.host = "195.208.65.189"
            //            ConnectionManager.sharedInstance.port = 2021
            //            ConnectionManager.sharedInstance.channel = "51"
            
            //            ConnectionManager.sharedInstance.host = "172.16.1.141"
            //            ConnectionManager.sharedInstance.port = 2043
            //            ConnectionManager.sharedInstance.channel = "51"
            
            //            ConnectionManager.sharedInstance.host = "172.16.1.185"
            //            ConnectionManager.sharedInstance.port = 2043
            //            ConnectionManager.sharedInstance.channel = "51"
            
            //            ConnectionManager.sharedInstance.host = "172.16.1.94"
            //            ConnectionManager.sharedInstance.port = 2043
            //            ConnectionManager.sharedInstance.channel = "774"
            
/*
            ConnectionManager.sharedInstance.host = host
            ConnectionManager.sharedInstance.port = port
            ConnectionManager.sharedInstance.channel = stream

            ConnectionManager.sharedInstance.sps = sps
            ConnectionManager.sharedInstance.pps = pps
            ConnectionManager.sharedInstance.profileLevelId = profileLevelId
            ConnectionManager.sharedInstance.delegate = self
            ConnectionManager.sharedInstance.connectVideoServer()
  */          

            var frameSettings = FrameManagerSessionSettings()
            frameSettings.settings = serverSettings
            frameSettings.host = host
            frameSettings.port = Int(port)
            frameSettings.stream = stream
            frameSettings.sps = sps
            frameSettings.pps = pps
            frameSettings.profileLevelId = profileLevelId

            self.frameManager = FrameManager()
            self.frameManager.sessionSettings = frameSettings
            self.frameManager.delegate = self
            self.frameManager.start()

        }else{
            
        }
    }

    func testVideo() {
        self.cameraManager.delegate = self
        cameraManager.startVideoTest()
    }

    override init() {
        self.cameraManager.cameraDevice = .back
        self.cameraManager.cameraOutputMode = .videoWithMic
    }
    
    func addPreviewLayerToView(_ view:UIView) {
        self.cameraManager.updateCameraQualityMode()
        _ = self.cameraManager.addPreviewLayerToView(view)
    }

    func update() {
        self.cameraManager.updateCameraQualityMode()
    }

    func stop() {
        record = false
        self.cameraManager.stopRecordingVideo()
        self.cameraManager.stopRecordingVideo({ (videoURL, error) -> Void in
            print("ERRORSTOPERROR!")
        })

//        ConnectionManager.sharedInstance.disconnectVideoServer()
        frameManager.stop()
        state = .stop(nil)
        self.delegate?.mobistreamManager(self, state: self.state)
    }

    func hasTorch() -> Bool {
        return cameraManager.hasTorch
    }
    
    func setBitrate(){
        
    }

    func setFramerate(){
        
    }

    func setResolution(){
        
    }

    func setVideoOrientation(_ orientation:AVCaptureVideoOrientation){
        self.cameraManager.videoOrientation = orientation
    }

    func videoOrientation() -> AVCaptureVideoOrientation {
        return self.cameraManager.videoOrientation
    }

    func setStreamMode(_ mode:StreamCameraOutputMode){
        self.cameraManager.cameraOutputMode = mode
    }

    func streamMode() -> StreamCameraOutputMode {
        return self.cameraManager.cameraOutputMode
    }

    func setCameraDevice(_ device:StreamCameraDevice){
        self.cameraManager.cameraDevice = device
    }
    
    func cameraDevice() -> StreamCameraDevice {
        return self.cameraManager.cameraDevice
    }
    
    func setTorchMode(_ mode:StreamCameraFlashMode){
        self.cameraManager.torchMode = mode
    }
    
    func torchMode() -> StreamCameraFlashMode {
        return self.cameraManager.torchMode
    }
}

extension MobistreamManager: FrameManagerDelegate {
    
    func startingAtFirstIDR() {
        delegate?.startingAtFirstIDR()
    }

    func bufferOverFlow() {
        delegate?.bufferOverFlow()
    }
    
    func frameManager(uploadSpeed: Double) {
        delegate?.mobistreamManager(self, speed: uploadSpeed)
    }
    
    func frameManager(registerCamera: Bool, error: Error?) {
        if registerCamera {
            record = true
            self.cameraManager.startRecordingVideo()
            self.delegate?.mobistreamManager(self, state: .run)
            self.frameManager.startLoop()
        }else{
            self.cameraManager.stopRecordingVideo({ (videoURL, error) -> Void in
                
            })
            self.delegate?.mobistreamManager(self, state: .stop(error as NSError?))
        }
    }
}

extension MobistreamManager: StreamCameraManagerDelegate {

    func streamCameraManager(_ sender: StreamCameraManager, test: StreamCameraManagerTestStatus) {
        delegate?.mobistreamManager(self, testStatus: test)
    }

    func connectionManager(_ sender: ConnectionManager, status: ConnectionManagerStatus) {
        switch status {
        case .connected:
            print("connectionManager connected")
        case .connecting:
            print("connectionManager connecting")
        case .disconnected(let t):
            self.delegate?.mobistreamManager(self, state: .stop(t))
            print("connectionManager disconnected")
        case .none:
            print("connectionManager none")
        case .registered:
            print("connectionManager registered")
        case .registering:
            print("connectionManager registering")
        }
    }

    func streamCameraManager(_ sender: StreamCameraManager, data: Data, pts: Double, cmtime:CMTime) {
        if record {
//          ConnectionManager.sharedInstance.writeVideo(data, pts: pts, cmtime: cmtime)
                let frame = FrameEntity()
//                frame.value = NSData(data: data) as Data
                frame.value = data
                frame.ts = pts
                frame.type = .video
//                frame.time = cmtime
                frameManager.push(frame)
        }
    }

    func streamCameraManager(_ sender: StreamCameraManager, audio: Data, pts: Double, cmtime:CMTime) {
        if record {
//          ConnectionManager.sharedInstance.writeAudio(audio, pts: pts, cmtime: cmtime)
                let frame = FrameEntity()
//                frame.value = NSData(data: audio) as Data
                frame.value = audio
                frame.ts = pts
                frame.type = .audio
                frame.time = Int((Float(cmtime.value) / Float(cmtime.timescale) ) * 1000)
                frameManager.push(frame)
        }
    }

    func streamCameraManager(_ sender: StreamCameraManager, status: StreamCameraManagerStatus) {
        
    }

    func streamCameraManager(_ sender: StreamCameraManager, sps: String, pps: String, profileLevelId: String) {
        self.sps = sps
        self.pps = pps
        self.profileLevelId = profileLevelId
    }
}
