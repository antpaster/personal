//
//  StreamCameraManager.swift
//  SwiftMobistream
//
//  Created by netris on 27.05.16.
//  Copyright © 2016 netris. All rights reserved.
//

import UIKit
import AVFoundation
import GLKit

public enum StreamCameraState {
    case ready, accessDenied, noDeviceFound, notDetermined
}

public enum StreamCameraDevice {
    case front, back
}

public enum StreamCameraFlashMode: Int {
    case off, on, auto
}

public enum StreamCameraOutputMode {
    case stillImage, videoWithMic, videoOnly, micOnly
}

public enum StreamCameraOutputQuality: Int {
    case low, medium, high
}

public enum StreamCameraManagerStatus {
    case ready, accessDenied, noDeviceFound, notDetermined
}

protocol StreamCameraManagerDelegate : class{
    func streamCameraManager(_ sender: StreamCameraManager, test:StreamCameraManagerTestStatus)
    func streamCameraManager(_ sender: StreamCameraManager, status:StreamCameraManagerStatus)
    func streamCameraManager(_ sender: StreamCameraManager, data:Data, pts: Double, cmtime:CMTime)
    func streamCameraManager(_ sender: StreamCameraManager, audio:Data, pts: Double, cmtime:CMTime)
    func streamCameraManager(_ sender: StreamCameraManager, sps:String, pps:String, profileLevelId:String)
}

public enum StreamCameraManagerTestStatus {
    case none
    case testing
    case tested
}

extension StreamCameraManager: AudioEncoderDelegate {
    func audioEncode(_ sender: AudioEncoder, data: Data, pts: Double, cmtime: CMTime) {
        if !testing {
            delegate?.streamCameraManager(self, audio: data, pts: pts, cmtime:cmtime)
        }
    }
}

extension StreamCameraManager: VideoEncoderDelegate {

    func videoEncode(_ sender: VideoEncoder, sps: Data, pps: Data) {

        if testing {
            self.sps = sps
            self.pps = pps
            stopVideoTest()

            self.spsString = sps.base64EncodedString(options: NSData.Base64EncodingOptions())
            self.ppsString = pps.base64EncodedString(options: NSData.Base64EncodingOptions())
            let myNSString = sps.base64EncodedString(options: NSData.Base64EncodingOptions()) as NSString
            let levelString = myNSString.substring(with: NSRange(location: 1, length: 3))
            self.profileLevelIdString = levelString.data(using: String.Encoding.utf8)?.hexadecimalString()
            delegate?.streamCameraManager(self, sps: self.spsString!, pps: self.ppsString!, profileLevelId: self.profileLevelIdString!)
            testing = false
        } else {
            
        }
    }

    func videoEncode(_ sender: VideoEncoder, data: NSMutableData, pts: Double, cmtime: CMTime) {
        if !testing {
            delegate?.streamCameraManager(self, data: data as Data, pts:pts, cmtime:cmtime)
        }
    }
}

extension StreamCameraManager: AVCaptureAudioDataOutputSampleBufferDelegate, AVCaptureVideoDataOutputSampleBufferDelegate {

    func captureOutput(_ captureOutput: AVCaptureOutput, didDrop sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        if captureOutput == videoOutput {
            VideoEncoder.sharedInstance.captureOutput(captureOutput, didDrop: sampleBuffer, from: connection)
        }else if  captureOutput == audioOutput {
            AudioEncoder.sharedInstance.captureOutput(captureOutput, didDropSampleBuffer: sampleBuffer, fromConnection: connection)
        }
    }

    func captureOutput(_ captureOutput: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        if  captureOutput == videoOutput {
            if isRecording || testing {
                autoreleasepool{
                    VideoEncoder.sharedInstance.captureOutput(captureOutput, didOutput: sampleBuffer, from: connection)
                }
            }
        }else if  captureOutput == audioOutput {
//            if isRecording && isAudioEnable {
            if isRecording {
                autoreleasepool{
                    AudioEncoder.sharedInstance.captureOutput(captureOutput, didOutput: sampleBuffer, from: connection)
                }
            }
        }
    }
}

extension StreamCameraManager: UIGestureRecognizerDelegate {
    func gestureRecognizerShouldBegin(_ gestureRecognizer: UIGestureRecognizer) -> Bool {
        if gestureRecognizer.isKind(of: UIPinchGestureRecognizer.self) {
            beginZoomScale = zoomScale;
        }else if gestureRecognizer.isKind(of: UITapGestureRecognizer.self) {
//            print("TAPPPPPP")
        }
        return true
    }
}

class StreamCameraManager: NSObject {
    
    var sps:Data?
    var pps:Data?
    var profileLevelId:Data?

    var spsString:String?
    var ppsString:String?
    var profileLevelIdString:String?

    var captureSession: AVCaptureSession?
    var showErrorsToUsers = false
    var showAccessPermissionPopupAutomatically = true

    var isRecording:Bool = false
    var isAudioEnable = false

    var delegate:StreamCameraManagerDelegate?

    var presetsList:[String:[Int]] = {
        var ss = [AVCaptureSession.Preset.cif352x288.rawValue:[352,288],
                  AVCaptureSession.Preset.medium.rawValue:[480,360],
                  AVCaptureSession.Preset.vga640x480.rawValue:[640,480],
                  AVCaptureSession.Preset.hd1280x720.rawValue:[1280,720],
                  AVCaptureSession.Preset.hd1920x1080.rawValue:[1920,1080],
                  AVCaptureSession.Preset.hd4K3840x2160.rawValue:[3840,2160]]
        return ss
    }()

    var bitratesList:[String:[Int]] = {
        var ss = [AVCaptureSession.Preset.cif352x288.rawValue:[140,280,560,700],
                  AVCaptureSession.Preset.medium.rawValue:[400,600, 800,1000],
                  AVCaptureSession.Preset.vga640x480.rawValue:[700,1500,2500,3500],
                  AVCaptureSession.Preset.hd1280x720.rawValue:[1000,2500,3750,5000],
                  AVCaptureSession.Preset.hd1920x1080.rawValue:[1300,3000,5000,6000],
                  AVCaptureSession.Preset.hd4K3840x2160.rawValue:[3000,5000,7000,9000]]
        return ss
    }()

    var frameRatesList:[Int] = {
        return [15,25,30]
    }()

    var supportedPresets:[String:[Int]] {
        get{
            var supported = [String:[Int]]()
            for it in presetsList {
                if self.captureSession?.canSetSessionPreset(AVCaptureSession.Preset(rawValue: it.0)) == true {
                    supported[it.0] = it.1
                }
            }
            return supported
        }
    }

    var showErrorBlock:(_ erTitle: String, _ erMessage: String) -> Void = { (erTitle: String, erMessage: String) -> Void in
//        var alertController = UIAlertController(title: erTitle, message: erMessage, preferredStyle: .Alert)
//        alertController.addAction(UIAlertAction(title: "OK", style: UIAlertActionStyle.Default, handler: { (alertAction) -> Void in  }))
//        if let topController = UIApplication.sharedApplication().keyWindow?.rootViewController {
//            topController.presentViewController(alertController, animated: true, completion:nil)
//        }
    }

    /// Property to determine if manager should follow device orientation. Default value is true.
    var shouldRespondToOrientationChanges = false {
        didSet {
            if shouldRespondToOrientationChanges {
                _startFollowingDeviceOrientation()
            } else {
                _stopFollowingDeviceOrientation()
            }
        }
    }

    var videoOrientation: AVCaptureVideoOrientation = .portrait {
        didSet {
            _orientationChanged()
        }
    }

    var cameraIsReady: Bool {
        get {
            return cameraIsSetup
        }
    }

    var hasFrontCamera: Bool = {
        let devices = AVCaptureDevice.devices(for: AVMediaType.video)
        for  device in devices  {
            let captureDevice = device 
            if (captureDevice.position == .front) {
                return true
            }
        }
        return false
    }()

    var hasFlash: Bool = {
        let devices = AVCaptureDevice.devices(for: AVMediaType.video)
        for  device in devices  {
            let captureDevice = device 
            if (captureDevice.position == .back) {
                return captureDevice.hasFlash
            }
        }
        return false
    }()

    var hasTorch: Bool {
        if cameraDevice == .front {
            return false
        }

        let devices = AVCaptureDevice.devices(for: AVMediaType.video)

        for  device in devices  {
            let captureDevice = device 
            if (captureDevice.position == .back) {
                return captureDevice.hasTorch
            }
        }
        return false
    }

    var cameraDevice = StreamCameraDevice.back {
        didSet {
            if cameraIsSetup {
                if cameraDevice != oldValue {
                    _updateCameraDevice(cameraDevice)
                    _setupMaxZoomScale()
                    _zoom(0)
                }
            }
        }
    }

    var flashMode = StreamCameraFlashMode.off {
        didSet {
            if cameraIsSetup {
                if flashMode != oldValue {
                    _updateFlasMode(flashMode)
                }
            }
        }
    }

    var torchMode = StreamCameraFlashMode.off {
        didSet {
            if cameraIsSetup {
                if torchMode != oldValue {
                    _updateTorch(torchMode)
                }
            }
        }
    }

    var cameraOutputQuality = StreamCameraOutputQuality.high {
        didSet {
            if cameraIsSetup {
                if cameraOutputQuality != oldValue {
                    _updateCameraQualityMode(cameraOutputQuality)
                }
            }
        }
    }

    var cameraOutputMode = StreamCameraOutputMode.videoWithMic {
        didSet {
            if cameraIsSetup {
                if cameraOutputMode != oldValue {
                    _setupOutputMode(cameraOutputMode, oldCameraOutputMode: oldValue)
                }
                _setupMaxZoomScale()
                _zoom(0)
            }
        }
    }

    fileprivate weak var embeddingView: UIView?
    fileprivate var videoCompletition: ((_ videoURL: URL?, _ error: NSError?) -> Void)?

    fileprivate var sessionQueue: DispatchQueue = DispatchQueue(label: "CameraSessionQueue", attributes: [])

    fileprivate lazy var frontCameraDevice: AVCaptureDevice? = {
        let devices = AVCaptureDevice.devices(for: AVMediaType.video) 
        return devices.filter{$0.position == .front}.first
    }()

    fileprivate lazy var backCameraDevice: AVCaptureDevice? = {
        let devices = AVCaptureDevice.devices(for: AVMediaType.video) 
        return devices.filter{$0.position == .back}.first
    }()

    fileprivate lazy var mic: AVCaptureDevice? = {
        return AVCaptureDevice.default(for: AVMediaType.audio)
    }()

    fileprivate var previewLayer: AVCaptureVideoPreviewLayer?

    fileprivate var cameraIsSetup = false
    fileprivate var cameraIsObservingDeviceOrientation = false

    fileprivate var zoomScale       = CGFloat(1.0)
    fileprivate var beginZoomScale  = CGFloat(1.0)
    fileprivate var maxZoomScale    = CGFloat(1.0)

    func addPreviewLayerToView(_ view: UIView) -> StreamCameraState {
        return addPreviewLayerToView(view, newCameraOutputMode: cameraOutputMode)
    }

    func addPreviewLayerToView(_ view: UIView, newCameraOutputMode: StreamCameraOutputMode) -> StreamCameraState {
        return addPreviewLayerToView(view, newCameraOutputMode: newCameraOutputMode, completition: nil)
    }

    func addPreviewLayerToView(_ view: UIView, newCameraOutputMode: StreamCameraOutputMode, completition: (() -> Void)?) -> StreamCameraState {
        if _canLoadCamera() {
            if let _ = embeddingView {
                if let validPreviewLayer = previewLayer {
                    validPreviewLayer.removeFromSuperlayer()
                }
            }
            if cameraIsSetup {
                _addPreviewLayerToView(view)
                cameraOutputMode = newCameraOutputMode
                if let validCompletition = completition {
                    validCompletition()
                }
            } else {
                _setupCamera({ () -> Void in
                    self._addPreviewLayerToView(view)
                    self.cameraOutputMode = newCameraOutputMode
                    if let validCompletition = completition {
                        validCompletition()
                    }
                })
            }
        }
        return _checkIfCameraIsAvailable()
    }

    func askUserForCameraPermissions(_ completition: @escaping (Bool) -> Void) {
        AVCaptureDevice.requestAccess(for: AVMediaType.video, completionHandler: { (alowedAccess) -> Void in
            if self.cameraOutputMode == .videoWithMic {
                AVCaptureDevice.requestAccess(for: AVMediaType.audio, completionHandler: { (alowedAccess) -> Void in
                    DispatchQueue.main.sync(execute: { () -> Void in
                        completition(alowedAccess)
                    })
                })
            } else {
                DispatchQueue.main.sync(execute: { () -> Void in
                    completition(alowedAccess)
                })
            }
        })
        
    }

    func stopCaptureSession() {
        captureSession?.stopRunning()
        _stopFollowingDeviceOrientation()
    }

    func resumeCaptureSession() {
        if let validCaptureSession = captureSession {
            if !validCaptureSession.isRunning && cameraIsSetup {
                validCaptureSession.startRunning()
                _startFollowingDeviceOrientation()
            }
        } else {
            if _canLoadCamera() {
                if cameraIsSetup {
                    stopAndRemoveCaptureSession()
                }
                _setupCamera({ () -> Void in
                    if let validEmbeddingView = self.embeddingView {
                        self._addPreviewLayerToView(validEmbeddingView)
                    }
                    self._startFollowingDeviceOrientation()
                })
            }
        }
    }

    func stopAndRemoveCaptureSession() {
        stopCaptureSession()
        cameraDevice = .back
        cameraIsSetup = false
        previewLayer = nil
        captureSession = nil
        frontCameraDevice = nil
        backCameraDevice = nil
        mic = nil
    }

    func startRecordingVideo() {
        updateSettings()
        VideoEncoder.sharedInstance.delegate = self
        AudioEncoder.sharedInstance.delegate = self

//        switch cameraOutputMode {
//        case .videoWithMic, .stillImage, .micOnly:
//            AudioEncoder.sharedInstance.mute(false)
//            print("MUTE FALSE")
//        case .videoOnly:
//            AudioEncoder.sharedInstance.mute(true)
//            print("MUTE TRUE")
//        }
        isRecording = true
    }

    func stopRecordingVideo(){
        self.isRecording = false
        DispatchQueue.main.async(execute: {
            self.isRecording = false
        })
    }

    func stopRecordingVideo(_ completition:(_ videoURL: URL?, _ error: NSError?) -> Void) {
        isRecording = false
        print("STOP!STOP!STOP!STOP!")
    }

    func currentCameraStatus() -> StreamCameraState {
        return _checkIfCameraIsAvailable()
    }

    func changeFlashMode() -> StreamCameraFlashMode {
        flashMode = StreamCameraFlashMode(rawValue: (flashMode.rawValue+1)%3)!
        return flashMode
    }

    func changeQualityMode() -> StreamCameraOutputQuality {
        cameraOutputQuality = StreamCameraOutputQuality(rawValue: (cameraOutputQuality.rawValue+1)%3)!
        return cameraOutputQuality
    }

    // MARK: - UIGestureRecognizerDelegate

    fileprivate func attachFocusTap(_ view: UIView) {
        let tap = UITapGestureRecognizer(target: self, action: #selector(StreamCameraManager._tap(_:)))
        view.addGestureRecognizer(tap)
        tap.delegate = self
    }
    
    fileprivate func attachZoom(_ view: UIView) {
        let pinch = UIPinchGestureRecognizer(target: self, action: #selector(StreamCameraManager._zoomStart(_:)))
        view.addGestureRecognizer(pinch)
        pinch.delegate = self
    }

    @objc
    fileprivate func _zoomStart(_ recognizer: UIPinchGestureRecognizer) {
        guard let view = embeddingView, let previewLayer = previewLayer else {
            return
        }

        var allTouchesOnPreviewLayer = true
        let numTouch = recognizer.numberOfTouches

        for i in 0 ..< numTouch {
            let location = recognizer.location(ofTouch: i, in: view)
            let convertedTouch = previewLayer.convert(location, from: previewLayer.superlayer)
            if !previewLayer.contains(convertedTouch) {
                allTouchesOnPreviewLayer = false
                break
            }
        }
        if allTouchesOnPreviewLayer {
            _zoom(recognizer.scale)
        }
    }
    
    @objc
    fileprivate func _tap(_ recognizer: UITapGestureRecognizer) {
        guard let view = embeddingView, let previewLayer = previewLayer else {
            return
        }

        let location = recognizer.location(ofTouch: 0, in: view)
        let focusPoint = previewLayer.convert(location, from: previewLayer.superlayer)
        if previewLayer.contains(focusPoint) {
            do {
                let captureDevice = AVCaptureDevice.devices().first
                try captureDevice?.lockForConfiguration()
                captureDevice?.focusPointOfInterest = focusPoint
                //device.focusMode = .continuousAutoFocus
                captureDevice?.focusMode = .autoFocus
                //device.focusMode = .locked
                captureDevice?.exposurePointOfInterest = focusPoint
                captureDevice?.exposureMode = AVCaptureDevice.ExposureMode.continuousAutoExposure
                captureDevice?.unlockForConfiguration()
            }catch {
                // just ignore
            }
        }
    }

    fileprivate func _zoom(_ scale: CGFloat) {
        do {
            let captureDevice = AVCaptureDevice.devices().first as? AVCaptureDevice
            try captureDevice?.lockForConfiguration()
            zoomScale = max(1.0, min(beginZoomScale * scale, maxZoomScale))
            captureDevice?.videoZoomFactor = zoomScale
            captureDevice?.unlockForConfiguration()
        } catch {
            print("Error locking configuration")
        }
    }
    
    // MARK: - CameraManager()
    
    fileprivate func _updateTorch(_ flashMode: StreamCameraFlashMode) {
        captureSession?.beginConfiguration()
        let devices = AVCaptureDevice.devices(for: AVMediaType.video)
        for  device in devices  {
            let captureDevice = device 
            if (captureDevice.position == AVCaptureDevice.Position.back) {
                let avTorchMode = AVCaptureDevice.TorchMode(rawValue: flashMode.rawValue)
                if (captureDevice.isTorchModeSupported(avTorchMode!)) {
                    do {
                        try captureDevice.lockForConfiguration()
                    } catch {
                        return;
                    }
                    captureDevice.torchMode = avTorchMode!
                    captureDevice.unlockForConfiguration()
                }
            }
        }
        captureSession?.commitConfiguration()
    }
    
    fileprivate func _executeVideoCompletitionWithURL(_ url: URL?, error: NSError?) {
        if let validCompletition = videoCompletition {
            validCompletition(url, error)
            videoCompletition = nil
        }
    }

    var videoOutput: AVCaptureVideoDataOutput?
    var audioOutput: AVCaptureAudioDataOutput?

    fileprivate func _getVideoOutput() -> AVCaptureVideoDataOutput {
        var shouldReinitializeMovieOutput = videoOutput == nil
        if !shouldReinitializeMovieOutput {
            if let connection = videoOutput!.connection(with: AVMediaType.video) {
                shouldReinitializeMovieOutput = shouldReinitializeMovieOutput || !connection.isActive
            }
        }

        if shouldReinitializeMovieOutput {
            videoOutput = AVCaptureVideoDataOutput()
            videoOutput!.videoSettings = [((kCVPixelBufferPixelFormatTypeKey as NSString) as String) : NSNumber(value: kCVPixelFormatType_32BGRA as UInt32)]
            videoOutput!.alwaysDiscardsLateVideoFrames = false
//            videoOutput!.setSampleBufferDelegate(VideoEncoder.sharedInstance, queue: dispatch_queue_create("ru.netris.mobistream.samplebuffer", DISPATCH_QUEUE_SERIAL))
//            videoOutput!.setSampleBufferDelegate(self, queue: DispatchQueue(label: "ru.netris.mobistream.video.samplebuffer", attributes: [.concurrent]))
            videoOutput!.setSampleBufferDelegate(self, queue: DispatchQueue.global(qos: .userInitiated))
        }
        return videoOutput!
    }

    fileprivate func _getAudioOutput() -> AVCaptureAudioDataOutput {
        var shouldReinitializeMovieOutput = audioOutput == nil
        if !shouldReinitializeMovieOutput {
            if let connection = audioOutput!.connection(with: AVMediaType.audio) {
                shouldReinitializeMovieOutput = shouldReinitializeMovieOutput || !connection.isActive
            }
        }
        if shouldReinitializeMovieOutput {
            audioOutput = AVCaptureAudioDataOutput()
//            audioOutput!.setSampleBufferDelegate(AudioEncoder.sharedInstance, queue: dispatch_queue_create("ru.netris.mobistream.samplebuffer", DISPATCH_QUEUE_SERIAL))
//            DispatchQueue(label: "", qos: .userInitiated, attributes: [.concurrent], autoreleaseFrequency: DispatchQueue.AutoreleaseFrequency.workItem, target: DispatchQueue?)

            audioOutput!.setSampleBufferDelegate(self, queue: DispatchQueue(label: "ru.netris.mobistream.samplebuffer", attributes: [.concurrent]))
        }
        return audioOutput!
    }

    @objc fileprivate func _orientationChanged() {

        return

        var currentConnection: AVCaptureConnection?;
        switch cameraOutputMode {
            case .stillImage:
                break
            case .videoOnly, .videoWithMic:
                currentConnection = _getVideoOutput().connection(with: AVMediaType.video)
                _getAudioOutput().connection(with: AVMediaType.audio)
            case .micOnly:
                currentConnection = _getAudioOutput().connection(with: AVMediaType.audio)
        }
        if let validPreviewLayer = previewLayer {
            if let validPreviewLayerConnection = validPreviewLayer.connection {
                if validPreviewLayerConnection.isVideoOrientationSupported {
                    validPreviewLayerConnection.videoOrientation = _currentVideoOrientation()
                }
            }
            if let validOutputLayerConnection = currentConnection {
                if validOutputLayerConnection.isVideoOrientationSupported {
                    validOutputLayerConnection.videoOrientation = _currentVideoOrientation()
                }
            }
            DispatchQueue.main.async(execute: { () -> Void in
                if let validEmbeddingView = self.embeddingView {
                    validPreviewLayer.frame = validEmbeddingView.bounds
                }
            })
        }
    }

    fileprivate func _currentVideoOrientation() -> AVCaptureVideoOrientation {
        return self.videoOrientation
    }

    fileprivate func _canLoadCamera() -> Bool {
        let currentCameraState = _checkIfCameraIsAvailable()
        return currentCameraState == .ready || (currentCameraState == .notDetermined && showAccessPermissionPopupAutomatically)
    }

    fileprivate func _setupCamera(_ completition: @escaping () -> Void) {
        captureSession = AVCaptureSession()

        let s = SettingsService().getVideoSize()

        sessionQueue.async(execute: {
            if let validCaptureSession = self.captureSession {
                validCaptureSession.beginConfiguration()

                switch s {
                case "352x288":
                    validCaptureSession.sessionPreset = AVCaptureSession.Preset.cif352x288
                case "640x480":
                    validCaptureSession.sessionPreset = AVCaptureSession.Preset.vga640x480
                case "1280x720":
                    validCaptureSession.sessionPreset = AVCaptureSession.Preset.hd1280x720
                default:
                    validCaptureSession.sessionPreset = AVCaptureSession.Preset.vga640x480
                }

                self._updateCameraDevice(self.cameraDevice)
                self._setupOutputs()
                self._setupOutputMode(self.cameraOutputMode, oldCameraOutputMode: nil)
                self._setupPreviewLayer()
                validCaptureSession.commitConfiguration()
                self._updateFlasMode(self.flashMode)
                self._updateCameraQualityMode(self.cameraOutputQuality)
                validCaptureSession.startRunning()
                self._startFollowingDeviceOrientation()
                self.cameraIsSetup = true
                self._orientationChanged()

                completition()
            }
        })
    }

    fileprivate func _startFollowingDeviceOrientation() {
        return
//        if shouldRespondToOrientationChanges && !cameraIsObservingDeviceOrientation {
//            NSNotificationCenter.defaultCenter().addObserver(self, selector:#selector(_orientationChanged), name: UIDeviceOrientationDidChangeNotification, object: nil)
//            cameraIsObservingDeviceOrientation = true
//        }
    }

    fileprivate func _stopFollowingDeviceOrientation() {
        return
//        if cameraIsObservingDeviceOrientation {
//            NSNotificationCenter.defaultCenter().removeObserver(self, name: UIDeviceOrientationDidChangeNotification, object: nil)
//            cameraIsObservingDeviceOrientation = false
//        }
    }

    fileprivate func _addPreviewLayerToView(_ view: UIView) {
        embeddingView = view
        attachZoom(view)
        attachFocusTap(view)
        DispatchQueue.main.async(execute: { () -> Void in
            guard let _ = self.previewLayer else {
                return
            }
            self.previewLayer!.frame = view.layer.bounds
            view.layer.addSublayer(self.previewLayer!)
        })
    }

    fileprivate func _setupMaxZoomScale() {
        var maxZoom = CGFloat(1.0)
        beginZoomScale = CGFloat(1.0)

        if cameraDevice == .back {
            maxZoom = (backCameraDevice?.activeFormat.videoMaxZoomFactor)!
        }
        else if cameraDevice == .front {
            maxZoom = (frontCameraDevice?.activeFormat.videoMaxZoomFactor)!
        }
        maxZoomScale = maxZoom
    }

    fileprivate func _checkIfCameraIsAvailable() -> StreamCameraState {
        let deviceHasCamera = UIImagePickerController.isCameraDeviceAvailable(UIImagePickerControllerCameraDevice.rear) || UIImagePickerController.isCameraDeviceAvailable(UIImagePickerControllerCameraDevice.front)
        if deviceHasCamera {
            let authorizationStatus = AVCaptureDevice.authorizationStatus(for: AVMediaType.video)
            let userAgreedToUseIt = authorizationStatus == .authorized
            if userAgreedToUseIt {
                return .ready
            } else if authorizationStatus == AVAuthorizationStatus.notDetermined {
                return .notDetermined
            } else {
                _show(NSLocalizedString("Camera access denied", comment:""), message:NSLocalizedString("You need to go to settings app and grant acces to the camera device to use it.", comment:""))
                return .accessDenied
            }
        } else {
            _show(NSLocalizedString("Camera unavailable", comment:""), message:NSLocalizedString("The device does not have a camera.", comment:""))
            return .noDeviceFound
        }
    }

    fileprivate func _setupOutputMode(_ newCameraOutputMode: StreamCameraOutputMode, oldCameraOutputMode: StreamCameraOutputMode?) {
        captureSession?.beginConfiguration()
        
        if let _ = oldCameraOutputMode {
            if let validMovieOutput = videoOutput {
                captureSession?.removeOutput(validMovieOutput)
            }
            if let validMicOutput = audioOutput {
                captureSession?.removeOutput(validMicOutput)
            }
            _removeMicInput()
        }

        captureSession?.addOutput(_getVideoOutput())

        let aOutput = _getAudioOutput()
        if let contains = captureSession?.outputs.contains(aOutput), !contains {
            captureSession?.addOutput(aOutput)
        }

        if let validMic = _deviceInputFromDevice(mic) {
            if let contains = captureSession?.inputs.contains(validMic), !contains {
                captureSession?.addInput(validMic)
            }
        }
        captureSession?.commitConfiguration()
        _updateCameraQualityMode(cameraOutputQuality)
        _orientationChanged()
    }
    
    
//    fileprivate func _setupOutputMode(_ newCameraOutputMode: StreamCameraOutputMode, oldCameraOutputMode: StreamCameraOutputMode?) {
//        captureSession?.beginConfiguration()
//
//        if let cameraOutputToRemove = oldCameraOutputMode {
//            switch cameraOutputToRemove {
//                case .stillImage:
//                    break
////                case .videoOnly, .videoWithMic:
//                case .videoOnly, .videoWithMic, .micOnly:
//                    if let validMovieOutput = videoOutput {
//                        captureSession?.removeOutput(validMovieOutput)
//                    }
//
//                    if let validMicOutput = audioOutput {
//                        captureSession?.removeOutput(validMicOutput)
//                    }
////                    if cameraOutputToRemove == .videoWithMic {
//                    if cameraOutputToRemove == .videoWithMic || cameraOutputToRemove == .videoOnly {
//                        _removeMicInput()
//                    }
////                case .micOnly:
////                    _removeMicInput()
//            }
//        }
//
//        switch newCameraOutputMode {
//            case .stillImage:
//                break
////            case .videoOnly, .videoWithMic:
//            case .videoOnly, .videoWithMic, .micOnly:
//                captureSession?.addOutput(_getVideoOutput())
////                if newCameraOutputMode == .videoWithMic {
//                    if let validMic = _deviceInputFromDevice(mic) {
//                        if let contains = captureSession?.inputs.contains(validMic), !contains {
//                            captureSession?.addInput(validMic)
//                        }
//                    }
////                }
//
//                let aOutput = _getAudioOutput()
//                if let contains = captureSession?.outputs.contains(aOutput), !contains {
//                    captureSession?.addOutput(aOutput)
//                }
////            case .micOnly:
////                if let validMic = _deviceInputFromDevice(mic) {
////                    captureSession?.addInput(validMic)
////                }
////                captureSession?.addOutput(_getAudioOutput())
//        }
//        captureSession?.commitConfiguration()
//        _updateCameraQualityMode(cameraOutputQuality)
//        _orientationChanged()
//    }

    fileprivate func _setupOutputs() {
        if (videoOutput == nil) {
            videoOutput = AVCaptureVideoDataOutput()
            if let videoOutput = videoOutput {
                videoOutput.videoSettings = [((kCVPixelBufferPixelFormatTypeKey as NSString) as String) : NSNumber(value: kCVPixelFormatType_32BGRA as UInt32)]
                videoOutput.alwaysDiscardsLateVideoFrames = false
                videoOutput.setSampleBufferDelegate(self, queue: DispatchQueue(label: "ru.netris.mobistream.video.samplebuffer", attributes: [.concurrent]))
            }
        }
    }

    fileprivate func _setupPreviewLayer() {
        if let validCaptureSession = captureSession {
            previewLayer = AVCaptureVideoPreviewLayer(session: validCaptureSession)
        }
    }

    fileprivate func _updateCameraDevice(_ deviceType: StreamCameraDevice) {
        if let validCaptureSession = captureSession {
            validCaptureSession.beginConfiguration()
            let inputs = validCaptureSession.inputs 

            for input in inputs {
                if let deviceInput = input as? AVCaptureDeviceInput {
                    if deviceInput.device == backCameraDevice && cameraDevice == .front {
                        validCaptureSession.removeInput(deviceInput)
                        break;
                    } else if deviceInput.device == frontCameraDevice && cameraDevice == .back {
                        validCaptureSession.removeInput(deviceInput)
                        break;
                    }
                }
            }
            switch cameraDevice {
                case .front:
                    if hasFrontCamera {
                        if let validFrontDevice = _deviceInputFromDevice(frontCameraDevice) {
                            if !inputs.contains(validFrontDevice) {
                                validCaptureSession.addInput(validFrontDevice)
                                VideoEncoder.isFrontCamera = true
                            }
                        }
                    }
                case .back:
                    if let validBackDevice = _deviceInputFromDevice(backCameraDevice) {
                        if !inputs.contains(validBackDevice) {
                            validCaptureSession.addInput(validBackDevice)
                            VideoEncoder.isFrontCamera = false
                        }
                    }
            }
            validCaptureSession.commitConfiguration()
        }
    }

    fileprivate func _updateFlasMode(_ flashMode: StreamCameraFlashMode) {
        captureSession?.beginConfiguration()
        let devices = AVCaptureDevice.devices(for: AVMediaType.video)
        for  device in devices  {
            let captureDevice = device 
            if (captureDevice.position == AVCaptureDevice.Position.back) {
                let avFlashMode = AVCaptureDevice.FlashMode(rawValue: flashMode.rawValue)
                if (captureDevice.isFlashModeSupported(avFlashMode!)) {
                    do {
                        try captureDevice.lockForConfiguration()
                    } catch {
                        return
                    }
                    captureDevice.flashMode = avFlashMode!
                    captureDevice.unlockForConfiguration()
                }
            }
        }
        captureSession?.commitConfiguration()
    }

    func updateCameraQualityMode() {
        self._updateCameraQualityMode(self.cameraOutputQuality)
    }

    fileprivate func _updateCameraQualityMode(_ newCameraOutputQuality: StreamCameraOutputQuality) {       
        if let validCaptureSession = captureSession {
            var sessionPreset = AVCaptureSession.Preset.low
            let serverSettings = SettingsService()
            let s = serverSettings.getVideoSize()
            switch s {
            case "352x288":
                sessionPreset = AVCaptureSession.Preset.cif352x288
            case "640x480":
                sessionPreset = AVCaptureSession.Preset.vga640x480
            case "1280x720":
                sessionPreset = AVCaptureSession.Preset.hd1280x720
            default:
                sessionPreset = AVCaptureSession.Preset.vga640x480
            }

            if validCaptureSession.canSetSessionPreset(sessionPreset) {
                validCaptureSession.beginConfiguration()
                validCaptureSession.sessionPreset = sessionPreset
                validCaptureSession.commitConfiguration()
            } else {
                _show(NSLocalizedString("Preset not supported", comment:""), message: NSLocalizedString("Camera preset not supported. Please try another one.", comment:""))
            }
        } else {
            _show(NSLocalizedString("Camera error", comment:""), message: NSLocalizedString("No valid capture session found, I can't take any pictures or videos.", comment:""))
        }
    }

    fileprivate func _removeMicInput() {
        guard let inputs = captureSession?.inputs as? [AVCaptureInput] else { return }

        for input in inputs {
            if let deviceInput = input as? AVCaptureDeviceInput {
                if deviceInput.device == mic {
                    captureSession?.removeInput(deviceInput)
                    break;
                }
            }
        }
    }

    fileprivate func _show(_ title: String, message: String) {
        if showErrorsToUsers {
            DispatchQueue.main.async(execute: { () -> Void in
                self.showErrorBlock(title, message)
            })
        }
    }

    fileprivate func _deviceInputFromDevice(_ device: AVCaptureDevice?) -> AVCaptureDeviceInput? {
        guard let validDevice = device else { return nil }
        do {
            return try AVCaptureDeviceInput(device: validDevice)
        } catch let outError {
            _show(NSLocalizedString("Device setup error occured", comment:""), message: "\(outError)")
            return nil
        }
    }

    fileprivate var testing:Bool = false

    func startVideoTest() {
        VideoEncoder.sharedInstance.delegate = self
        AudioEncoder.sharedInstance.delegate = self
        delegate?.streamCameraManager(self, test: .testing)
        DispatchQueue(label: "ru.netris.mobistream.test", attributes: []).async(execute: { () in
            self.testing = true
        })
    }

    func stopVideoTest() {
        DispatchQueue(label: "ru.netris.mobistream.test", attributes: []).async(execute: { () in
            self.delegate?.streamCameraManager(self, test: .tested)
            self.testing = false
        })
    }

    func updateSettings() {
        if SettingsService().getStreamMode() > 0 {
            isAudioEnable = true
        }else{
            isAudioEnable = true
        }
    }

    deinit {
        stopAndRemoveCaptureSession()
        _stopFollowingDeviceOrientation()
    }
}

extension Data {
    func hexadecimalString() -> String {
        var string = ""
        var byte: UInt8 = 0

        for i in 0 ..< count {
//            var range: Range<String.Index> = Range<String.Index>(start: i,end: i+1)
            copyBytes(to: &byte, from: i..<i+1)//NSMakeRange(i, 1)
            string += String(format: "%02x", byte)
        }
        return string
    }
}
