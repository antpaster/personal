#import "RuNetrisStreamingViewProxy.h"
#import "RuNetrisStreamingView.h"

@implementation RuNetrisStreamingViewProxy

#pragma mark Events

MAKE_SYSTEM_STR(EVENT_TYPE_ORIENTATION_CHANGED, @"orientationChanged");

MAKE_SYSTEM_STR(EVENT_TYPE_STREAM_STARTED, @"streamStarted");
MAKE_SYSTEM_STR(EVENT_TYPE_STREAM_STOPPED, @"streamStopped");

MAKE_SYSTEM_STR(EVENT_TYPE_ERROR_CAMERA, @"errorCamera");
MAKE_SYSTEM_STR(EVENT_TYPE_ERROR_SERVER, @"errorServer");
MAKE_SYSTEM_STR(EVENT_TYPE_ERROR_NETWORK, @"errorNetwork");

#pragma mark API exposed to Javascript

- (void)setURL:(id)args
{
  NSLog(@"setURL");
}

- (void)setURLAndStart:(id)args
{
  NSLog(@"setURLAndStart");
}

- (void)start:(id)args
{
  NSLog(@"start");
}

- (void)stop:(id)args
{
  NSLog(@"stop");
}

- (NSArray *)getCameras:(id)args
{
  NSArray *cameras = [NSArray array];
    
  return cameras;
}

- (void)useCamera:(id)camera
{
  NSLog(@"useCamera");
}

- (void)useTorch:(BOOL)value
{
  NSLog(@"useTorch: %@", (value ? @"Yes" : @"No"));
}

- (BOOL)torchIsOn
{
	return NO;
}

- (BOOL)isStarted
{
	return YES;
}

- (id)activeCamera
{
	return nil;
}

#pragma mark Listener Notifications

-(void)_listenerAdded:(NSString *)type count:(int)count
{
	NSLog(@"A listener for the \"%@\" event is added", type);
}

-(void)_listenerRemoved:(NSString *)type count:(int)count
{
	NSLog(@"A listener for the \"%@\" event is removed", type);
}

@end
