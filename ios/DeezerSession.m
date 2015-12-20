#import "DeezerSession.h"
#import "DZRModel.h"
#import "DZRRequestManager.h"

#define DEEZER_TOKEN_KEY @"DeezerTokenKey"
#define DEEZER_EXPIRATION_DATE_KEY @"DeezerExpirationDateKey"
#define DEEZER_USER_ID_KEY @"DeezerUserId"

@implementation DeezerSession

@synthesize deezerConnect = _deezerConnect;
@synthesize me = _me;

#pragma mark - NSObject

- (id)init {
  if (self = [super init]) {
    _deezerConnect = [[DeezerConnect alloc] initWithAppId:kDeezerAppId andDelegate:self];
    [[DZRRequestManager defaultManager] setDzrConnect:_deezerConnect];
    [self retrieveTokenAndExpirationDate];
    
    self.manager = [[DZRRequestManager defaultManager] subManager];

  }
  return self;
}

#pragma mark - Connection

- (void)connectToDeezerWithPermissions:(NSArray*)permissionsArray {
  [_deezerConnect authorize:permissionsArray];
}

- (void)disconnect {
  [_deezerConnect logout];
}

- (void)logOut
{
  [self clearTokenAndExpirationDate];
  [self disconnect];
}

- (BOOL)isSessionValid {
  return [_deezerConnect isSessionValid];
}

#pragma mark - RTC methods

- (void)getTracksWithResolver:(RCTPromiseResolveBlock)resolve andRejecter:(RCTPromiseRejectBlock)reject {
  [_currentUser valueForKey:@"tracks"
         withRequestManager:[DZRRequestManager defaultManager]
                   callback:^(DZRObjectList *list, NSError *error) {
    NSInteger count = [list count];

    [list allObjectsWithManager:[DZRRequestManager defaultManager]
                       callback:^(NSArray *tracks, NSError *error) {
      NSMutableArray *trackInfoArray = [[NSMutableArray alloc] init];
      
      [tracks enumerateObjectsUsingBlock:^(DZRTrack * _Nonnull track, NSUInteger idx, BOOL * _Nonnull stop) {
        [track valuesForKeyPaths:@[@"id", @"title", @"album.cover", @"album.title", @"artist.name", @"duration"]
              withRequestManager:[DZRRequestManager defaultManager]
                        callback:^(NSDictionary *trackInfo, NSError *error) {
          [trackInfoArray addObject:trackInfo];
          
          if (count == idx + 1) {
            resolve(trackInfoArray);
          }
        }];
      }];
    }];
  }];
}

- (void)getPlaylistTracks:(NSString *)identifier withResolver:(RCTPromiseResolveBlock)resolve andRejecter:(RCTPromiseRejectBlock)reject {
  
  [DZRPlaylist objectWithIdentifier:identifier
                     requestManager:_manager
                           callback:^(DZRPlaylist *playlist, NSError *error) {
                             
    [playlist valueForKey:@"tracks"
       withRequestManager:[DZRRequestManager defaultManager]
                 callback:^(DZRObjectList *list, NSError *error) {
                   
      NSInteger count = [list count];
                   
      [list allObjectsWithManager:[DZRRequestManager defaultManager]
                         callback:^(NSArray *tracks, NSError *error) {
                           
        NSMutableArray *trackInfoArray = [[NSMutableArray alloc] init];
                           
        [tracks enumerateObjectsUsingBlock:^(DZRTrack * _Nonnull track, NSUInteger idx, BOOL * _Nonnull stop) {
          
          [track valuesForKeyPaths:@[@"id", @"title", @"album.cover", @"album.title", @"artist.name", @"duration"]
                withRequestManager:[DZRRequestManager defaultManager]
                          callback:^(NSDictionary *trackInfo, NSError *error) {
                            
            [trackInfoArray addObject:trackInfo];
                            
            if (count == idx + 1) {
              resolve(trackInfoArray);
            }
          }];
        }];
      }];
    }];
  }];
}

- (void)getPlaylistsWithResolver:(RCTPromiseResolveBlock)resolve andRejecter:(RCTPromiseRejectBlock)reject {
  [_currentUser valueForKey:@"playlists" withRequestManager:_manager callback:^(DZRObjectList *list, NSError *error) {
    NSInteger count = [list count];
    
    [list allObjectsWithManager:_manager callback:^(NSArray *playlists, NSError *error) {
      NSMutableArray *playlistInfoArray = [[NSMutableArray alloc] init];
      
      [playlists enumerateObjectsUsingBlock:^(DZRPlaylist * _Nonnull playlist, NSUInteger idx, BOOL * _Nonnull stop) {
        [playlist valuesForKeyPaths:@[@"id", @"title", @"description"] withRequestManager:_manager callback:^(NSDictionary *playlistInfo, NSError *error) {
          
          [playlistInfoArray addObject:playlistInfo];
          
          if (count == idx + 1) {
            resolve(playlistInfoArray);
          }
        }];
      }];
    }];
  }];
}

- (void)getCurrentUserWithCallback:(void (^)())callback {
  [DZRUser objectWithIdentifier:@"me" requestManager:[DZRRequestManager defaultManager] callback:^(DZRUser *currentUser, NSError *error) {
    _currentUser = currentUser;
    callback();
  }];
}

#pragma mark - DeezerSessionDelegate

- (void)deezerDidLogin {
  NSLog(@"Deezer did login");
  
  [self saveToken:[_deezerConnect accessToken] andExpirationDate:[_deezerConnect expirationDate] forUserId:[_deezerConnect userId]];
  [self getCurrentUserWithCallback:^() {
    _initCallback(@[@YES]);
  }];
}

- (void)deezerDidNotLogin:(BOOL)cancelled {
  NSLog(@"Deezer Did not login : %@", cancelled ? @"Cancelled" : @"Not Cancelled");
   _initCallback(@[@"Deezer Did not login : %@", cancelled ? @"Cancelled" : @"Not Cancelled"]);
}

- (void)deezerDidLogout {
  NSLog(@"Deezer Did logout");
   _initCallback(@[@"Deezer Did logout"]);
}

#pragma mark - Token
// The token needs to be saved on the device
- (void)retrieveTokenAndExpirationDate {
  NSUserDefaults* standardUserDefaults = [NSUserDefaults standardUserDefaults];
  [_deezerConnect setAccessToken:[standardUserDefaults objectForKey:DEEZER_TOKEN_KEY]];
  [_deezerConnect setExpirationDate:[standardUserDefaults objectForKey:DEEZER_EXPIRATION_DATE_KEY]];
  [_deezerConnect setUserId:[standardUserDefaults objectForKey:DEEZER_USER_ID_KEY]];
}

- (void)saveToken:(NSString*)token andExpirationDate:(NSDate*)expirationDate forUserId:(NSString*)userId {
  NSUserDefaults* standardUserDefaults = [NSUserDefaults standardUserDefaults];
  [standardUserDefaults setObject:token forKey:DEEZER_TOKEN_KEY];
  [standardUserDefaults setObject:expirationDate forKey:DEEZER_EXPIRATION_DATE_KEY];
  [standardUserDefaults setObject:userId forKey:DEEZER_USER_ID_KEY];
  [standardUserDefaults synchronize];
}

- (void)clearTokenAndExpirationDate {
  NSUserDefaults* standardUserDefaults = [NSUserDefaults standardUserDefaults];
  [standardUserDefaults removeObjectForKey:DEEZER_TOKEN_KEY];
  [standardUserDefaults removeObjectForKey:DEEZER_EXPIRATION_DATE_KEY];
  [standardUserDefaults removeObjectForKey:DEEZER_USER_ID_KEY];
  [standardUserDefaults synchronize];
}


#pragma mark - Singleton methods

static DeezerSession* _sharedSessionManager = nil;

+ (DeezerSession*)sharedSession {
  if (_sharedSessionManager == nil) {
    _sharedSessionManager = [[super alloc] init];
  }
  return _sharedSessionManager;
}

@end
