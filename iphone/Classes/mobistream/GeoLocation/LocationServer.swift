//
//  LocationServer.swift
//  AreaSight
//
//  Created by Александр on 25.01.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit

protocol LocationServerDelegate : class{
    func locationServer(_ sender: LocationServer, message:String)
}

class LocationServer: NSObject {

    var emei = "222222222222222"
    var gpsHost = "194.135.112.73"
    var gpsPort = 11002

    static let sharedInstance = LocationServer()
    var locationManager:CLLocationManager = CLLocationManager()
    var timer:Timer?
    var lastLocation:CLLocation?
    var delegate:LocationServerDelegate?

    var gpsConnection:SimpleConnection?
    var gpsStreamConnected = false
    
    var showGpsInVideo:Bool = false

    func start() {
        locationManager.delegate = self
        locationManager.requestAlwaysAuthorization()
        locationManager.startUpdatingLocation()
        
        startTimer()
    }

    func stop(){
        locationManager.stopUpdatingLocation()

        stopTimer()
        disconnectGpsServer()
    }

    func startTimer() {
        print("in start timer")
        timer = Timer(timeInterval: 10, target: self, selector: #selector(addSecond), userInfo: nil, repeats: true)
        if let timer = self.timer {
            RunLoop.current.add(timer, forMode: RunLoopMode.defaultRunLoopMode)
        }
    }

    func stopTimer() {
        timer?.invalidate()
    }

    var mes:String?
    
    @objc func addSecond() {
        DispatchQueue.main.async {
            if let lastLocation = self.lastLocation {
                let message = self.toServerProtocol(lastLocation)
//                self.delegate?.locationServer(self, message: message)

                //writeGps(message)
                self.mes = message
//                print(message)
                self.connectGpsServer()

                
            }
        }
    }

    func toServerProtocol(_ location:CLLocation) -> String {
        //  imei:666136661366613,tracker,0809231929,13554900601,F,112909.397,A,2234.4669,N,11354.3287,E,0.11,;
//        let dateString = getUTCFormatDate(location.timestamp)
//        let timeString = getUTCFormatTime(location.timestamp)
        let imei = self.emei//UIDevice.current.identifierForVendor?.uuidString
        let status = "tracker"
        let number1 = "0"
        let signal = "F"
        let currentTime = getUTCFormatTime(location.timestamp)
        let dataStatus = "A" // A - данные достоверны V - недостоверны

//        let dms = coordinateToDMS(lat: location.coordinate.latitude, lon: location.coordinate.longitude)

      let latitude = coordinateString(latitude: location.coordinate.latitude, longitude: location.coordinate.longitude)[0]
//        let latitude = dms.latitude
        let latitudeSemisphere = location.coordinate.latitude > 0 ? "N" : "S"
        
      let longitude = coordinateString(latitude: location.coordinate.latitude, longitude: location.coordinate.longitude)[1]
//        let longitude = dms.longitude
        
        let longitudeSemisphere = location.coordinate.longitude > 0 ? "E" : "W"
        let speed = Double(location.speed) < 0 ? 0 : Double(location.speed)
        let speedCourse = Double(location.course) < 0 ? 0 : Double(location.course)
        let str = "imei:\(imei),\(status),\(number1),,\(signal),\(currentTime),\(dataStatus),\(latitude),\(latitudeSemisphere),\(longitude),\(longitudeSemisphere),\(speed),\(Int(speedCourse));\\r\\n\n"
        return str
    }

    func getUTCFormatDate(_ localDate:Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "ddMMYY"
        dateFormatter.timeZone = TimeZone(abbreviation: "UTC")
        let date = dateFormatter.string(from: localDate)
        return date
    }

    func getUTCFormatTime(_ localDate:Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "HHmmss.SSS"
        dateFormatter.timeZone = TimeZone(abbreviation: "UTC")
        let date = dateFormatter.string(from: localDate)
        return date
    }

    func convert(_ coord:Double) -> String? {
        var coordinate = coord
        if coordinate < -180.0 || coordinate > 180.0 {
            return nil;
        }
        var str = ""
        if coordinate < 0 {
            str.append("-")
            coordinate = abs(coordinate)
        }
        let degrees = floor(coordinate)
        str.append("\(degrees)")
        coordinate = coordinate - degrees
        coordinate = coordinate * 60.0
        var temp = String(format: "%08.6f", coordinate)
        if coordinate < 10 {
            temp = String(format: "0%f", coordinate)
        }
        return "\(degrees)\(temp)"
    }
    
    func coordinateToDMS(lat: Double, lon: Double) -> (latitude: String, longitude: String) {
        
        let latDegrees = abs(Int(lat))
        let latMinutes = abs(Int((lat * 3600).truncatingRemainder(dividingBy: 3600) / 60))
        let latSeconds = Double(abs((lat * 3600).truncatingRemainder(dividingBy: 3600)).truncatingRemainder(dividingBy: 60))
        
        let lonDegrees = abs(Int(lon))
        let lonMinutes = abs(Int((lon * 3600).truncatingRemainder(dividingBy: 3600) / 60) )
        let lonSeconds = Double(abs((lon * 3600).truncatingRemainder(dividingBy: 3600)) / 60 )
        
        return (String(format:"%d%d%.4f", latDegrees, latMinutes, latSeconds),
                String(format:"%d%d%.4f", lonDegrees, lonMinutes, lonSeconds))
    }
    
    func coordinateString(latitude:Double, longitude:Double) -> [String] {
        let latDegrees = Int(latitude)
        let latMinutes = (latitude - Double(Int(latitude))) * 0.6 * 100
        let latRes = String(format:"%d%2.8f", latDegrees, latMinutes)
        
        
        let lngDegrees = Int(longitude)
        let lngMinutes = (longitude - Double(Int(longitude))) * 0.6 * 100
        let lngRes = String(format:"%d%2.8f", lngDegrees, lngMinutes)
        
        return [latRes, lngRes]
        
        
        
//        var latSeconds = Int(latitude * 3600)
//        let latDegrees = latSeconds / 3600
//        latSeconds = abs(latSeconds % 3600)
//        let latMinutes = latSeconds / 60
//        latSeconds %= 60
//        var longSeconds = Int(longitude * 3600)
//        let longDegrees = longSeconds / 3600
//        longSeconds = abs(longSeconds % 3600)
//        let longMinutes = longSeconds / 60
//        longSeconds %= 60
//
//        let lat = String(format:"%d%d.%d", abs(latDegrees), latMinutes, latSeconds)
//        let lon = String(format:"%d%d.%d", abs(longDegrees), longMinutes, longSeconds)
//        return [lat, lon]
    }

//    func coordinateString(latitude:Double, longitude:Double) -> String {
//        var latSeconds = Int(latitude * 3600)
//        let latDegrees = latSeconds / 3600
//        latSeconds = abs(latSeconds % 3600)
//        let latMinutes = latSeconds / 60
//        latSeconds %= 60
//        var longSeconds = Int(longitude * 3600)
//        let longDegrees = longSeconds / 3600
//        longSeconds = abs(longSeconds % 3600)
//        let longMinutes = longSeconds / 60
//        longSeconds %= 60
//        return String(format:"%d°%d'%d\"%@ %d°%d'%d\"%@",
//                      abs(latDegrees),
//                      latMinutes,
//                      latSeconds,
//                      {return latDegrees >= 0 ? "N" : "S"}(),
//                      abs(longDegrees),
//                      longMinutes,
//                      longSeconds,
//                      {return longDegrees >= 0 ? "E" : "W"}() )
//    }
    
    

    
    func writeGps(_ data:String) {
        _ = self.gpsConnection?.write(data.data(using: .utf8))
    }
    
    func connectGpsServer() {

        if gpsConnection != nil {
            gpsConnection?.disconnect()
            gpsConnection = nil
        }

        gpsConnection = SimpleConnection(host: gpsHost, andPort: Int32(gpsPort))
        gpsConnection?.setDelegate(self)
        gpsConnection?.connect()
    }
    
    func disconnectGpsServer() {
        gpsConnection?.disconnect()
    }
}

extension LocationServer: CLLocationManagerDelegate {
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        //        for item in locations {
        //            var loc:GeoLocation = GeoLocation()
        //            loc.latitude = item.coordinate.latitude
        //            loc.longitude = item.coordinate.longitude
        //            loc.latitudeHemisphere = item.coordinate.latitude > 0 ? "N" : "S"
        //            loc.longitudeHemisphere = item.coordinate.longitude > 0 ? "E" : "W"
        //            loc.date = item.timestamp
        //            loc.speed = item.speed
        //            loc.course = item.course
        //            loc.horizontalAccuracy = item.horizontalAccuracy
        //            loc.verticalAccuracy = item.verticalAccuracy
        //            lastLocation = loc
        //        }
        DispatchQueue.main.async {
//            if self.showGpsInVideo {
//                if let latitude = locations.last?.coordinate.latitude, let longitude = locations.last?.coordinate.longitude {
//
//                    VideoEncoder.sharedInstance.setLocationTitle("\(String(format: "%02.6f", latitude))  \(String(format: "%02.6f", longitude))")
//                }
//            }
            self.lastLocation = locations.last
        }
    }
}

extension LocationServer: SimpleConnectionDelegate {
    
    func onMessageReceivedString(_ message: String!, fromConnection connection: Any!) {
        //        print("Recive:\(message)")
    }
    
    func onMessageReceived(_ message: Data!) {
        //        print(String(data: message, encoding: .utf8) ?? "Location server error")
    }
    
    func onConnected(_ connection: Any!, isConnected: Bool, withError error: Error!) {
        if isConnected {
            if let mes = mes {
                writeGps(mes)
            }
        }
        //        gpsStreamConnected = isConnected
        //        if isConnected {
        //            print("CONNECTED!")
        //            requestRegisterCamera()
        //        } else {
        //            print(error)
        //            delegate?.onVideoRegistered?(self, connected: false, withError: error)
        //        }
    }
}
