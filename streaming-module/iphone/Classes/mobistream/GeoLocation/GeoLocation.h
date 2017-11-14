//
//  GeoLocation.h
//  MobiStream
//
//  Created by netris on 21.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface GeoLocation : NSObject

@property (nonatomic) CLLocationDegrees latitude;
@property (nonatomic) CLLocationDegrees longitude;
@property (strong, nonatomic) NSString *latitudeHemisphere;
@property (strong, nonatomic) NSString *longitudeHemisphere;
@property (strong, nonatomic) NSDate *date;
@property (nonatomic) CLLocationSpeed speed;
@property (nonatomic) CLLocationDirection course;
@property (nonatomic) CLLocationAccuracy horizontalAccuracy;
@property (nonatomic) CLLocationAccuracy verticalAccuracy;

@end
