//
//  DZRPlaylist.h
//  Deezer
//
//  Created by GFaure on 24/04/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import "DZRObject.h"

/*!
 A class representing a playlist in Deezer's model.
 
 Please refer to the documentation of [Deezer's web services for artists](http://developers.deezer.com/api/playlist). for
 more information.
 */
@interface DZRPlaylist : DZRObject <DZRPlayable, DZRRatable, DZRCommentable, DZRRadioStreamable, DZRDeletable>

/*!
 The chunk size the playlists tracks are retrieved.

 When the SDK retrieve the tracks of a playlist, the result is paginated. This property indicates
 the size of the pages or chunks. It is possible to change this size with !ref setTrackListChunkSize:

 !see +[DZRPlaylist setTrackListChunkSize:]
 */
+ (NSUInteger)trackListChunkSize;
/*!
 Changes the chunk size the playlists tracks are retrieved.

 !see +[DZRPlaylist trackListChunkSize:]
 */
+ (void)setTrackListChunkSize:(NSUInteger)size;

- (void)setValues:(NSDictionary*)values withRequestManager:(DZRRequestManager*)manager callback:(void(^)(NSError *error))callback;
/*!
 Add some DZRTrack to the playlist.

 !param tracks An array of DZRTrack the caller wants addeded to the playlist.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback A error callback. If the model detects an error, it will call the
   provided callback with the specific error.
 */
- (void)addTracks:(NSArray*)tracks withRequestManager:(DZRRequestManager*)manager callback:(void(^)(NSError *error))callback;
/*!
 Delete some DZRTrack from the playlist.
 
 !param tracks An array of DZRTrack the caller wants deleted from the playlist.
 !param manager A request manager the model will use to schedule network requests.
    If nil, the default request manager is used.
 !param callback A error callback. If the model detects an error, it will call the
    provided callback with the specific error.
 */
- (void)deleteTracks:(NSArray*)tracks withRequestManager:(DZRRequestManager*)manager callback:(void(^)(NSError *error))callback;
/*!
 Order some DZRTrack to the playlist.
 
 !param tracks An array of DZRTrack that indicates the order the caller wants the tracks to be in
   for this playlist.
 !param manager A request manager the model will use to schedule network requests.
    If nil, the default request manager is used.
 !param callback A error callback. If the model detects an error, it will call the
    provided callback with the specific error.
 */
- (void)orderTracks:(NSArray*)tracks withRequestManager:(DZRRequestManager*)manager callback:(void(^)(NSError *error))callback;
@end
