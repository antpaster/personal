//
//  MobiCamera.swift
//  SwiftMobistream
//
//  Created by netris on 26.05.16.
//  Copyright © 2016 netris. All rights reserved.
//

import UIKit
import AVFoundation
import VideoToolbox

public enum MobiCameraState {
    case ready, accessDenied, noDeviceFound, notDetermined
}

public enum MobiCameraDevice {
    case front, back
}

public enum MobiCameraFlashMode: Int {
    case off, on, auto
}

public enum MobiCameraOutputMode {
    case stillImage, videoWithMic, videoOnly
}

public enum MobiCameraOutputQuality: Int {
    case low, medium, high
}

protocol MobiCameraDelegate : class{
    func mobiCamera(_ sender: MobiCamera, data:AnyObject?, error:NSError?)
}

class MobiCamera: NSObject, AVCaptureVideoDataOutputSampleBufferDelegate, AVCaptureAudioDataOutputSampleBufferDelegate {


    var delegate: MobiCameraDelegate?
    
    let session = AVCaptureSession()
    var videoOutput: AVCaptureVideoDataOutput = AVCaptureVideoDataOutput()
    var audioOutput: AVCaptureAudioDataOutput = AVCaptureAudioDataOutput()

    var currentCameraDevicePosition:AVCaptureDevice.Position = .back
    var currentCameraDevice:AVCaptureDevice?

    var cameraPreviewLayer: AVCaptureVideoPreviewLayer?
    var cameraPreviewView: UIView?

    var videoSupport:Bool = false
    var audioSupport:Bool = false

    var sessionQueue = DispatchQueue(label: "CameraSessionQueue", attributes: [])
    
    var videoOrientation:AVCaptureVideoOrientation {
        get{
            let previewLayerConnection : AVCaptureConnection = (self.cameraPreviewLayer?.connection)!
            return previewLayerConnection.videoOrientation
        }
        set(newOrientation){
            let previewLayerConnection : AVCaptureConnection = (self.cameraPreviewLayer?.connection)!
            if (previewLayerConnection.isVideoOrientationSupported){
                previewLayerConnection.videoOrientation = newOrientation
            }
        }
    }
    
    func updatePreviewSize() {
        self.cameraPreviewLayer?.frame = self.cameraPreviewView!.bounds
    }

    init(cameraPreviewView:UIView, videoSupport:Bool, audioSupport:Bool, cameraPosition:AVCaptureDevice.Position, delegate:MobiCameraDelegate) {
        super.init()
        
        self.delegate = delegate
        self.cameraPreviewView = cameraPreviewView
        self.videoSupport = videoSupport
        self.audioSupport = audioSupport
        self.currentCameraDevicePosition = cameraPosition

        self.authorize()
        self.loadVideo()
        self.startRunningCamera()

    }
    
    deinit{
        stopRunningCamera()
    }

    func startRunningCamera() {
        sessionQueue.async(execute: { () -> Void in
            self.session.startRunning()
        })
    }

    func stopRunningCamera() {
        sessionQueue.async(execute: { () -> Void in
            self.session.stopRunning()
        })
    }

    func loadVideo() {
        let availableCameraDevices = AVCaptureDevice.devices(for: AVMediaType.video)
        for device in availableCameraDevices {
            if device.position == currentCameraDevicePosition {
                self.currentCameraDevice = device
            }
        }
        ////
        do{
            let cameraInput: AVCaptureDeviceInput = try AVCaptureDeviceInput(device: self.currentCameraDevice!)
            
            self.session.beginConfiguration()
            
            if self.session.canAddInput(cameraInput){
                self.session.addInput(cameraInput)
            }
            
//            videoOutput.videoSettings = [(kCVPixelBufferPixelFormatTypeKey as NSString) : NSNumber(value: kCVPixelFormatType_420YpCbCr8BiPlanarFullRange as UInt32)]
            videoOutput.videoSettings = [((kCVPixelBufferPixelFormatTypeKey as NSString) as String) : NSNumber(value: kCVPixelFormatType_32BGRA as UInt32)]
            videoOutput.alwaysDiscardsLateVideoFrames = true
           
            if session.canAddOutput(self.videoOutput) {
                session.addOutput(self.videoOutput)
            }
            
            self.session.commitConfiguration()

            videoOutput.setSampleBufferDelegate(self, queue: DispatchQueue(label: "ru.netris.mobistream.samplebuffer", attributes: []))

            /////
            self.cameraPreviewLayer = AVCaptureVideoPreviewLayer(session: self.session)
            self.cameraPreviewLayer?.frame = self.cameraPreviewView!.bounds
            self.cameraPreviewView!.layer.addSublayer(self.cameraPreviewLayer!)
            /////
        } catch let error as NSError {
            print(error)
        }
        
        /////////
//        print(session.sessionPreset)
//        let supportedPresets = supportedPresetList(session)
//        for preset in supportedPresets {
//            print(nameByPreset(preset))
//        }
    }

    func authorize() {
        let authorizationStatus = AVCaptureDevice.authorizationStatus(for: AVMediaType.video)
        switch authorizationStatus {
        case .notDetermined:
            AVCaptureDevice.requestAccess(for: AVMediaType.video, completionHandler: {(granted:Bool) -> Void in
                if granted {
                    
                }else{
                    //self.dismissViewControllerAnimated(true, completion: nil)
                }
            })
        case .authorized:
            print("")
        case .denied:
            print("")
            //self.dismissViewControllerAnimated(true, completion: nil)
        default:
            print("")
        }
    }

    func captureOutput(_ captureOutput: AVCaptureOutput, didDrop sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        
        if  captureOutput == videoOutput {
            print("sampleBuffer Dropped video!")
        }else if  captureOutput == audioOutput {
            print("sampleBuffer Dropped audio!")
        }
    }

    func captureOutput(captureOutput: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        if  captureOutput == videoOutput {
       //     print("sampleBuffer Recieved Vidoe!")
        }else if  captureOutput == audioOutput {
         //   print("sampleBuffer Recieved Audio!")
        }
    }

    func switchCamera() {
        if self.currentCameraDevicePosition == .back {
           self.currentCameraDevicePosition = .front
        }else{
           self.currentCameraDevicePosition = .back
        }
        
        do {
            try currentCameraDevice?.lockForConfiguration()
            // locked successfully, go on with configuration
            
            
            
            self.currentCameraDevice?.unlockForConfiguration()
        }catch{
            // something went wrong, the device was probably already locked
        }
        
    }

    func getVideoQuality() -> String {
        return ""
    }

    func setVideoQuality(_ preset:String) {
        
    }
    
    func setTorchMode(_ torchMode: AVCaptureDevice.TorchMode, device: AVCaptureDevice) {
        if device.isTorchAvailable && device.isTorchModeSupported(torchMode) {
            do {
                try device.lockForConfiguration()
                device.torchMode = torchMode
                device.unlockForConfiguration()
            } catch let error as NSError {
                print("Could not lock device for configuration: \(error.debugDescription)")
            }
        }
    }
    
    func setFlashMode(_ flashMode: AVCaptureDevice.FlashMode, forDevice device: AVCaptureDevice) {
        if device.hasFlash && device.isFlashModeSupported(flashMode) {
            do {
                try device.lockForConfiguration()
                device.flashMode = flashMode
                device.unlockForConfiguration()
            } catch let error as NSError {
                print("Could not lock device for configuration: \(error.debugDescription)")
            }
        }
    }
    
    func switchTorch() {
//        if isSupportTorch() {
            if let device = self.currentCameraDevice {
                if device.torchMode == .on {
                    setTorchMode(.off)
                }else{
                    setTorchMode(.on)
                }
            }
 //       }
    }
    
    func switchFlash() {
        if isSupportFlash() {
            if let device = self.currentCameraDevice {
                if device.flashMode == .on {
                   setFlashMode(.off)
                }else{
                   setFlashMode(.on)
                }
            }
        }
    }

    func isSupportTorch() -> Bool {
        if let device = self.currentCameraDevice {
            return device.isTorchAvailable
        }
        return false
    }

    func isSupportFlash() -> Bool {
        if let device = self.currentCameraDevice {
            return device.hasFlash
        }
        return false
    }

    func setTorchMode(_ torchMode: AVCaptureDevice.TorchMode) {
        if let device = self.currentCameraDevice {
            setTorchMode(torchMode, device: device)
        }
    }

    func setFlashMode(_ flashMode: AVCaptureDevice.FlashMode) {
        if let device = self.currentCameraDevice {
            setFlashMode(flashMode, forDevice: device)
        }
//        if (self.currentCameraDevice!.hasFlash && self.currentCameraDevice!.isFlashModeSupported(flashMode)) {
//            do {
//                try currentCameraDevice?.lockForConfiguration()
//                // locked successfully, go on with configuration
//                self.currentCameraDevice?.flashMode = flashMode
//                self.currentCameraDevice?.unlockForConfiguration()
//            }catch{
//                // something went wrong, the device was probably already locked
//            }
//        }
    }

    func setFrameRate(_ rate:Int) {
        
    }

    func getFrameRate() -> Int {
        return 0
    }
    
    func getSupportedFrameRate() {
        
//        let supportedRanges = currentCameraDevice?.activeFormat.videoSupportedFrameRateRanges

//        print(supportedRanges)
        
//        CMTime frameDuration = CMTimeMake(1, 60);
//        NSArray *supportedFrameRateRanges = [device.activeFormat videoSupportedFrameRateRanges];
//        BOOL frameRateSupported = NO;
//        for (AVFrameRateRange *range in supportedFrameRateRanges) {
//            if (CMTIME_COMPARE_INLINE(frameDuration, >=, range.minFrameDuration) &&
//                CMTIME_COMPARE_INLINE(frameDuration, <=, range.maxFrameDuration)) {
//                frameRateSupported = YES;
//            }
//        }
//        
//        if (frameRateSupported && [device lockForConfiguration:&error]) {
//            [device setActiveVideoMaxFrameDuration:frameDuration];
//            [device setActiveVideoMinFrameDuration:frameDuration];
//            [device unlockForConfiguration];
//        }
    }

    func setBitRate(_ rate:Int) {
        
    }

    func getBitRate() -> Int {
        return 0
    }

    func getSupportedList() -> [String] {
        return supportedPresetList(self.session)
    }

    func supportedPresetList(_ session:AVCaptureSession) -> [String] {
        //        session.sessionPreset = AVCaptureSessionPresetPhoto
        //        session.sessionPreset = AVCaptureSessionPresetHigh
        //        session.sessionPreset = AVCaptureSessionPresetMedium
        //        session.sessionPreset = AVCaptureSessionPresetLow
        //        session.sessionPreset = AVCaptureSessionPreset352x288
        //        session.sessionPreset = AVCaptureSessionPreset640x480
        //        session.sessionPreset = AVCaptureSessionPreset1280x720
        //        session.sessionPreset = AVCaptureSessionPreset1920x1080
        //        session.sessionPreset = AVCaptureSessionPresetiFrame960x540
        //        session.sessionPreset = AVCaptureSessionPresetiFrame1280x720
        //        session.sessionPreset = AVCaptureSessionPresetInputPriority
        var list = [String]()
        if session.canSetSessionPreset(AVCaptureSession.Preset.photo) {
            list.append(AVCaptureSession.Preset.photo.rawValue)
        }
        if session.canSetSessionPreset(AVCaptureSession.Preset.high) {
            list.append(AVCaptureSession.Preset.high.rawValue)
        }
        if session.canSetSessionPreset(AVCaptureSession.Preset.medium) {
            list.append(AVCaptureSession.Preset.medium.rawValue)
        }
        if session.canSetSessionPreset(AVCaptureSession.Preset.low) {
            list.append(AVCaptureSession.Preset.low.rawValue)
        }
        if session.canSetSessionPreset(AVCaptureSession.Preset.cif352x288) {
            list.append(AVCaptureSession.Preset.cif352x288.rawValue)
        }
        if session.canSetSessionPreset(AVCaptureSession.Preset.vga640x480) {
            list.append(AVCaptureSession.Preset.vga640x480.rawValue)
        }
        if session.canSetSessionPreset(AVCaptureSession.Preset.hd1280x720) {
            list.append(AVCaptureSession.Preset.hd1280x720.rawValue)
        }
        if session.canSetSessionPreset(AVCaptureSession.Preset.hd1920x1080) {
            list.append(AVCaptureSession.Preset.hd1920x1080.rawValue)
        }
        if session.canSetSessionPreset(AVCaptureSession.Preset.iFrame960x540) {
            list.append(AVCaptureSession.Preset.iFrame960x540.rawValue)
        }
        if session.canSetSessionPreset(AVCaptureSession.Preset.iFrame1280x720) {
            list.append(AVCaptureSession.Preset.iFrame1280x720.rawValue)
        }
        if session.canSetSessionPreset(AVCaptureSession.Preset.inputPriority) {
            list.append(AVCaptureSession.Preset.inputPriority.rawValue)
        }
        return list
    }
    
    func nameByPreset(_ preset:String) -> String?{
        switch preset {
        case AVCaptureSession.Preset.photo.rawValue:
            return "Photo"
        case AVCaptureSession.Preset.high.rawValue:
            return "High"
        case AVCaptureSession.Preset.medium.rawValue:
            return "Medium"
        case AVCaptureSession.Preset.low.rawValue:
            return "Low"
        case AVCaptureSession.Preset.cif352x288.rawValue:
            return "352x288"
        case AVCaptureSession.Preset.vga640x480.rawValue:
            return "640x480"
        case AVCaptureSession.Preset.hd1280x720.rawValue:
            return "1280x720"
        case AVCaptureSession.Preset.hd1920x1080.rawValue:
            return "1920x1080"
        case AVCaptureSession.Preset.iFrame960x540.rawValue:
            return "960x540"
        case AVCaptureSession.Preset.iFrame1280x720.rawValue:
            return "1280x720"
        case AVCaptureSession.Preset.inputPriority.rawValue:
            return "InputPriority"
        default:
            print("")
        }
        return nil
    }

    func presetByName(_ preset:String) -> String?{
        switch preset {
        case "Photo":
            return AVCaptureSession.Preset.photo.rawValue
        case "High":
            return AVCaptureSession.Preset.high.rawValue
        case "Medium":
            return AVCaptureSession.Preset.medium.rawValue
        case "Low":
            return AVCaptureSession.Preset.low.rawValue
        case "352x288":
            return AVCaptureSession.Preset.cif352x288.rawValue
        case "640x480":
            return AVCaptureSession.Preset.vga640x480.rawValue
        case "1280x720":
            return AVCaptureSession.Preset.hd1280x720.rawValue
        case "1920x1080":
            return AVCaptureSession.Preset.hd1920x1080.rawValue
        case "960x540":
            return AVCaptureSession.Preset.iFrame960x540.rawValue
        case "1280x720":
            return AVCaptureSession.Preset.iFrame1280x720.rawValue
        case "InputPriority":
            return AVCaptureSession.Preset.inputPriority.rawValue
        default:
            print("")
        }
        return nil
    }
}
