//
//  VideoEncoder.swift
//  SwiftMobistream
//
//  Created by netris on 31.05.16.
//  Copyright © 2016 netris. All rights reserved.
//

import UIKit
import VideoToolbox
import AVFoundation
import OpenGLES
import CoreImage
import GLKit.GLKMathUtils
import QuartzCore

protocol VideoEncoderDelegate : class{
    func videoEncode(_ sender: VideoEncoder, data:NSMutableData, pts:Double, cmtime:CMTime)
    func videoEncode(_ sender: VideoEncoder, sps:Data, pps:Data)
}

class VideoEncoder: NSObject, AVCaptureVideoDataOutputSampleBufferDelegate {
    
    static let sharedInstance = VideoEncoder()
    var delegate: VideoEncoderDelegate?
    fileprivate var encodeSession: VTCompressionSession?
    fileprivate var formatDescription: CMFormatDescription!
    static var previewView: UIView?

    var serverSettings:ServerSettingsEntity = ServerSettingsEntity()

    var gpsSemaphore = DispatchSemaphore(value: 1)

    var locationString:String = ""

    func setLocationTitle(_ string:String) {
        gpsSemaphore.wait()
        locationString = string
        gpsSemaphore.signal()
    }

    func getLocationTitle() -> String {
        gpsSemaphore.wait()
        let str = locationString
        gpsSemaphore.signal()
        return str
    }

    var sps:String?
    var pps:String?

    var testProcess = false
    
    static var isFrontCamera = false
    
    var orientation:Int32 = 0

    fileprivate let defaultAttributes: [NSString: AnyObject] = [
        kCVPixelBufferPixelFormatTypeKey: Int(kCVPixelFormatType_32BGRA) as AnyObject,
        
        kCVPixelBufferOpenGLESCompatibilityKey: true as AnyObject]//kCVPixelBufferIOSurfacePropertiesKey: [:],
    
    fileprivate var videoTimeStamp = kCMTimeZero

    fileprivate var attributes: [NSString: AnyObject] {
        var attrs: [NSString: AnyObject] = defaultAttributes
        attrs[kCVPixelBufferWidthKey] = NSNumber(value: width as Int32)
        attrs[kCVPixelBufferHeightKey] = NSNumber(value: height as Int32)
        return attrs
    }

    var scale:Double = 720 / 1280
    var width = Int32(1280)
    var height = Int32(720)
    var profileLevel:CFString = kVTProfileLevel_H264_Main_AutoLevel

    var averageBitRate:CFNumber = (1024 * 1024 * 0.5) as CFNumber {
        didSet{
            if Int(averageBitRate) != Int(oldValue) {
                setProperty(kVTCompressionPropertyKey_AverageBitRate, propertyValue: averageBitRate)
            }
        }
    }

    var maxKeyFrameInterval:CFNumber = 30 as CFNumber {
        didSet{
            if Int(maxKeyFrameInterval) != Int(oldValue) {
                setProperty(kVTCompressionPropertyKey_MaxKeyFrameInterval, propertyValue: maxKeyFrameInterval)
            }
        }
    }

    var expectedFrameRate:CFNumber = 30 as CFNumber {
        didSet{
            if Int(expectedFrameRate) != Int(oldValue) {
                setProperty(kVTCompressionPropertyKey_ExpectedFrameRate, propertyValue: expectedFrameRate)
            }
        }
    }

    func setProperty(_ propertyKey:CFString, propertyValue:AnyObject) {
        if let encodeSession = encodeSession {
            VTSessionSetProperty(encodeSession, propertyKey, propertyValue)
        }
    }

    var isVideoEnable = false

    func updateSettings() {
        if SettingsService().getStreamMode() < 0 {
            isVideoEnable = true
        }else{
            isVideoEnable = false
        }
    }

    var streamMode = SettingsService().getStreamMode()
    var logoImage:CIImage = CIImage(image: UIImage(named: "video_off_icon")!)!
    static var titleText:String = "Mobistream"//SettingsService().getTitleText()
    var textSize = 30

    func reloadEncoder() {
        self.sps = nil
        self.pps = nil
        self.configCompressionSession()
    }
    
    func loadSettings() {
        bg = nil
        novideobg = nil
        updateSettings()
        let settings = SettingsService()
//        self.averageBitRate = Settings.sharedInstance.getBitrate() as CFNumber
        self.expectedFrameRate = settings.getFramerate() as CFNumber
        self.streamMode = settings.getStreamMode()
        let videosize = settings.getVideoSize()

        switch videosize {
        case "352x288":
            self.scale = 288 / 352
            self.width = Int32(352)
            self.height = Int32(288)

            self.textSize = 7

            switch settings.getBitrate() {
            case 0:
                self.averageBitRate = (1024 * 1024 * 0.140) as CFNumber
            case 1:
                self.averageBitRate = (1024 * 1024 * 0.280) as CFNumber
            case 2:
                self.averageBitRate = (1024 * 1024 * 0.56) as CFNumber
            case 3:
                self.averageBitRate = (1024 * 1024 * 0.7) as CFNumber
            default:
                break;
            }
        case "640x480":
            self.scale = 480 / 640
            self.width = Int32(640)
            self.height = Int32(480)
            
            self.textSize = 11
            
            switch settings.getBitrate() {
            case 0:
                self.averageBitRate = (1024 * 1024 * 0.7) as CFNumber
            case 1:
                self.averageBitRate = (1024 * 1024 * 1.0) as CFNumber
            case 2:
                self.averageBitRate = (1024 * 1024 * 1.7) as CFNumber
            case 3:
                self.averageBitRate = (1024 * 1024 * 2.0) as CFNumber
            default:
                break;
            }
        case "960x540":
            self.scale = 540 / 960
            self.width = Int32(960)
            self.height = Int32(540)
            
            self.textSize = 20
            
        case "1280x720":
            self.scale = 720 / 1280
            self.width = Int32(1280)
            self.height = Int32(720)

            self.textSize = 15
            
            switch settings.getBitrate() {
            case 0:
                self.averageBitRate = (1024 * 1024 * 1.0) as CFNumber
            case 1:
                self.averageBitRate = (1024 * 1024 * 1.5) as CFNumber
            case 2:
                self.averageBitRate = (1024 * 1024 * 2.0) as CFNumber
            case 3:
                self.averageBitRate = (1024 * 1024 * 3.5) as CFNumber
            default:
                break;
            }
        default:
            break
        }
//        self.titleText = settings.getTitleText()
    }

    fileprivate func configCompressionSession(_ width:Int32, height:Int32, avarageBitRate:CFNumber, keyFrameInterval:CFNumber, frameRate:CFNumber) {

        invalidateCompressionSession()

        self.width = width
        self.height = height
        self.averageBitRate = avarageBitRate
        self.maxKeyFrameInterval = keyFrameInterval
        self.expectedFrameRate = frameRate
        
        if encodeSession != nil {
            VTCompressionSessionInvalidate(encodeSession!)
            encodeSession = nil
        }

        let _: OSStatus = VTCompressionSessionCreate(kCFAllocatorDefault,
                                                            width,
                                                            height,
                                                            kCMVideoCodecType_H264,
                                                            nil,
                                                            attributes as CFDictionary?,
                                                            nil,
                                                            callback,
                                                            unsafeBitCast(self, to: UnsafeMutableRawPointer.self),
                                                            &encodeSession)
        
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_MaxKeyFrameInterval, keyFrameInterval)
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_AverageBitRate, avarageBitRate)
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_ProfileLevel, kVTProfileLevel_H264_Main_AutoLevel)
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_ExpectedFrameRate, frameRate)
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_RealTime, kCFBooleanTrue);
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_H264EntropyMode, kVTH264EntropyMode_CABAC);
    }

    func configCompressionSession() {
        loadSettings()
        invalidateCompressionSession()

        let status: OSStatus = VTCompressionSessionCreate(kCFAllocatorDefault,
                                                          width,
                                                          height,
                                                          kCMVideoCodecType_H264,
                                                          nil,
                                                          attributes as CFDictionary?,
                                                          nil,
                                                          callback,
                                                          unsafeBitCast(self, to: UnsafeMutableRawPointer.self),
                                                          &encodeSession)

        guard encodeSession != nil else {
            print("encode session is nil: \(status)")
            DispatchQueue.main.async {
                self.configCompressionSession()
            }
            return
        }

    //    VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_H264EntropyMode, kVTH264EntropyMode_CABAC);
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_MaxKeyFrameInterval, self.maxKeyFrameInterval)
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_AverageBitRate, self.averageBitRate)
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_ProfileLevel, self.profileLevel)
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_ExpectedFrameRate, self.expectedFrameRate)
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_RealTime, kCFBooleanTrue);
        VTSessionSetProperty(encodeSession!, kVTCompressionPropertyKey_AllowFrameReordering, kCFBooleanFalse);
    }

    deinit {
        invalidateCompressionSession()
    }

    func invalidateCompressionSession() {
        if nil != encodeSession {
            VTCompressionSessionInvalidate(encodeSession!)
            encodeSession = nil
            sps = nil
            pps = nil
//            configCompressionSession()
        }
    }

    fileprivate var callback:VTCompressionOutputCallback = {(
        outputCallbackRefCon:UnsafeMutableRawPointer?,
        sourceFrameRefCon:UnsafeMutableRawPointer?,
        status:OSStatus,
        infoFlags:VTEncodeInfoFlags,
        sampleBuffer:CMSampleBuffer?) in
        guard let sampleBuffer:CMSampleBuffer = sampleBuffer , status == noErr else {
            return
        }
        let encoder:VideoEncoder = unsafeBitCast(outputCallbackRefCon, to: VideoEncoder.self)
        encoder.formatDescription = CMSampleBufferGetFormatDescription(sampleBuffer)
        encoder.handleEncodedSampleBuffer(sampleBuffer)

//      encoder.delegate?.sampleOutput(video: sampleBuffer)
    }

    fileprivate func handleEncodedSampleBuffer(_ sampleBuffer: CMSampleBuffer) {
        let keyFrame = sampleBuffer.isKeyFrame
        guard keyFrame != nil else { return }
        if keyFrame! {
            let sps = get_sps_or_pps(by: true, sampleBuffer: sampleBuffer)
            let pps = get_sps_or_pps(by: false, sampleBuffer: sampleBuffer)
            delegate?.videoEncode(self, sps: sps!, pps: pps!)
            let pts = CMSampleBufferGetPresentationTimeStamp(sampleBuffer)
            delegate?.videoEncode(self, data: NSMutableData(data: sps!), pts: CMTimeGetSeconds(pts), cmtime:pts);
            delegate?.videoEncode(self, data: NSMutableData(data: pps!), pts: CMTimeGetSeconds(pts), cmtime:pts);
        }
        getEncodedData(sampleBuffer, iframe: keyFrame!)
    }

    // choice: true means sps. false means pps
    fileprivate func get_sps_or_pps(by choice: Bool, sampleBuffer: CMSampleBuffer) -> Data! {

        let format = CMSampleBufferGetFormatDescription(sampleBuffer)
        guard format != nil else { return nil }
        var paramSetPtr: UnsafePointer<UInt8>? = nil

        var paraSetSize = Int()
        var paraSetCount = Int()
        var naluHeadLen = Int32()
        var paraSetIndex = Int()
        if choice {
            paraSetIndex = 0
        } else {
            paraSetIndex = 1
        }

        let status = CMVideoFormatDescriptionGetH264ParameterSetAtIndex(format!, paraSetIndex, &paramSetPtr, &paraSetSize, &paraSetCount, &naluHeadLen)

        if status == noErr {
            // choice: true means sps. false means pps
            let paraData = Data(bytes: UnsafePointer<UInt8>(paramSetPtr!), count: paraSetSize)
            return paraData
        } else {
            print("CMVideoFormatDescriptionGetH264ParameterSetAtIndex error:\(status)")
            return nil
        }
    }

    fileprivate func getEncodedData(_ sampleBuffer: CMSampleBuffer, iframe:Bool) -> Data! {

        let blockBuffer = CMSampleBufferGetDataBuffer(sampleBuffer)
        guard blockBuffer != nil else { return nil }

        var totalLen = Int()
        var dataPointer: UnsafeMutablePointer<Int8>? = nil

        let status = CMBlockBufferGetDataPointer(blockBuffer!, 0, nil, &totalLen, &dataPointer)

        if status == noErr {
            var cto = Int32(0)
            let pts = CMSampleBufferGetPresentationTimeStamp(sampleBuffer)
            var dts = CMSampleBufferGetDecodeTimeStamp(sampleBuffer)

            if dts == kCMTimeInvalid {
                dts = pts
            } else {
                cto = Int32(CMTimeGetSeconds(pts) - CMTimeGetSeconds(dts)*1000)
            }

            let dis = CMTimeGetSeconds(dts) - CMTimeGetSeconds(videoTimeStamp)
            let delta = (videoTimeStamp == kCMTimeZero ? 0 : dis) * 1000

            guard sampleBuffer.isKeyFrame != nil else { return nil }

            var bufferOffset:size_t = 0
            let AVCCHeaderLength = 4;
            while bufferOffset < totalLen - AVCCHeaderLength {
                var NALUnitLength:UInt32 = 0;
                memcpy(&NALUnitLength, dataPointer! + bufferOffset, AVCCHeaderLength)
                NALUnitLength = CFSwapInt32BigToHost(NALUnitLength);
                let s:Int = Int(NALUnitLength)
                let data:Data = Data(bytes: UnsafeRawPointer(dataPointer! + bufferOffset + AVCCHeaderLength + 0), count: s - 0)
                bufferOffset = bufferOffset + AVCCHeaderLength + Int(NALUnitLength)
                delegate?.videoEncode(self, data: (data as NSData).mutableCopy() as! NSMutableData, pts: CMTimeGetSeconds(pts), cmtime:pts);
            }
            videoTimeStamp = dts
        } else {
            return nil
        }
        return nil
    }

    // CVPixelBuffer == CVImageBuffer == CVBuffer
    func encode(imageBuffer: CVImageBuffer,
                            presentationTimeStamp: CMTime,
                            presentationDuration: CMTime) {

        var flags: VTEncodeInfoFlags = VTEncodeInfoFlags()
        if encodeSession != nil {
            VTCompressionSessionEncodeFrame(encodeSession!,
                                            imageBuffer,
                                            presentationTimeStamp,
                                            presentationDuration,
                                            nil,
                                            nil,
                                            &flags)
        }
    }

    var eaglContext:EAGLContext?
    var ciContext:CIContext?

    fileprivate override init() {
        super.init()
        configCompressionSession()
        eaglContext = EAGLContext(api:EAGLRenderingAPI.openGLES2)
        ciContext = CIContext(eaglContext: eaglContext!, options: [kCIContextWorkingColorSpace : NSNull()])
    }

    func captureOutput(_ captureOutput: AVCaptureOutput, didDrop sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        print("sampleBuffer Dropped video!")
    }

    func captureOutput(_ captureOutput: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        DispatchQueue.global(qos: .userInteractive).async { //.default  .userInitiated
            autoreleasepool {
                let imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer)
                guard imageBuffer != nil else { return }
                let timeStamp = CMSampleBufferGetPresentationTimeStamp(sampleBuffer)
                let duration = CMSampleBufferGetDuration(sampleBuffer)
                let asd = self.processingSampleBuffer(sampleBuffer)
                self.encode(imageBuffer: asd, presentationTimeStamp: timeStamp, presentationDuration: duration)

            }
        }
    }

    func mirror(_ inputImage:CIImage) -> CIImage {
        let o:CGPoint = inputImage.extent.origin
        let inputWidth:CGFloat = inputImage.extent.size.width
        let to:CGAffineTransform = CGAffineTransform(translationX: -o.x, y: -o.y)
        let result:CIImage = inputImage.transformed(by: to)
        let from:CGAffineTransform = CGAffineTransform(translationX: o.x, y: o.y)
        return result.transformed(by: from)
    }
    
    func addTimeToImage(_ image:CIImage, fontSize: Int) -> CIImage? {
        let date = Date()
        let dayTimePeriodFormatter = DateFormatter()
        dayTimePeriodFormatter.dateFormat = "dd.MM.YYYY HH:mm:ss"
        let string:NSString = NSString(string:VideoEncoder.titleText + " " + dayTimePeriodFormatter.string(from: date))
        let attributes:[NSAttributedStringKey:AnyObject] = [
                        NSAttributedStringKey.font:UIFont(name: "PFDinTextCompPro-Regular", size: CGFloat(fontSize))!,
                        NSAttributedStringKey.foregroundColor : UIColor.white,
                        NSAttributedStringKey.backgroundColor : UIColor.black]
        let width = widthOfString(string, fontName: "PFDinTextCompPro-Regular", fontSize: CGFloat(fontSize))
        let height = heightOfString(string, fontName: "PFDinTextCompPro-Regular", fontSize: CGFloat(fontSize))

        let textImage:UIImage = imageFromString(string, attributes:attributes, size:CGSize(width: width, height: height))
        let ciText:CIImage = CIImage(image: textImage)!

        let transformFilter = CIFilter(name: "CIAffineTransform")
        transformFilter!.setValue(ciText, forKey: "inputImage")
        transformFilter!.setValue(NSValue(cgAffineTransform: CGAffineTransform(translationX: 0, y: image.extent.height - ciText.extent.height)), forKey: "inputTransform")

        let filterm = CIFilter(name:"CISourceOverCompositing")
        filterm!.setValue(transformFilter!.outputImage!, forKey: "inputImage")
        filterm!.setValue(image, forKey: "inputBackgroundImage")
        let outImage = filterm!.outputImage
        return outImage
    }
    
    func addLocationToImage(_ image:CIImage, fontSize: Int) -> CIImage? {
        let locationString = getLocationTitle()
        guard locationString != "" else {
            return image
        }

        let string:NSString = NSString(string:locationString)
        let attributes:[NSAttributedStringKey:AnyObject] = [
            NSAttributedStringKey.font:UIFont(name: "PFDinTextCompPro-Regular", size: CGFloat(fontSize))!,
            NSAttributedStringKey.foregroundColor : UIColor.white,
            NSAttributedStringKey.backgroundColor : UIColor.black]
        let width = widthOfString(string, fontName: "PFDinTextCompPro-Regular", fontSize: CGFloat(fontSize))
        let height = heightOfString(string, fontName: "PFDinTextCompPro-Regular", fontSize: CGFloat(fontSize))
        
        let textImage:UIImage = imageFromString(string, attributes:attributes, size:CGSize(width: width, height: height))
        let ciText:CIImage = CIImage(image: textImage)!

        let filterm = CIFilter(name:"CISourceOverCompositing")
        filterm!.setValue(ciText, forKey: "inputImage")
        filterm!.setValue(image, forKey: "inputBackgroundImage")
        let outImage = filterm!.outputImage
        return outImage
    }

    func imageOverComposition(_ backgroundImage:CIImage, foregroundImage:CIImage) -> CIImage? {
        let transformFilter = CIFilter(name: "CIAffineTransform")
        transformFilter!.setValue(foregroundImage, forKey: "inputImage")
        transformFilter!.setValue(NSValue(cgAffineTransform: CGAffineTransform(translationX: backgroundImage.extent.width * 0.5 - foregroundImage.extent.width * 0.5 , y: backgroundImage.extent.height * 0.5 - foregroundImage.extent.height * 0.5)), forKey: "inputTransform")
        let filter = CIFilter(name:"CISourceOverCompositing")
        filter!.setValue(transformFilter!.outputImage!, forKey: "inputImage")
        filter!.setValue(backgroundImage, forKey: "inputBackgroundImage")
        let outputImage = filter!.outputImage
        return outputImage
    }

    var bg:CIImage?
    var blackbg:CIImage?
    var novideobg:CIImage?

    func createBackgroundImage(_ width:Int, height:Int, color:UIColor) -> CIImage {
        let backgroundImage:CIImage = CIImage(image: UIImage.fromColor(color: color, width: width, height: height))!
        return backgroundImage
    }

    func createTimeOnlyImage(_ width:Int, height: Int) -> CIImage {
        if bg == nil {
            bg = createBackgroundImage(width, height: height, color: UIColor.lightGray)
        }
        if novideobg == nil {
            novideobg = imageOverComposition(bg!, foregroundImage: logoImage)
        }
        let imgWithText = addTimeToImage(novideobg!, fontSize: self.textSize)
        let locationString = getLocationTitle()
        if locationString != "" {
            let locImg = addLocationToImage(imgWithText!, fontSize: self.textSize)
            return locImg!
        }
        return imgWithText!
    }

    let context = CIContext(options: nil)

    func processImage(_ inputImage:CIImage, imageOrientation: Int32) -> CIImage? {
        var image:CIImage? = nil
        if blackbg == nil {
            blackbg = createBackgroundImage(Int(inputImage.extent.width), height: Int(inputImage.extent.height), color: UIColor.black)
        }
        if imageOrientation == 1 { // portrait
            let imageExtent:CGRect = inputImage.extent
            let transformFilter = CIFilter(name: "CIAffineTransform")
            transformFilter!.setValue(inputImage, forKey: "inputImage")
            transformFilter!.setValue(NSValue(cgAffineTransform: CGAffineTransform(scaleX: CGFloat(scale), y: CGFloat(scale)).rotated(by: CGFloat(-90.0 * 3.14/180.0)).translatedBy(x: -imageExtent.width, y: 0)), forKey: "inputTransform")
            let translateFilter = CIFilter(name: "CIAffineTransform")
            translateFilter!.setValue(transformFilter!.outputImage!, forKey: "inputImage")
            translateFilter!.setValue(NSValue(cgAffineTransform: CGAffineTransform(translationX: (imageExtent.width - imageExtent.height * CGFloat(scale)) / 2, y: 0)), forKey: "inputTransform")

            let cropedImage = context.createCGImage(translateFilter!.outputImage!, from: CGRect(x: 0, y: 0, width: imageExtent.width, height: imageExtent.height))
            image = CIImage(cgImage: cropedImage!)
        }else if imageOrientation == 3 { // portrait
            let imageExtent:CGRect = inputImage.extent
            let transformFilter = CIFilter(name: "CIAffineTransform")
            transformFilter!.setValue(inputImage, forKey: "inputImage")
            transformFilter!.setValue(NSValue(cgAffineTransform: CGAffineTransform(scaleX: CGFloat(scale), y: CGFloat(scale)).rotated(by: CGFloat(90.0 * 3.14/180.0)).translatedBy(x:0 , y:  -imageExtent.height)), forKey: "inputTransform")
            let translateFilter = CIFilter(name: "CIAffineTransform")
            translateFilter!.setValue(transformFilter!.outputImage!, forKey: "inputImage")
            translateFilter!.setValue(NSValue(cgAffineTransform: CGAffineTransform(translationX: (imageExtent.width - imageExtent.height * CGFloat(scale)) / 2, y: 0)), forKey: "inputTransform")

            let cropedImage = context.createCGImage(translateFilter!.outputImage!, from: CGRect(x: 0, y: 0, width: imageExtent.width, height: imageExtent.height))
            image = CIImage(cgImage: cropedImage!)
        }else if imageOrientation == 2 { // landscape
            if !VideoEncoder.isFrontCamera {
                let imageExtent:CGRect = inputImage.extent
                let transformFilter = CIFilter(name: "CIStraightenFilter")
                transformFilter!.setValue(inputImage, forKey: "inputImage")
                transformFilter!.setValue(NSNumber(value: M_PI_2 * 2), forKey: "inputAngle")
                let cropedImage = context.createCGImage(transformFilter!.outputImage!, from: CGRect(x: 0, y: 0, width: imageExtent.width, height: imageExtent.height))
                image = CIImage(cgImage: cropedImage!)
            }else{
                image = inputImage
            }
        }else{
            if !VideoEncoder.isFrontCamera {
                image = inputImage
            }else{
                let imageExtent:CGRect = inputImage.extent
                let transformFilter = CIFilter(name: "CIStraightenFilter")
                transformFilter!.setValue(inputImage, forKey: "inputImage")
                transformFilter!.setValue(NSNumber(value: M_PI_2 * 2), forKey: "inputAngle")
                let cropedImage = context.createCGImage(transformFilter!.outputImage!, from: CGRect(x: 0, y: 0, width: imageExtent.width, height: imageExtent.height))
                image = CIImage(cgImage: cropedImage!)
            }
        }
        guard let imgWithText = addTimeToImage(image!, fontSize: self.textSize) else {
            return nil
        }
        let locationString = getLocationTitle()
        if locationString != "" {
            let locImg = addLocationToImage(imgWithText, fontSize: self.textSize)
            return locImg
        }
        return imgWithText
    }

    func widthOfString(_ string:NSString, fontName:String, fontSize:CGFloat) -> CGFloat {
        if let font = UIFont(name: fontName, size: fontSize) {
            let fontAttributes = [NSAttributedStringKey.font: font] // it says name, but a UIFont works
            let size = string.size(withAttributes: fontAttributes)
            return size.width
        }
        return 0
    }

    func heightOfString(_ string:NSString, fontName:String, fontSize:CGFloat) -> CGFloat {
        if let font = UIFont(name: fontName, size: fontSize) {
            let fontAttributes = [NSAttributedStringKey.font: font]
            let size = string.size(withAttributes: fontAttributes)
            return size.height
        }
        return 0
    }

    func imageFromString(_ string:NSString, attributes:[NSAttributedStringKey:AnyObject]?, size:CGSize) -> UIImage {
        UIGraphicsBeginImageContextWithOptions(size, false, 0)
        string.draw(in: CGRect(x: 0, y: 0, width: size.width, height: size.height), withAttributes: attributes)
        let image:UIImage = UIGraphicsGetImageFromCurrentImageContext()!
        UIGraphicsEndImageContext()
        return image
    }

    func processingSampleBuffer(_ sampleBuffer: CMSampleBuffer!) -> CVPixelBuffer {
        
        let buffer = CMSampleBufferGetImageBuffer(sampleBuffer)!
        let inputImage: CIImage = CIImage(cvPixelBuffer: buffer)
        if self.streamMode == 2 {
            _ = CVPixelBufferLockBaseAddress(buffer, CVPixelBufferLockFlags(rawValue: 0));
            let rotatedImage = createTimeOnlyImage(Int(inputImage.extent.width), height: Int(inputImage.extent.height))
            self.ciContext?.render(rotatedImage, to: buffer)
            _ = CVPixelBufferUnlockBaseAddress(buffer, CVPixelBufferLockFlags(rawValue: 0));
            return buffer
        }else{
            autoreleasepool{
                _ = CVPixelBufferLockBaseAddress(buffer, CVPixelBufferLockFlags(rawValue: 0));
                let rotatedImage = processImage(inputImage, imageOrientation: self.orientation)!
                
                if bg == nil {
                    bg = createBackgroundImage(Int(inputImage.extent.width), height: Int(inputImage.extent.height), color: UIColor.lightGray)
                }
                self.ciContext?.render(rotatedImage, to: buffer, bounds:inputImage.extent, colorSpace:nil)
                _ = CVPixelBufferUnlockBaseAddress(buffer, CVPixelBufferLockFlags(rawValue: 0));
                }
            return buffer
        }
        
    }

  
//    status = CVPixelBufferLockBaseAddress(pxbuffer.memory!, 0);
//    
//    let bufferAddress = CVPixelBufferGetBaseAddress(pxbuffer.memory!);
//    
//    status = CVPixelBufferUnlockBaseAddress(pxbuffer.memory!, 0);
    
    /////////////
    //            let pixelLate:CIFilter = CIFilter(name: "CIPixellate")!
    //            pixelLate.setDefaults()
    //            pixelLate.setValue(CIImage(CVPixelBuffer: imageBuffer!), forKey: kCIInputImageKey)
    //            pixelLate.setValue(CIVector(CGPoint: CGPointMake(100.0, 100.0)), forKey: kCIInputCenterKey)
    //            pixelLate.setValue(22, forKey: kCIInputScaleKey)
    //            inputImage = pixelLate.outputImage!
    //////////////
    //            let gloom:CIFilter = CIFilter(name: "CISepiaTone")!
    //            gloom.setDefaults()
    //            gloom.setValue(CIImage(CVPixelBuffer: imageBuffer!), forKey: kCIInputImageKey)
    //            gloom.setValue(0.5, forKey: kCIInputIntensityKey)
    //
    //            let img = gloom.outputImage
    
    //////////////////////////////////////
    
    
//    func blendImages(buffer:CMSampleBuffer){
//        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)){
//            let pixelBuffer = CMSampleBufferGetImageBuffer(buffer)
//            let cameraImage = CIImage(CVPixelBuffer: pixelBuffer!)
//            if let backgroundImage = self.lastImage {
//                let blendEffect = CIFilter(name: "CILightenBlendMode")!
//                blendEffect.setValue(CIImage(image: backgroundImage), forKey: kCIInputBackgroundImageKey)
//                blendEffect.setValue(cameraImage, forKey:kCIInputImageKey)
//                let imageRef = self.context.createCGImage(blendEffect.outputImage!,fromRect: blendEffect.outputImage!.extent)
//                self.lastImage = UIImage(CGImage: imageRef)
//                print("Blending")
//            }else{
//                let imageRef = self.context.createCGImage(cameraImage,fromRect: cameraImage.extent)
//                self.lastImage = UIImage(CGImage: imageRef)
//            }
//            let filteredImage = self.lastImage
//            dispatch_async(dispatch_get_main_queue())
//            {
//                self.imageView.image = filteredImage
//            }
//        }
//    }
}

extension String {
    func heightWithConstrainedWidth(width: CGFloat, font: UIFont) -> CGFloat {
        let constraintRect = CGSize(width: width, height: .greatestFiniteMagnitude)
        let boundingBox = self.boundingRect(with: constraintRect, options: .usesLineFragmentOrigin, attributes: [NSAttributedStringKey.font: font], context: nil)
        return boundingBox.height
    }

    func widthWithConstrainedHeight(height: CGFloat, font: UIFont) -> CGFloat {
        let constraintRect = CGSize(width: .greatestFiniteMagnitude, height: height)
        let boundingBox = self.boundingRect(with: constraintRect, options: .usesLineFragmentOrigin, attributes: [NSAttributedStringKey.font: font], context: nil)
        return boundingBox.width
    }
}

extension NSAttributedString {
    func heightWithConstrainedWidth(width: CGFloat) -> CGFloat {
        let constraintRect = CGSize(width: width, height: .greatestFiniteMagnitude)
        let boundingBox = self.boundingRect(with: constraintRect, options: .usesLineFragmentOrigin, context: nil)
        
        return boundingBox.height
    }
    
    func widthWithConstrainedHeight(height: CGFloat) -> CGFloat {
        let constraintRect = CGSize(width: .greatestFiniteMagnitude, height: height)
        let boundingBox = self.boundingRect(with: constraintRect, options: .usesLineFragmentOrigin, context: nil)
        
        return boundingBox.width
    }
}

extension CMSampleBuffer {
    
    var isKeyFrame: Bool? {
        let attachments = CMSampleBufferGetSampleAttachmentsArray(self, true)
        guard attachments != nil else { return nil }
        
        let unsafePointer = CFArrayGetValueAtIndex(attachments, 0)
        let nsDic = unsafeBitCast(unsafePointer, to: NSDictionary.self)
        guard let dic = nsDic as? Dictionary<String, AnyObject> else { return nil }
        
        guard let dependsOnOthersOptinal = dic["DependsOnOthers"],
            let dependsOnOthers = dependsOnOthersOptinal as? Bool
            else { return nil }
        
        let keyFrame = !dependsOnOthers
        return keyFrame
    }
    
    var dependsOnOthers: Bool {
//        guard let
//            attachments = CMSampleBufferGetSampleAttachmentsArray(self, false),
//            let attachment = unsafeBitCast(CFArrayGetValueAtIndex(attachments, 0), to: CFDictionary.self) as Dictionary?
//            else { return false }
//        
//        return attachment["DependsOnOthers"] as! Bool

        guard
            let attachments:CFArray = CMSampleBufferGetSampleAttachmentsArray(self, false) else {
                return false
        }
        let attachment:[NSObject: AnyObject] = unsafeBitCast(CFArrayGetValueAtIndex(attachments, 0), to: CFDictionary.self) as [NSObject : AnyObject]
        return attachment["DependsOnOthers" as NSObject] as! Bool
    }

    var dataBuffer: CMBlockBuffer? {
        get {
            return CMSampleBufferGetDataBuffer(self)
        }
        set {
            guard let dataBuffer = newValue else {
                return
            }
            CMSampleBufferSetDataBuffer(self, dataBuffer)
        }
    }

    var duration: CMTime {
        return CMSampleBufferGetDuration(self)
    }

    var formatDescription: CMFormatDescription? {
        return CMSampleBufferGetFormatDescription(self)
    }

    var decodeTimeStamp: CMTime {
        let decodeTimestamp:CMTime = CMSampleBufferGetDecodeTimeStamp(self)
        return decodeTimestamp == kCMTimeInvalid ? presentationTimeStamp : decodeTimestamp
    }

    var presentationTimeStamp: CMTime {
        return CMSampleBufferGetPresentationTimeStamp(self)
    }
}

extension Mirror {
    var description: String {
        var data: [String] = []
        if let superclassMirror = superclassMirror {
            for child in superclassMirror.children {
                guard let label = child.label else {
                    continue
                }
                data.append("\(label):\(child.value)")
            }
        }
        for child in children {
            guard let label = child.label else {
                continue
            }
            data.append("\(label):\(child.value)")
        }
        return "\(subjectType){\(data.joined(separator: ","))}"
    }
}

extension UIImage {
    static func fromColor(color: UIColor, width: Int, height: Int) -> UIImage {
        let rect = CGRect(x: 0, y: 0, width: width, height: height)
        UIGraphicsBeginImageContext(rect.size)
        let context = UIGraphicsGetCurrentContext()
        context!.setFillColor(color.cgColor)
        context!.fill(rect)
        let img = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()
        return img!
    }
}

// MARK: -
extension ExpressibleByIntegerLiteral {
    var bytes:[UInt8] {
        var data:[UInt8] = [UInt8](repeating: 0, count: MemoryLayout<`Self`>.size)
        data.withUnsafeMutableBufferPointer {
            UnsafeMutableRawPointer($0.baseAddress!).storeBytes(of: self, as: Self.self)
        }
        return data
    }
    
    init(bytes:[UInt8]) {
        self = bytes.withUnsafeBufferPointer {
            UnsafeRawPointer($0.baseAddress!).load(as: Self.self)
        }
    }
}

/////////////////////////////////////////////////////////
//["CIAccordionFoldTransition",
// "CIAdditionCompositing",
// "CIAffineClamp",
// "CIAffineTile",
// "CIAffineTransform",
// "CIAreaAverage",
// "CIAreaHistogram",
// "CIAreaMaximum",
// "CIAreaMaximumAlpha",
// "CIAreaMinimum",
// "CIAreaMinimumAlpha",
// "CIBarsSwipeTransition",
// "CIBlendWithAlphaMask",
// "CIBlendWithMask",
// "CIBloom",
// "CIBoxBlur",
// "CIBumpDistortion",
// "CIBumpDistortionLinear",
// "CICheckerboardGenerator",
// "CICircleSplashDistortion",
// "CICircularScreen",
// "CICircularWrap",
// "CICMYKHalftone",
// "CIColorBlendMode",
// "CIColorBurnBlendMode",
// "CIColorClamp",
// "CIColorControls",
// "CIColorCrossPolynomial",
// "CIColorCube",
// "CIColorCubeWithColorSpace",
// "CIColorDodgeBlendMode",
// "CIColorInvert",
// "CIColorMap",
// "CIColorMatrix",
// "CIColorMonochrome",
// "CIColorPolynomial",
// "CIColorPosterize",
// "CIColumnAverage",
// "CIComicEffect",
// "CIConstantColorGenerator",
// "CIConvolution3X3",
// "CIConvolution5X5",
// "CIConvolution7X7",
// "CIConvolution9Horizontal",
// "CIConvolution9Vertical",
// "CICopyMachineTransition",
// "CICrop",
// "CICrystallize",
// "CIDarkenBlendMode",
// "CIDepthOfField",
// "CIDifferenceBlendMode",
// "CIDiscBlur",
// "CIDisintegrateWithMaskTransition",
// "CIDisplacementDistortion",
// "CIDissolveTransition",
// "CIDivideBlendMode",
// "CIDotScreen",
// "CIDroste",
// "CIEdges",
// "CIEdgeWork",
// "CIEightfoldReflectedTile",
// "CIExclusionBlendMode",
// "CIExposureAdjust",
// "CIFalseColor",
// "CIFlashTransition",
// "CIFourfoldReflectedTile",
// "CIFourfoldRotatedTile",
// "CIFourfoldTranslatedTile",
// "CIGammaAdjust",
// "CIGaussianBlur",
// "CIGaussianGradient",
// "CIGlassDistortion",
// "CIGlassLozenge",
// "CIGlideReflectedTile", "CIGloom", "CIHardLightBlendMode", "CIHatchedScreen", "CIHeightFieldFromMask", "CIHexagonalPixellate", "CIHighlightShadowAdjust", "CIHistogramDisplayFilter", "CIHoleDistortion", "CIHueAdjust", "CIHueBlendMode", "CIKaleidoscope", "CILanczosScaleTransform", "CILenticularHaloGenerator", "CILightenBlendMode", "CILightTunnel", "CILinearBurnBlendMode", "CILinearDodgeBlendMode", "CILinearGradient", "CILinearToSRGBToneCurve", "CILineOverlay", "CILineScreen", "CILuminosityBlendMode", "CIMaskedVariableBlur", "CIMaskToAlpha", "CIMaximumComponent", "CIMaximumCompositing", "CIMedianFilter", "CIMinimumComponent", "CIMinimumCompositing", "CIModTransition", "CIMotionBlur", "CIMultiplyBlendMode", "CIMultiplyCompositing", "CINoiseReduction", "CIOpTile", "CIOverlayBlendMode", "CIPageCurlTransition", "CIPageCurlWithShadowTransition", "CIParallelogramTile", "CIPDF417BarcodeGenerator", "CIPerspectiveCorrection", "CIPerspectiveTile", "CIPerspectiveTransform", "CIPerspectiveTransformWithExtent", "CIPhotoEffectChrome", "CIPhotoEffectFade", "CIPhotoEffectInstant", "CIPhotoEffectMono", "CIPhotoEffectNoir", "CIPhotoEffectProcess", "CIPhotoEffectTonal", "CIPhotoEffectTransfer", "CIPinchDistortion", "CIPinLightBlendMode", "CIPixellate", "CIPointillize", "CIRadialGradient", "CIRandomGenerator", "CIRippleTransition", "CIRowAverage", "CISaturationBlendMode", "CIScreenBlendMode", "CISepiaTone", "CIShadedMaterial", "CISharpenLuminance", "CISixfoldReflectedTile", "CISixfoldRotatedTile", "CISmoothLinearGradient", "CISoftLightBlendMode", "CISourceAtopCompositing", "CISourceInCompositing", "CISourceOutCompositing", "CISourceOverCompositing", "CISpotColor", "CISpotLight", "CISRGBToneCurveToLinear", "CIStarShineGenerator", "CIStraightenFilter", "CIStretchCrop", "CIStripesGenerator", "CISubtractBlendMode", "CISunbeamsGenerator", "CISwipeTransition", "CITemperatureAndTint", "CIToneCurve", "CITorusLensDistortion", "CITriangleKaleidoscope", "CITriangleTile", "CITwelvefoldReflectedTile", "CITwirlDistortion", "CIUnsharpMask", "CIVibrance", "CIVignette", "CIVignetteEffect", "CIVortexDistortion", "CIWhitePointAdjust", "CIZoomBlur"]

/////////////////////////////////////////////////////////
//{
//    AllocMaxOpBuffer =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    AllowFrameReordering =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    AllowPixelTransfer =     {
//    };
//    AllowTemporalCompression =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    AverageBitRate =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    AverageNonDroppableFrameRate =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    BPictures =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    CleanAperture =     {
//    };
//    ClientPID =     {
//    };
//    CodedBuffersOverride =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    ColorPrimaries =     {
//        PropertyType = Enumeration;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//        SupportedValueList =         (
//            "ITU_R_709_2",
//            "EBU_3213",
//            "SMPTE_C"
//        );
//    };
//    ConvergenceDurationForAverageDataRate =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    DataRateLimits =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    DeblockingFiltering =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    DebugMetadataSEI =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    DebugMetadataSEIuseEPB =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    DisableDynamicClocking =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableAttachMVStats =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableClosedGOP =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableContextSwitchInTheMiddle =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableGoldenVideo =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableLambdaMod =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableMBInputCtrl =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableMultiReferenceP =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableQPMod =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableRCDriver =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableRCFW =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableSEITagInsertion =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableStaticAreasLowQP =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableStatsCollect =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableTransform8x8 =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableUserQPForFacetime =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableUserRefForFacetime =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableVariableB =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnableWeightedPrediction =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EncoderUsage =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    EnsureTIJacinto4Compatibility =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    ExpectedDuration =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    ExpectedFrameRate =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    FieldCount = {
//    };
//    FieldDetail =     {
//    };
//    FigThreadPriority =     {
//    };
//    FlatAreaLowQp =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    GammaLevel = { };
//    H264EntropyMode =     {
//        PropertyType = Enumeration;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    ICCProfile =     {
//    };
//    InitialQPB =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    InitialQPI =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    InitialQPP =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    InputPixelFormat =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    InputQueueMaxCount =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    LossLess =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    MaxKeyFrameInterval =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    MaxKeyFrameIntervalDuration =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    MultiPassStorage =     {
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    MultiReferencePSpacing =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    NegotiationDetails =     {
//        PropertyType = Documentation;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    NumberOfPendingFrames = { };
//    NumberOfSlices =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    OffsetScaleMode =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    PerceptualQualityOptimization = { PropertyType = Boolean; ReadWriteStatus = ReadWrite; ShouldBeSerialized = 0;
//    };
//    PixelAspectRatio = { };
//    PixelBufferPoolIsShared = { };
//    PixelTransferProperties = { };
//    PoolPixelBufferAttributes = { };
//    PoolPixelBufferAttributesSeed = { };
//    Priority =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    ProfileLevel =     {
//        PropertyType = Enumeration;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//        SupportedValueList =         (
//            "H264_Baseline_1_3",
//            "H264_Baseline_3_0",
//            "H264_Baseline_3_1",
//            "H264_Baseline_3_2",
//            "H264_Baseline_4_0",
//            "H264_Baseline_4_1",
//            "H264_Baseline_5_0",
//            "H264_Baseline_5_1",
//            "H264_Baseline_5_2",
//            "H264_Main_3_0",
//            "H264_Main_3_1",
//            "H264_Main_3_2",
//            "H264_Main_4_0",
//            "H264_Main_4_1",
//            "H264_Main_5_0",
//            "H264_Main_5_1",
//            "H264_Main_5_2",
//            "H264_High_3_0",
//            "H264_High_3_1",
//            "H264_High_3_2",
//            "H264_High_4_0",
//            "H264_High_4_1",
//            "H264_High_5_0",
//            "H264_High_5_1",
//            "H264_High_5_2",
//            "H264_Baseline_AutoLevel",
//            "H264_Main_AutoLevel",
//            "H264_High_AutoLevel",
//            "H264_High422_AutoLevel",
//            "H264_High444Predictive_AutoLevel"
//        );
//    };
//    RealTime =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    RoundingOffsetMode =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    SoftMinH264QuantizationParameter =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    SourceFrameCount =     {
//        PropertyType = Number;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    ThrottleForBackground =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    TransferFunction =     {
//        PropertyType = Enumeration;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//        SupportedValueList =         (
//            "ITU_R_709_2",
//            "SMPTE_240M_1995",
//            UseGamma
//        );
//    };
//    UseAsyncFWScheduling =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    UseCAVLCBits =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    UseElementaryStreamOutput =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    UseLongTermReference =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    UseVideoResolutionAdaptation =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    UserDPBFramesForFaceTime =     {
//        PropertyType = Enumeration;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    UsingHardwareAcceleratedVideoEncoder = { PropertyType = Boolean; ReadWriteStatus = ReadWrite; ShouldBeSerialized = 0;
//    };
//    VideoEncoderPixelBufferAttributes = {   };
//    VnomQueueThrottling =     {
//        PropertyType = Boolean;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//    };
//    VnomQueueThrottlingThreshold = { PropertyType = Number; ReadWriteStatus = ReadWrite; ShouldBeSerialized = 0;
//    };
//    YCbCrMatrix =     {
//        PropertyType = Enumeration;
//        ReadWriteStatus = ReadWrite;
//        ShouldBeSerialized = 0;
//        SupportedValueList =         (
//            "ITU_R_709_2",
//            "ITU_R_601_4",
//            "SMPTE_240M_1995"
//        );
//    };
//    "log2_max_minus4" = { PropertyType = Number; ReadWriteStatus = ReadWrite; ShouldBeSerialized = 0;
//    };
//}
