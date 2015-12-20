//
//  DZRPlayer.h
//  Deezer
//
//  Created by GFaure on 29/04/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DZRModel.h"
#import "NSError+DZRPlayer.h"

@class DeezerConnect;
@class DZRPlayer;

#define DZR_PLAYER_STATE_AS_ENUM(s) DZRPlayerState##s,
#define DZR_PLAYER_STATE_AS_DISPATCH_TABLE(s) @ #s,
#define DZR_PLAYER_STATE(ENTRY)  \
    ENTRY(None)                  \
    ENTRY(Initializing)          \
    ENTRY(FetchingCurrentTrack)  \
    ENTRY(FetchingNextTrack)     \
    ENTRY(FetchingPreviousTrack) \
    ENTRY(LoadingTrack)          \
    ENTRY(Buffering)             \
    ENTRY(Playing)               \
    ENTRY(Paused)                \
    ENTRY(Stopped)

typedef enum {
    DZR_PLAYER_STATE(DZR_PLAYER_STATE_AS_ENUM)
} DZRPlayerState;

/*! Notification sent when the player changes track */
FOUNDATION_EXPORT NSString * const DZRAudioPlayerDidChangeTrackNotification;
/*! Notification sent when the player did stop playing the DZRPlayable */
FOUNDATION_EXPORT NSString * const DZRAudioPlayerDidStopPlayingNotification;
/*! Notification sent when the player was paused */
FOUNDATION_EXPORT NSString * const DZRTrackPlaybackDidPauseNotification;
/*! Notification sent when the player starts playing a DZRPlayable */
FOUNDATION_EXPORT NSString * const DZRTrackPlaybackDidStartPlayingNotification;
/*! Notification sent when the player seek inside da DZRTrack */
FOUNDATION_EXPORT NSString * const DZRTrackPlaybackDidSeekNotification;

typedef NS_ENUM(NSInteger, DZRPlayerNetworkType) {
    /*! Stream tracks ONLY with a WiFi connection */
    DZRPlayerNetworkTypeWIFIOnly,
    /*! Stream tracks on both WiFi and 3G/Edge connection. */
    DZRPlayerNetworkTypeWIFIAnd3G,
};

/*!
 
 */
@protocol DZRPlayerDelegate <NSObject>
@optional
- (void)player:(DZRPlayer*)player didBuffer:(long long)bufferedBytes outOf:(long long)totalBytes;
- (void)player:(DZRPlayer*)player didPlay:(long long)playedBytes outOf:(long long)totalBytes;
- (void)player:(DZRPlayer*)player didStartPlayingTrack:(DZRTrack*)track;
- (void)player:(DZRPlayer*)player didEncounterError:(NSError*)error;
- (void)playerDidPause:(DZRPlayer*)player;
@end

/*!
 */
@interface DZRPlayer : NSObject
@property (nonatomic, weak) id<DZRPlayerDelegate> delegate;

/// @name Initialization

/*!
 Initialize a DZRPlayer instance.
 
 !param connection A connection the player can use to verify the rights of the
   user.
 */
- (id)initWithConnection:(DeezerConnect*)connection;

/// @name Configuration

/*!
 Indicate if the player should take care of informing the MPNowPlayingInfoCenter
 of the current playing track.
 */
@property (nonatomic, assign) BOOL shouldUpdateNowPlayingInfo;

/// @name Playing
/*!
 Plays a DZRPlayable object.
 
 This is the entry point in a player. The caller gives to this method a Deezer
 model objects that is playable, like a DZRTrack, DZRAlbum, DZRRadio, DZRPlaylist...
 and the player will take care of fetching tracks information and play each tracks
 in its turn. You can control the playback of the tracks by sending the play, pause, 
 stop and next message on the player.
 
 !param playable the playable object.
 */
- (void)play:(id<DZRPlayable>)playable;

/// @name Player control

/*!
 Asks the player to pause the playing of the current track.
 */
- (void)pause;
/*!
 Asks the player to start or resume playing the current track.
 */
- (void)play;
/*!
 Asks the player to stop the playing of the current track.
 
 If the caller sends the play message later to this DZRPlayer instance, the
 player will requests the next track and start playing it.
 */
- (void)stop;
/*!
 Asks the player skip the rest of the current track.
 
 The player will stop the current track and automatically fetch the information
 of the next track from its DZRPlayable and start playing it.
 */
- (void)next;
/*!
 Asks the player to go back to the previous track.
 
 The player will stop the current track and automatically fetch the information
 of the previous track from the DZRPlayable and start playing it.
 */
- (void)previous;

/// @name Query status

/*!
 Tests if the player is currently playing.
 
 A player is playing is it is not stopped, paused or initializing. Notably, the
 player may be not effectively "playing" music, but actively fetching track
 information or buffering. It would be considered playing.
 */
- (BOOL)isPlaying;

/*!
 Tests if the player is capable of playing anything.
 
 At this point the player owns a DZRPlayable instance and is correctly initialized.
 
 Sending control messages before the player reports being ready is a no-op.
*/
- (BOOL)isReady;

/*!
 The DZRTrack currently played by the player.
 */
@property (nonatomic, readonly) DZRTrack *currentTrack;
/*!
 The currently paying DZRTrack's music lenght.
 */
@property (nonatomic, readonly) size_t currentTrackDuration;
/*!
 The type of network the player can operate on.
 
 This property tells the player on which type of network it is allowed to buffer
 tracks.
 */
@property (nonatomic, assign) DZRPlayerNetworkType networkType;
/*!
 The progress in the playback of the current playing DZRTrack.
 
 This is the percentage of the track aldready played. You can assign to this 
 property to seek inside the track.
 */
@property (nonatomic, assign) double progress;

/*!
 The bitrate of the current track.
 */
@property (nonatomic, readonly) double bitrate;

/*!
 The state the player is currently in.
 */
@property (nonatomic, readonly) DZRPlayerState state;

/*!
 
 */
@property (nonatomic, readonly) double bufferProgress;

@end
