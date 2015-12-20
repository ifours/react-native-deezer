//
//  NSError+DZRPlayer.h
//  Deezer
//
//  Created by GFaure on 17/11/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import <Foundation/Foundation.h>

/*! Domain error for Player */
FOUNDATION_EXPORT NSString *const DZRPlayerErrorDomain;
typedef NS_ENUM(NSUInteger, DZRPlayerError) {
    /*! The player is unable to get the track's stream */
    DZRPlayerAPIStreamError,
    /*! The player internal audio processing encountered and error */
    DZRPlayerAudioError,
    /*! The player encounter an error while asking tracks from its current playable */
    DZRPlayerTrackQueueError,
    /*! The buffering of audio data from the network encountered some error */
    DZRPlayerBufferingError,
    /*! The player was restricted by Deezer. This generally mean that the user
     account is beeing used to play music on another device */
    DZRPlayerRestrictedError,
    /*! Previous was called on the player but the playable currently playing
     does not support two way skipping (no backward iterator, only forward) */
    DZRPlayerNotTwoWayPlayableError,
};
/*! Key to query the original error from the Error's userInfo when a player error is reported */
FOUNDATION_EXPORT NSString *const DZRPlayerErrorOriginalErrorKey;

@interface NSError (DZRPlayer)
+ (NSError*)trackQueueErrorWithOrigninalError:(NSError*)error;
+ (NSError*)restrictedError;
+ (NSError*)notTwoWayPlayableError;
@end
