//
//  ApplicationErrors.h
//  MobiStream
//
//  Created by netris on 29.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ApplicationErrors : NSObject

+(NSError *)createErrorInDomain:(NSString *)domain code:(int)code reason:(NSString *)reason description:(NSString *)description;

@end
