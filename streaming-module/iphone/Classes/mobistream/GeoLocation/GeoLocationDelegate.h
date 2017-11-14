//
//  GeoLocationDelegate.h
//  MobiStream
//
//  Created by netris on 21.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol GeoLocationDelegate

@required

- (void) onLocationChangedJson:(NSString *) json;
- (void) onLocationChanged:(CLLocation *) location;
- (void) onLocationError:(NSError *)error;

@optional

@end