#import "TiViewProxy.h"

@interface RuNetrisStreamingViewProxy : TiViewProxy {
    
}

@property(readonly) BOOL torchIsOn;
@property(readonly) BOOL isStarted;
@property(readonly, copy) id activeCamera;

@end
