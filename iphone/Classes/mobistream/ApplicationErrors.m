//
//  ApplicationErrors.m
//  MobiStream
//
//  Created by netris on 29.01.15.
//  Copyright (c) 2015 netris. All rights reserved.
//

#import "ApplicationErrors.h"

@implementation ApplicationErrors

//static NSString* errorDomain = @"myAppErrorDomain"; // домен, в котором произошла ошибка

+(NSError *)createErrorInDomain:(NSString *)domain code:(int)code reason:(NSString *)reason description:(NSString *)description
{
    NSArray *objArray = [NSArray arrayWithObjects:description, reason, nil];
    NSArray *keyArray = [NSArray arrayWithObjects:NSLocalizedDescriptionKey,NSLocalizedFailureReasonErrorKey, nil];
    NSDictionary *userInfo = [NSDictionary dictionaryWithObjects:objArray forKeys:keyArray];
    NSError* error = [NSError errorWithDomain:domain code:code userInfo:userInfo];
    return error;
}

@end
