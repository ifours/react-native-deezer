//
//  DZRObject.h
//  dsearch
//
//  Created by guillaume faure on 15/01/2014.
//  Copyright (c) 2014 guillaume faure. All rights reserved.
//

#import <Foundation/Foundation.h>
@class DZRRequestManager;
@class DZRNetworkRequest;
@class DZRTrack;
@class DZRComment;
@class DZRObjectList;
@class DZRManagedRadio;
@class UIImage;

@protocol DZRCancelable;

/*!
 Indicate the type of DZRObject you want to search.

 !see +[DZRObject searchFor:withQuery:requestManager:callback:]
 */
typedef NS_ENUM(NSUInteger, DZRSearchType) {
    /*! Search for tracks */
    DZRSearchTypeTrack,
    /*! Search for artists */
    DZRSearchTypeArtist,
    /*! Search for albums */
    DZRSearchTypeAlbum,
    /*! Search for users */
    DZRSearchTypeUser,
    /*! Ask for autocompletion results, not implemented yet */
    DZRSearchTypeAutocomplete,
};

typedef void (^DZRTrackFetchingCallback)(DZRTrack*, NSError*);

/*!
 Used by the DZRPlayer to get the tracks to play.

 Whenever the player needs a track to play (when the player starts
 or when the player finished a track an need the next one) it will requests
 a new one from the DZRPlayableIterator. The DZRPlayableIterator is given to
 the payer by a DZRPlayable.
 */
@protocol DZRPlayableIterator
- (void)currentWithRequestManager:(DZRRequestManager *)requestManager callback:(DZRTrackFetchingCallback)callback;
- (void)nextWithRequestManager:(DZRRequestManager *)requestManager callback:(DZRTrackFetchingCallback)callback;
@end

@protocol DZRPlayableRandomAccessIterator <DZRPlayableIterator>
- (void)trackAtIndex:(NSUInteger)index
    withRequestManager:(DZRRequestManager *)manager
              callback:(DZRTrackFetchingCallback)callback;
- (void)previousFrom:(DZRTrack *)track
    withRequestManager:(DZRRequestManager *)manager
              callback:(DZRTrackFetchingCallback)callback;
- (void)nextFrom:(DZRTrack *)track
    withRequestManager:(DZRRequestManager *)manager
              callback:(DZRTrackFetchingCallback)callback;
- (void)previousWithRequestManager:(DZRRequestManager *)requestManager callback:(DZRTrackFetchingCallback)callback;
@end

/*!
 Marks a object as playable.

 Playable objects can be given to a DZRPlayer instance by sending the
 -[DZRPlayer play:] message.
 */
@protocol DZRPlayable <NSObject>
- (NSString*)identifier;
/*!
 Hand over a track iterator which itself will provide the tracks of the playable object
 to a DZRPlayer.
 */
- (id<DZRPlayableIterator>)iterator;
@end

/*!
 Marks the object as illustratable.

 Illustratable objects can provide an UIImage.
 */
@protocol DZRIllustratable <NSObject>
/*!
 Request the UIImage illustrating the object.

 !param manager A request manager the model will use to schedule the request.
 !param callback The callback you want the model to call when it have the
      requested UIImage.

 @result A cancelable representing the request so the caller can cancel the
    request.
 */
- (id<DZRCancelable>)illustrationWithRequestManager:(DZRRequestManager*)manager
                                           callback:(void (^)(UIImage*, NSError*))callback;
- (id<DZRCancelable>)thumbnailIllustrationWithRequestManager:(DZRRequestManager*)manager
                                                    callback:(void (^)(UIImage*, NSError*))callback;
- (id<DZRCancelable>)heighDefinitionIllustrationWithRequestManager:(DZRRequestManager*)manager
                                                          callback:(void (^)(UIImage*,
                                                                             NSError*))callback;
@end

/*!
 Marks the object as deletable.
 */
@protocol DZRDeletable <NSObject>
/*!
 Ask the model to delete this object.

 The logged in user need to have the necessary rights in order to do so.

 !param manager A request manager the model will use to schedule the request.
 !param callback The callback you want the model to call if an error occur.
 */
- (void)deleteObjectWithRequestManager:(DZRRequestManager*)manager
                              callback:(void (^)(NSError* error))callback;
@end

/*!
 Marks the object as ratable.
 */
@protocol DZRRatable <NSObject>
/*!
 Assign a note to the object.

 The logged in user need to have the necessary rights in order to do so.

 !param note An integer between 0 and 5 providing the note to assign to this object.
 !param manager A request manager the model will use to schedule the request.
 !param callback The callback you want the model to call if an error occur.
 */
- (void)rateObject:(NSUInteger)note
    withRequestManager:(DZRRequestManager*)manager
              callback:(void (^)(NSError* error))callback;
@end

/*!
 Marks the object as commentable.
 */
@protocol DZRCommentable <NSObject>
/*!
 Posts a comment to the object.

 The logged in user need to have the necessary rights in order to do so.

 !param text The text to post as comment.
 !param manager A request manager the model will use to schedule the request.
 !param callback The callback you want the model to call if an error occur.
 */
- (void)postComment:(NSString*)text
    withRequestManager:(DZRRequestManager*)manager
              callback:(void (^)(DZRComment* comment, NSError* error))callback;
@end

/*!
 Marks the object as flowable.

 Only DZRUser objects are flowable. This means that the application can request the flow of the
 users.
 */
@protocol DZRFlowable <NSObject>
/*!
 Request the radio managing the user's Flow.

 !param manager A request manager the model will use to schedule the request.
 !param callback The callback you want the model to call handing you the user's Flow radio.
 */
- (void)flowRadioWithRequestManager:(DZRRequestManager*)manager
                           callback:(void (^)(DZRManagedRadio* radio, NSError* error))callback;
@end

/*!
 Marks the object as streamable.

 Streamable objects can provide an infinite stream of DZRtrack.
 */
@protocol DZRRadioStreamable <NSObject>
/*!
 Request the radio managing the track stream of this object.

 !param manager A request manager the model will use to schedule the request.
 !param callback The callback you want the model to call handing you the object's tracks stream.
 */
- (void)radioWithRequestManager:(DZRRequestManager*)manager
                       callback:(void (^)(DZRManagedRadio* radio, NSError* error))callback;
@end

/*!
 Root of the Deezer's SDK model.

 Most of the behavious of the model is defined in this class. The model
 is designed to be similar to an asynchronous KVC.

 Errors are reported by the model in the domain `DZRModelErrorDomain` and the
 error codes are described by DZRModelError.
 */
@interface DZRObject : NSObject <NSCopying>

/*!
 Identifier of the DZRObject.

 Every DZRObject have an identifier execept for some ghost objects.
 */
@property (nonatomic, readonly) NSString* identifier;

/// @name Entry points

/*!
 Search for `DZRObject`.

 !param type Select the type of `DZRObject` you are searching for.
 !param query The query string you want to match
 !param manager A request manager the model will use to schedule the request.
 !param callback The callback you want the model to call when it have the
      results of the search.
 */
+ (void)searchFor:(DZRSearchType)type
         withQuery:(NSString*)query
    requestManager:(DZRRequestManager*)manager
          callback:(void (^)(DZRObjectList*, NSError*))callback;

/*!
 Allow the query of an object by type and identifier.

 !param identifier The object's identifier you want.
 !param manager A request manager the model will use to schedule the request.
 !param callback The callback you want the model to call when it have the
      results of the search.

 You should not call this method directly on the DZRObject class but on one
 of its concrete subclass (e.g. DZRUser, DZRTrack, DZRArtist, ...)
 */
+ (DZRNetworkRequest*)objectWithIdentifier:(NSString*)identifier
                            requestManager:(DZRRequestManager*)manager
                                  callback:(void (^)(id object, NSError* error))callback;

/// @name Async KVC keys

/*!
 The information keys the object supports.

 These keys are more or less the sames as the properties exposed by
 [Deezer's web service documentation INFO tab](http://developers.deezer.com/api/artist#infos).
 Info keys are cached. You can suppress
 the cache by sending the -[DZRObject invalidateInfos] message to the object.
 This will force the model to fetch again the information for this object.
 */
- (NSArray*)supportedInfoKeys;

/*!
 Suppress the info keys cached values.
 */
- (void)invalidateInfos;

/*!
 The method keys the object supports.

 These keys corresponds to [Deezer's web services METHODS
 tab](http://developers.deezer.com/api/artist#connections).
 The information associated to these keys are *not* cached by the
 model.
 */
- (NSArray*)supportedMethodKeys;

/// @name Async KVC queries

/*!
 Query a property of this object by its keys.

 This method allows you to query the value of a property of the object
 (Deezer model property, not an Objective-C property). The supported keys
 are the ones returned by supportedInfoKeys and supportedMethodKeys.

 The model will schedule all the eventual network request on the provided network
 manager and give the result value to the provided callback. If an error occur
 preventing the model to retrieve the property's value, and error will be handed to
 the caller through the error parameter of the callback.

 !param key The key of the property you query. The keys supported by the object
    are indicated by the result of supportedInfoKeys and supportedMethodKeys.
 !param manager A request manager the model will use to schedule network request.
    You can pass nil to use the default request manager.
 !param callback A callback the model will call once it have retrieved the
    requeted key.

 @return a cancelable representing the request so the caller can cancel the
    request.
 */
- (id<DZRCancelable>)valueForKey:(NSString*)key
              withRequestManager:(DZRRequestManager*)manager
                        callback:(void (^)(id, NSError*))callback;
/*!
 Query a property of an object connected to this one.

 Allows the caller to query the value of a property of an object
 (Deezer model property, not an Objective-C property) connected to this one.
 Instead of a simple key, the caller provides a key path (dotted chain of keys
 indicating to the model the intermediate objects the model have to fetch to get
 to the final value).

 For example, the caller can request the name of the artist of an album.

     ```
     [album
      valueForKeyPath:@"artist.name"
      withRequestManager:nil
      callback:^(NSString *name, NSError *error) {}];
     ```

 The model will fetch a DZRArtist object first (requesting the value of the `artist`
 property of the album object), then it requests the value of the name property on the
 intermediate DZRArtist object which is the value requested by the caller. Finally the
 model will hand the last value to the caller by calling the provided callback.

 The model will schedule all the eventual network request on the provided network
 manager and give the result value to the provided callback. If an error occur
 preventing the model to retrieve the property's value, and error will be handed to
 the caller through the error parameter of the callback.

 This methods is convenient to query information farther away than the object owned
 by the caller without having to resort to cascading callbacks.

 !param key The key of the property you query. The keys supported by the object
    are indicated by the result of supportedInfoKeys and supportedMethodKeys.
 !param manager A request manager the model will use to schedule network request.
    You can pass nil to use the default request manager.
 !param callback A callback the model will call once it have retrieved the
    requeted key.

 !warning The caller should be careful to not query too much far away from the
   root object as since the model will follow the keypath, requesting all the
   intermediate objects, such operation could be costly.

 @return a cancelable representing the request so the caller can cancel the
    request.
 */
- (id<DZRCancelable>)valueForKeyPath:(NSString*)key
                  withRequestManager:(DZRRequestManager*)manager
                            callback:(void (^)(id, NSError*))callback;
/*!
 Query a set of value properties by keypath.

 Allows the caller to request more than one value at a time.

 !param keyPaths An array of keypath listing all the properties the caller want
   the value of.
 !param manager A request manager the model will use to schedule network request.
    You can pass nil to use the default request manager.
 !param callback A callback the model will call once it have retrieved the
    requeted key.

 !warning The caller should be careful to not query too much far away from the
   root object as since the model will follow the keypath, requesting all the
   intermediate objects, such operation could be costly.

 @return a cancelable representing the request so the caller can cancel the
    request.
 */
- (id<DZRCancelable>)valuesForKeyPaths:(NSArray*)keyPaths
                    withRequestManager:(DZRRequestManager*)manager
                              callback:(void (^)(NSDictionary*, NSError*))callback;

/// @name Model protocols

/*!
 Tests if the object is DZRPlayable.
 */
- (BOOL)isPlayable;

/*!
 Tests if the object is DZRIllustratable.
 */
- (BOOL)isIllustratable;

/*!
 Tests if the object is DZRDeletable.
 */
- (BOOL)isDeletable;

/*!
 Tests if the object is DZRRatable.
 */
- (BOOL)isRatable;

/*!
 Tests if the object is DZRCommentable.
 */
- (BOOL)isCommentable;

/*!
 Tests if the object is DZRFlowable.
 */
- (BOOL)isFlowable;

/*!
 Tests if the object is DZRRadioStreamable.
 */
- (BOOL)isRadioStreamable;

/// @name Ghost objects

/*!
 Tests if the object is a ghost.

 Ghost objects are degraded model objects for which the model
 does not know how to fetch more information. Generally this means
 the object does not have an identifier and just a subset of
 of the normal properties are defined.

 If the application try to request the value of an undefined
 property, the model will return an error.
 */
- (BOOL)isGhost;
@end
