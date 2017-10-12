//
//  GeoLocation.h
//  MobiStream
//
//  Created by netris on 20.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "GeoLocation.h"
#import "GeoLocationDelegate.h"
#import "ApplicationErrors.h"

@interface GeoLocationServer : NSObject <CLLocationManagerDelegate>


@property (strong, nonatomic) CLLocationManager *locationManager;

- (BOOL) isLocationAvailable;
- (void) stopUpdatingLocation;
- (void) startUpdatingLocation;
- (void) startupWithDistanceFilter:(CLLocationDistance)distFilter accuracy:(CLLocationAccuracy) accuracy withMac:(NSString *)mac;
+ (GeoLocationServer*) server;
- (void) setDelegate: (id) newDelegate;
@end
