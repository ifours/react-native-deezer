//
//  DZRUser.h
//  Deezer
//
//  Created by GFaure on 24/04/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import "DZRObject.h"

@class DZRAlbum;
@class DZRArtist;
@class DZRPlaylist;
@class DZRRadio;
@class DZRTrack;

@class DZRRequestManager;

/*!
 A class representing a user in Deezer's model.
 
 Please refer to the documentation of [Deezer's web services for users](http://developers.deezer.com/api/user). for
 more information.
 */
@interface DZRUser : DZRObject <DZRIllustratable, DZRFlowable>

/// @name Manage user's favorite

/*!
 Set a model objects as user's favorite.
 
 The caller can pass in any model object. If it can be marked as favorite for
 the user, the model will set it as favorite. Otherwise, an error will be passed
 by to the caller through the provided callback.
 
 !see deleteFavorite:withRequestManager:callback:
 
 !param object The model object to be set as user's favorite.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)addFavorite:(DZRObject*)object
 withRequestManager:(DZRRequestManager*)manager
           callback:(void(^)(NSError *error))callback;
/*!
 Remove an objects from user's favorite.
 
 !see addFavorite:withRequestManager:callback:
 
 !param object The model object to remove from user's favorite.
 !param manager A request manager the model will use to schedule network requests.
    If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)deleteFavorite:(DZRObject*)object
    withRequestManager:(DZRRequestManager*)manager
              callback:(void(^)(NSError *error))callback;

/// @name Manage user's albums

/*!
 Add a DZRAlbum as the user's favorite.
 
 This is a specialized version of addFavorite:withRequestManager:callback: for 
 albums.
 
 !see deleteFavoriteAlbum:withRequestManager:callback:, addFavorite:withRequestManager:callback:
 
 !param album The DZRAlbum to be set as user's favorite.
 !param manager A request manager the model will use to schedule network requests.
    If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)addFavoriteAlbum:(DZRAlbum*)album
      withRequestManager:(DZRRequestManager*)manager
                callback:(void(^)(NSError *error))callback;
/*!
 Remove a DZRAlbum from the user's favorite.
 
 This is a specialized version of deleteFavorite:withRequestManager:callback: for
 albums.
 
 !see addFavoriteAlbum:withRequestManager:callback:, deleteFavorite:withRequestManager:callback:
 
 !param album The DZRAlbum to remove from user's favorite.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */

- (void)deleteFavoriteAlbum:(DZRAlbum*)album
         withRequestManager:(DZRRequestManager*)manager
                   callback:(void(^)(NSError *error))callback;

/// @name Manage user's artists

/*!
 Add a DZRArtist as the user's favorite.
 
 This is a specialized version of addFavorite:withRequestManager:callback: for
 artist.
 
 !see deleteFavoriteArtist:withRequestManager:callback:, addFavorite:withRequestManager:callback:
 
 !param artist The DZRArtist to be set as user's favorite.
 !param manager A request manager the model will use to schedule network requests.
 If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)addFavoriteArtist:(DZRArtist*)artist
       withRequestManager:(DZRRequestManager*)manager
                 callback:(void(^)(NSError *error))callback;
/*!
 Remove a DZRArtist remove the user's favorite.
 
 This is a specialized version of deleteFavorite:withRequestManager:callback: for
 artist.
 
 !see addFavoriteArtist:withRequestManager:callback:, deleteFavorite:withRequestManager:callback:
 
 !param artist The DZRArtist to remove from user's favorite.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)deleteFavoriteArtist:(DZRArtist*)artist
          withRequestManager:(DZRRequestManager*)manager
                    callback:(void(^)(NSError *error))callback;

/// @name Manage user's playlists

/*!
 Add a DZRPlaylist as the user's favorite.
 
 This is a specialized version of addFavorite:withRequestManager:callback: for
 playlists.
 
 !see deleteFavoritePlaylist:withRequestManager:callback:, addFavorite:withRequestManager:callback:
 
 !param playlist The DZRPlaylist to be set as user's favorite.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)addFavoritePlaylist:(DZRPlaylist*)playlist
         withRequestManager:(DZRRequestManager*)manager
                   callback:(void(^)(NSError *error))callback;
/*!
 Remove a DZRPlaylist from the user's favorite.
 
 This is a specialized version of deleteFavorite:withRequestManager:callback: for
 playlists.
 
 !see addFavoritePlaylist:withRequestManager:callback:, deleteFavorite:withRequestManager:callback:
 
 !param playlist The DZRPlaylist to remove from user's favorite.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)deleteFavoritePlaylist:(DZRPlaylist*)playlist
            withRequestManager:(DZRRequestManager*)manager
                      callback:(void(^)(NSError *error))callback;

/*!
 Create a new DZRPlaylist for this user.
 
 After creation, the new playlist will be handed to the caller through
 the provided callback.
 
 !param title A string to set as the title of the new playlist.
 !param tracks An array of DZRTrack to add to the new playlist upon creation.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)createPlaylist:(NSString*)title
      containingTracks:(NSArray*)tracks
    withRequestManager:(DZRRequestManager*)manager
              callback:(void(^)(DZRPlaylist *playlist, NSError *error))callback;

/// @name Manage user's radios

/*!
 Add a DZRRadio as the user's favorite.
 
 This is a specialized version of addFavorite:withRequestManager:callback: for
 radios.
 
 !see deleteFavoriteRadio:withRequestManager:callback:, addFavorite:withRequestManager:callback:
 
 !param radio The DZRRadio to be set as user's favorite.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)addFavoriteRadio:(DZRRadio*)radio
      withRequestManager:(DZRRequestManager*)manager
                callback:(void(^)(NSError *error))callback;
/*!
 Remove a DZRRadio from the user's favorite.
 
 This is a specialized version of deleteFavorite:withRequestManager:callback: for
 radios.
 
 !see addFavoriteRadio:withRequestManager:callback:, deleteFavorite:withRequestManager:callback:
 
 !param radio The DZRRadio to remove from user's favorite.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)deleteFavoriteRadio:(DZRRadio*)radio
         withRequestManager:(DZRRequestManager*)manager
                   callback:(void(^)(NSError *error))callback;

/// @name Manage user's tracks

/*!
 Add a DZRTrack as the user's favorite.
 
 This is a specialized version of addFavorite:withRequestManager:callback: for
 tracks.
 
 !see deleteFavoriteTrack:withRequestManager:callback:, addFavorite:withRequestManager:callback:
 
 !param track The DZRTrack to be set as user's favorite.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)addFavoriteTrack:(DZRTrack*)track
      withRequestManager:(DZRRequestManager*)manager
                callback:(void(^)(NSError *error))callback;
/*!
 Remove a DZRTrack from the user's favorite.
 
 This is a specialized version of deleteFavorite:withRequestManager:callback: for
 tracks.
 
 !see addFavoriteTrack:withRequestManager:callback:, deleteFavorite:withRequestManager:callback:
 
 !param track The DZRTrack to remove from user's favorite.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call if an error occured.
 */
- (void)deleteFavoriteTrack:(DZRTrack*)track
         withRequestManager:(DZRRequestManager*)manager
                   callback:(void(^)(NSError *error))callback;
@end
