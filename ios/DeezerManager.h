#import "DZRPlayer.h"

#import "RCTBridge.h"
#import "RCTBridgeModule.h"
#import "RCTEventDispatcher.h"

@interface DeezerManager : NSObject <RCTBridgeModule, DZRPlayerDelegate>
+ (RCTBridge*)globalBridge;
@end
