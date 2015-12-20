#import "DZRRequestManager.h"
#import "DZRPlayer.h"

#import "RCTBridge.h"

@interface DeezerPlayer : NSObject <DZRPlayerDelegate>

@property (nonatomic, readonly) DZRPlayer *player;
@property (nonatomic, strong) DZRRequestManager *manager;
@property (nonatomic, strong) RCTBridge *bridge;
@property (nonatomic, strong) id<DZRCancelable> trackRequest;

+ (DeezerPlayer*)sharedPlayer;

#pragma mark - Player methods
- (void)playTrackWithIdentifier:(NSString*)identifier;
- (void)playTrackWithIdentifier:(NSString*)identifier
                   withResolver:(RCTPromiseResolveBlock)resolve
                    andRejecter:(RCTPromiseRejectBlock)reject;
- (void)pause;
- (void)play;
- (void)nextTrack;
- (void)previosTrack;
- (BOOL)isPlaying;
@end
