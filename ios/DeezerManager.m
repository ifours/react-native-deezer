#import "DeezerManager.h"

#import "DeezerSession.h"
#import "DeezerPlayer.h"

@implementation DeezerManager
@synthesize bridge = _bridge;

RCT_EXPORT_MODULE();

RCT_EXPORT_METHOD(connect:(RCTResponseSenderBlock)callback) {
   _globalBridge = _bridge;

  NSMutableArray* permissionsArray = [NSMutableArray array];
  [permissionsArray addObject:DeezerConnectPermissionBasicAccess];
  [permissionsArray addObject:DeezerConnectPermissionListeningHistory];
  
  [DeezerSession sharedSession].initCallback = callback;
  dispatch_async(dispatch_get_main_queue(), ^{
    [[DeezerSession sharedSession] connectToDeezerWithPermissions:permissionsArray];
  });
}

RCT_EXPORT_METHOD(isSessionValid:(RCTResponseSenderBlock)callback) {
  _globalBridge = _bridge;

  [[DeezerSession sharedSession] isSessionValid] ? [[DeezerSession sharedSession] getCurrentUserWithCallback:^() {
    callback(@[@YES]);
  }] : callback(@[@NO]);
}

RCT_REMAP_METHOD(getFavoritesTracks,
                 resolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject) {
  [[DeezerSession sharedSession] getTracksWithResolver:resolve andRejecter:reject];
}

RCT_EXPORT_METHOD(getPlaylists:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  [[DeezerSession sharedSession] getPlaylistsWithResolver:resolve andRejecter:reject];
}

RCT_EXPORT_METHOD(getPlaylistTracks:(NSString *)identifier
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  [[DeezerSession sharedSession] getPlaylistTracks:identifier withResolver:resolve andRejecter:reject];
}

RCT_EXPORT_METHOD(playTrack:(NSString *)identifier
                   resolver:(RCTPromiseResolveBlock)resolve
                   rejecter:(RCTPromiseRejectBlock)reject) {
  [[DeezerPlayer sharedPlayer] playTrackWithIdentifier:identifier withResolver:resolve andRejecter:reject];
}


RCT_EXPORT_METHOD(pause) {
  [[DeezerPlayer sharedPlayer] pause];
}

RCT_EXPORT_METHOD(play) {
  [[DeezerPlayer sharedPlayer] play];
}

#pragma mark - Singleton methods

static RCTBridge* _globalBridge = nil;

+ (RCTBridge*)globalBridge {
  return _globalBridge;
}

@end
