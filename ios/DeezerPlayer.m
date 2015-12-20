#import "DeezerPlayer.h"
#import "DeezerSession.h"
#import "DeezerManager.h"

#import "RCTBridge.h"
#import "RCTEventDispatcher.h"

@implementation DeezerPlayer

#pragma mark - NSObject

- (id)init {
  if (self = [super init]) {
    _player = [[DZRPlayer alloc] initWithConnection:[DeezerSession sharedSession].deezerConnect];
    _player.delegate = self;
    _player.shouldUpdateNowPlayingInfo = YES;

    _manager = [[DZRRequestManager defaultManager] subManager];
    _bridge = [DeezerManager globalBridge];
    
    
    [[UIApplication sharedApplication] beginReceivingRemoteControlEvents];
  }
  return self;
}

#pragma mark - Player methods

- (void)playTrackWithIdentifier:(NSString*)identifier {
  [DZRTrack objectWithIdentifier:identifier requestManager:_manager callback:^(DZRTrack *track, NSError *error) {
    [_player play:track];
  }];
}

- (void)playTrackWithIdentifier:(NSString*)identifier
                   withResolver:(RCTPromiseResolveBlock)resolve
                    andRejecter:(RCTPromiseRejectBlock)reject {
  
  [self.trackRequest cancel];
  [self.player stop];

  self.trackRequest = [DZRTrack objectWithIdentifier:identifier requestManager:_manager callback:^(DZRTrack *track, NSError *error) {
    [_player play];
    [_player play:track];
    resolve(@YES);
  }];
}

- (void)pause {
  [_player pause];
  [_bridge.eventDispatcher sendDeviceEventWithName:@"player.didPause" body:nil];
}

- (void)play {
  [_player play];
  [_bridge.eventDispatcher sendDeviceEventWithName:@"player.playAfterPause" body:nil];
}

- (void)nextTrack {
  [_bridge.eventDispatcher sendDeviceEventWithName:@"player.nextTrack" body:nil];
}

- (void)previosTrack {
  [_bridge.eventDispatcher sendDeviceEventWithName:@"player.previosTrack" body:nil];
}

- (BOOL)isPlaying {
  return [_player isPlaying];
}

#pragma mark DZRPlayerDelegate

- (void)player:(DZRPlayer *)player didBuffer:(long long)bufferedBytes outOf:(long long)totalBytes {
  float progress = 0.0;
  if (totalBytes != 0) {
    progress = (double)bufferedBytes / (double)totalBytes;
  }
  [_bridge.eventDispatcher sendDeviceEventWithName:@"player.didBuffer" body:[NSNumber numberWithFloat:progress]];
}

- (void)player:(DZRPlayer *)player didPlay:(long long)playedBytes outOf:(long long)totalBytes {
  float progress = 0.0;
  if (totalBytes != 0) {
    progress = (double)playedBytes / (double)totalBytes;
  }
  [_bridge.eventDispatcher sendDeviceEventWithName:@"player.didPlay" body:[NSNumber numberWithFloat:progress]];
}

- (void)player:(DZRPlayer *)player didStartPlayingTrack:(DZRTrack *)track {
  [_bridge.eventDispatcher sendDeviceEventWithName:@"player.didStartPlay" body:nil];
}

- (void)playerDidPause:(DZRPlayer *)player {
  [_bridge.eventDispatcher sendDeviceEventWithName:@"player.didPause" body:nil];
}

#pragma mark - Singleton methods

static DeezerPlayer* _sharedPlayer = nil;

+ (DeezerPlayer*)sharedPlayer {
  if (_sharedPlayer == nil) {
    _sharedPlayer = [[super alloc] init];
  }
  _sharedPlayer.bridge = [DeezerManager globalBridge];
  return _sharedPlayer;
}

@end