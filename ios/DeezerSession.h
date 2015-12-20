#import <Foundation/Foundation.h>

#import "DeezerConnect.h"
#import "DZRRequestManager.h"
#import "DZRModel.h"
#import "DZRPlayer.h"

#import "RCTBridgeModule.h"
#import "RCTConvert.h"

#define kDeezerAppId @"YOUR_APPLICATION_ID"

@interface DeezerSession : NSObject <DeezerSessionDelegate>

@property (nonatomic, readonly) DeezerConnect* deezerConnect;
@property (nonatomic, strong) DZRObject *me;
@property (nonatomic, strong) DZRRequestManager *manager;
@property (nonatomic, strong) DZRRequestManager *illustrationManager;
@property (nonatomic, strong) DZRUser *currentUser;
@property (nonatomic, strong) DZRPlayer *player;
@property (nonatomic, strong) RCTResponseSenderBlock initCallback;

+ (DeezerSession*)sharedSession;

#pragma mark - RTC methods
- (void)getTracksWithResolver:(RCTPromiseResolveBlock)resolve andRejecter:(RCTPromiseRejectBlock)reject;
- (void)getPlaylistsWithResolver:(RCTPromiseResolveBlock)resolve andRejecter:(RCTPromiseRejectBlock)reject;
- (void)getPlaylistTracks:(NSString *)identifier withResolver:(RCTPromiseResolveBlock)resolve andRejecter:(RCTPromiseRejectBlock)reject;

#pragma mark - Connection
- (void)connectToDeezerWithPermissions:(NSArray*)permissionsArray;
- (void)disconnect;
- (BOOL)isSessionValid;

- (void)getCurrentUserWithCallback:(void (^)())callback;

@end



