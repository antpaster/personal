//
//  GeoLocation.m
//  MobiStream
//
//  Created by netris on 20.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import "GeoLocationServer.h"
#import <UIKit/UIKit.h>

static GeoLocationServer *server;
static id<GeoLocationDelegate> delegate;

@implementation GeoLocationServer
{
    NSString *macAddress;
    float currentHeading;
    float magneticHeading;
}

+ (void) initialize
{
    if (self == [GeoLocationServer class]){
        server = [[GeoLocationServer alloc] init];
    }
}

+ (GeoLocationServer*) server
{
    return server;
}

//- (id) init {
//    self = [super init];
//    if(nil != self){
//        self.locationManager = [[CLLocationManager alloc] init];
//        self.locationManager.delegate = self;
////      self.locationManager.desiredAccuracy = kCLLocationAccuracyHundredMeters;
////      self.locationManager.distanceFilter = 10; // 10 m
//        [self.locationManager requestAlwaysAuthorization];
//    }
//    return self;
//}

- (void) startupWithDistanceFilter:(CLLocationDistance)distFilter accuracy:(CLLocationAccuracy) accuracy withMac:(NSString *)mac
{
    [self.locationManager requestAlwaysAuthorization];
    macAddress = [mac copy];
    currentHeading = -1;
    magneticHeading = -1;
    self.locationManager = [[CLLocationManager alloc] init];
 //   self.locationManager.distanceFilter = distFilter; // 10 m
    self.locationManager.desiredAccuracy = accuracy;
    self.locationManager.headingFilter = 1;
//    self.locationManager.desiredAccuracy = kCLLocationAccuracyKilometer;
//                                      kCLLocationAccuracyBest;
//                                      kCLLocationAccuracyBestForNavigation;
//                                      kCLLocationAccuracyHundredMeters;
//                                      kCLLocationAccuracyKilometer;
//                                      kCLLocationAccuracyNearestTenMeters;
//                                      kCLLocationAccuracyThreeKilometers;

    self.locationManager.delegate = self;
    [self.locationManager requestAlwaysAuthorization];
}

- (void) startUpdatingLocation
{
    if ([CLLocationManager locationServicesEnabled]) {
        [self.locationManager startUpdatingLocation];
    }else{
        [delegate onLocationError:[ApplicationErrors createErrorInDomain:@"GeoLocationServer" code:1001 reason:@"Location service not enabled." description:@"Location service not enabled."]];
    }
    if ([CLLocationManager headingAvailable]) {
        [self.locationManager startUpdatingHeading];
    }else{
        [delegate onLocationError:[ApplicationErrors createErrorInDomain:@"GeoLocationServer" code:1001 reason:@"Heading service not enabled." description:@"Heading service not enabled."]];
    }
}

- (void) stopUpdatingLocation
{
    if([CLLocationManager locationServicesEnabled])
        [self.locationManager stopUpdatingLocation];
    
    if ([CLLocationManager headingAvailable])
        [self.locationManager stopUpdatingHeading];
}

- (void) locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations
{
    CLLocation *location = [locations lastObject];
    [location course];
    GeoLocation *geoLocation = [[GeoLocation alloc] init];
    CLLocationCoordinate2D coord = [location coordinate];
    geoLocation.latitude = coord.latitude;
    geoLocation.longitude = coord.longitude;
    geoLocation.latitudeHemisphere = coord.latitude > 0 ? @"N" : @"S";
    geoLocation.longitudeHemisphere = coord.longitude > 0 ? @"E" : @"W";
    geoLocation.date = [location timestamp];
    geoLocation.speed = [location speed];
    geoLocation.course = [location course];
    geoLocation.horizontalAccuracy = [location horizontalAccuracy];
    geoLocation.verticalAccuracy = [location verticalAccuracy];
    NSData *json = [self toJson:geoLocation];
    if(json != nil){
//        NSString *jsonString = [[NSString alloc] initWithData:json encoding:NSUTF8StringEncoding];
        if (nil != delegate) {
            //[delegate onLocationChangedJson:jsonString];
            
            [delegate onLocationChanged:location];
           
         //   [delegate onLocationChangedJson:[self toGpsServerFormat:location]];
        }
    }
}

- (void) locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading
{
    if(newHeading.headingAccuracy > 0){
        magneticHeading = newHeading.magneticHeading;
        currentHeading = newHeading.trueHeading;
    }
}

- (float) convertHeading:(float)heading fromOrientation:(UIDeviceOrientation) orientation
{
    float realHeading = heading;
    
    switch (orientation) {
        case UIDeviceOrientationPortrait:
            break;
        case UIDeviceOrientationPortraitUpsideDown:
            realHeading = realHeading + 180.0f;
            break;
        case UIDeviceOrientationLandscapeLeft:
            realHeading = realHeading + 90.0f;
            break;
        case UIDeviceOrientationLandscapeRight:
            realHeading = realHeading - 90.0f;
            break;
        default:
            break;
    }
    while (realHeading > 360.0f) {
        realHeading = realHeading - 360;
    }
    return realHeading;
}

- (void) setDelegate: (id) newDelegate
{
    delegate = newDelegate;
}

- (NSString *) toGpsServerFormat: (CLLocation *) location
{
    //  imei:666136661366613,tracker,0809231929,13554900601,F,112909.397,A,2234.4669,N,11354.3287,E,0.11,;
//    NSString *dateString = [self getUTCFormateDate:[location timestamp]];
//    NSString *timeString = [self getUTCFormateTime:[location timestamp]];
    
    
    NSString *imei = @"666136661366613";
    NSString *status = @"tracker";
    NSString *number1 = @"0809231929";
    NSString *number2 = @"13554900601";
    NSString *signal = @"F";
    NSString *currenttime = [self getUTCFormateTime:location.timestamp]; //hhmmss.sss
    NSString *datastatus = @"A"; // A - данные достоверны V - недостоверны
    NSString *latitude = [self convert:location.coordinate.latitude];//[self convert:location.latitude];
    NSString *latitudeSemisphere = location.coordinate.latitude > 0 ? @"N" : @"S";
    NSString *longitude = [self convert:location.coordinate.longitude];
    NSString *longitudeSemisphere = location.coordinate.longitude > 0 ? @"E" : @"W";

    NSNumber *speed = [NSNumber numberWithFloat:location.speed];
    NSNumber *speedCourse = [NSNumber numberWithFloat:location.course];
    
    if (location.speed >= 0) {
        speed = [NSNumber numberWithDouble:location.speed];//[NSString stringWithFormat:@"%@",[NSNumber numberWithDouble:location.speed]];// forKey:@"speed"
        if (location.course >= 0) {
            speedCourse = [NSNumber numberWithDouble:location.course];// forKey:@"direction"
        }
    }
    
    NSString *str = [NSString stringWithFormat:@"imei:%@,%@,%@,%@,%@,%@,%@,%@,%@,%@,%@,%@,%@;", imei, status,number1,number2,signal,currenttime,datastatus,latitude,latitudeSemisphere,longitude,longitudeSemisphere,speed,speedCourse];
    
    return str;
}

- (NSString *) toServerFormat: (GeoLocation *) location
{
//  imei:666136661366613,tracker,0809231929,13554900601,F,112909.397,A,2234.4669,N,11354.3287,E,0.11,;

    NSString *imei = @"666136661366613";
    NSString *status = @"tracker";
    NSString *number1 = @"0809231929";
    NSString *number2 = @"13554900601";
    NSString *signal = @"F";
    NSString *currenttime = [self getUTCFormateTime:location.date]; //hhmmss.sss
    NSString *datastatus = @"A"; // A - данные достоверны V - недостоверны
    NSString *latitude = [self convert:location.latitude];
    NSString *latitudeSemisphere = location.latitudeHemisphere;
    NSString *longitude = [self convert:location.longitude];
    NSString *longitudeSemisphere = location.longitudeHemisphere;
    NSNumber *speed;
    NSNumber *speedCourse;
    
    if (location.speed >= 0) {
        speed = [NSNumber numberWithDouble:location.speed];//[NSString stringWithFormat:@"%@",[NSNumber numberWithDouble:location.speed]];// forKey:@"speed"
        if (location.course >= 0) {
            speedCourse = [NSNumber numberWithDouble:location.course];// forKey:@"direction"
        }
    }

    NSString *str = [NSString stringWithFormat:@"imei:%@,%@,%@,%@,%@,%@,%@,%@,%@,%@,%@,%@,%@", imei, status,number1,number2,signal,currenttime,datastatus,latitude,latitudeSemisphere,longitude,longitudeSemisphere,speed,speedCourse];

    return str;
}

- (NSData *) toJson: (GeoLocation *)location
{
    // {
    //   "action":"send_gps_data",
    //   "parameters":{
    //            "mac":"",
    //            "lat":1.23,
    //            "latHemisphere":"N",
    //            "lon":1.23,
    //            "lonHemisphere":"E",
    //            "time":"",
    //            "date":""
    //            "speed":123.213,
    //            "direction":123.132,
    //            "magnDecl":123.234,
    //            "magnDeclDirection":"E"
    //    }
    // }

    NSString *dateString = [self getUTCFormateDate:location.date];
    NSString *timeString = [self getUTCFormateTime:location.date];
    NSMutableDictionary *parametersDic = [[NSMutableDictionary alloc] init];
    [parametersDic setObject:macAddress forKey:@"mac"];
    [parametersDic setObject:[self convert:location.latitude] forKey:@"lat"];
    [parametersDic setObject:location.latitudeHemisphere forKey:@"latHemisphere"];
    [parametersDic setObject:[self convert:location.longitude] forKey:@"lon"];
    [parametersDic setObject:location.longitudeHemisphere forKey:@"lonHemisphere"];
    [parametersDic setObject:timeString forKey:@"time"];
    [parametersDic setObject:dateString forKey:@"date"];
    if (location.speed >= 0) {
        [parametersDic setObject:[NSNumber numberWithDouble:location.speed] forKey:@"speed"];
        if (location.course >= 0) {
            [parametersDic setObject:[NSNumber numberWithDouble:location.course] forKey:@"direction"];
        }
    }
    if (currentHeading >= 0 && currentHeading < 360) {
//        [parametersDic setObject:[NSNumber numberWithDouble:currentHeading] forKey:@"heading"];
    }
//    [parametersDic setObject:@"" forKey:@"magnDecl"];
//    [parametersDic setObject:@"" forKey:@"magnDeclDirection"];

    NSMutableDictionary *jsonDic = [[NSMutableDictionary alloc] init];
    [jsonDic setObject:@"send_gps_data" forKey:@"action"];
    [jsonDic setObject:parametersDic forKey:@"parameters"];

    NSError *error = nil;
    NSData *json;

    if ([NSJSONSerialization isValidJSONObject:jsonDic]) {
        json = [NSJSONSerialization dataWithJSONObject:jsonDic options:NSJSONWritingPrettyPrinted error:&error];
        if (json != nil && error == nil) {
//            NSString *jsonString = [[NSString alloc] initWithData:json encoding:NSUTF8StringEncoding];
//            NSLog(@"JSON:\n%@", jsonString);
        }else{
            [delegate onLocationError:[ApplicationErrors createErrorInDomain:@"GeoLocationServer" code:1001 reason:@"Error: can't generate json from dic" description:@"Error: can't generate json from dic"]];
        }
    }else{
        [delegate onLocationError:[ApplicationErrors createErrorInDomain:@"GeoLocationServer" code:1001 reason:@"Error: json dic not valid." description:@"Error: json dic not valid."]];
    }
    return json;
}

- (void) locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    [self.locationManager stopUpdatingLocation];
    [self.locationManager stopUpdatingHeading];
    [delegate onLocationError:error];
}

- (BOOL) isLocationAvailable
{
    return [CLLocationManager locationServicesEnabled];
}

- (BOOL) isMagnitometerAvailable
{
    return [CLLocationManager headingAvailable];
}

- (NSString *)getUTCFormateDate:(NSDate*)localDate
{
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    NSTimeZone *timeZone = [NSTimeZone timeZoneWithName:@"UTC"];
    [dateFormatter setTimeZone:timeZone];
    [dateFormatter setDateFormat:@"ddMMyy"];
    NSString *dateString = [dateFormatter stringFromDate:localDate];
    return dateString;
}

- (NSString *)getUTCFormateTime:(NSDate*)localDate
{
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    NSTimeZone *timeZone = [NSTimeZone timeZoneWithName:@"UTC"];
    [dateFormatter setTimeZone:timeZone];
    [dateFormatter setDateFormat:@"HHmmss.SSS"];
    NSString *dateString = [dateFormatter stringFromDate:localDate];
    return dateString;
}

- (NSString *) convert:(double) coordinate
{
    if (coordinate < -180.0 || coordinate > 180.0) {
        return nil;
    }
    NSMutableString *str = [[NSMutableString alloc] init];
    if (coordinate < 0) {
        [str appendString:@"-"];
        coordinate = -coordinate;
    }
    int degrees = floor(coordinate);
    [str appendFormat:@"%d",degrees];
    coordinate -= degrees;
    coordinate *= 60.0;
    NSString *temp = [NSString stringWithFormat:@"%08.6f", coordinate];
    if(coordinate < 10){
        temp = [NSString stringWithFormat:@"0%f", coordinate];
    }
    NSString *fStr = [NSString stringWithFormat:@"%d%@", degrees, temp];
    return fStr;
}

@end
