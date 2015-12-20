//
//  DZRNetworkRequest.h
//  Deezer
//
//  Created by GFaure on 12/05/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DZRCancelable.h"

@class UIImage;
@class DeezerConnect;

/*!
 Priority levels for requests scheduling in the network stack.
 */
typedef NS_ENUM(NSInteger, DZRRequestPriority) {
    /*! The requests using this priority are not guaranteed to de issued any
     time soon and can be delayed until the manager can batch them or some
     request with higher priority is scheduled. You can use this priority
     for example to send some tacking information. */
    DZRRequestPriorityLow = -4,
    /*! This is the default priority. Requests
     configured with this priority will be sent as soon as possible but can
     be delayed when the manager is busy handling higher priorities or
     prior requests. You can let the request priority set to this value
     safely most of the time */
    DZRRequestPriorityNormal = 0,
    /*! This is the highest priority you can
     specify for a request. This kind of request is processed by the
     manager as an absolute priority. If no slot is currently available for
     request with this priority, the manager can cancel a lower priority
     request and queue it back in order to free a slot. You should use this
     priority carefully for times when you really need information quickly
     from the server. */
    DZRRequestPriorityHigh = 4
};

NSString* DZRRequestURLEncodeDictionary(NSDictionary *dic);
NSDictionary *DZRRequestURLDecodeString(NSString* urlEncoded);

/*!
 Represent network requests.
 
 This is the base class of a collection of specialized network request.
 */
@interface DZRNetworkRequest : NSObject<DZRCancelable>

- (NSString *)identifier;

/// @name Configuration

/*!
 The complete URL.
 
 This URL can be different than the one passed into the constructor. It happens
 for example if the network stack add some session information.
 */
@property (nonatomic, readonly) NSURL *URL;
/*!
 The request priority.

 The default priority for a request is DZRRequestPriorityNormal. The application
 can set a different priority for special casses.
 */
@property (nonatomic, assign) DZRRequestPriority priority;

/// @name Request completion

/*!
 Block called by the network stack on request complement.
 
 Whenever the request finishes, being a reponse by the server or an error, the 
 network stack will call this block. If a response comes back from the server,
 the data will be passed as the first paramater of the block. If the netork
 stack encounter and error, it will be passed to the second parameter. Note that
 in some cases, both the response and error parameters can be set or nil.
 */
@property (nonatomic, copy) void(^dataCompletionBlock)(NSData* response, NSError* error);

/// @name Initilization

/*!
 Initlialize a request the string of a URL.
 
 !param urlString The string representation of the URL to request.
 */
- (id)initWithURLString:(NSString*)urlString;
/*!
 Initialize a request with an URL.
 
 !param URL The URL to request.
 */
- (id)initWitURL:(NSURL*)URL;

/// @name Cancel

/*!
 Cancels the request.
 */
- (void)cancel;
@end

/*!
 This is a specialized network request for JSON payload response.
 
 In addition to the normal network management, the returned server response will
 be parsed as JSON and handed to the application by the means of the JSONCompletionBlock.
 
 The DZRNetworkRequest implementation will still call the -[DZRNetworkRequest dataCompletionBlock],
 just before the call to JSONCompletionBlock is called.
 */
@interface DZRJSONRequest : DZRNetworkRequest
/*!
 The completion block to be called with the results of parsing the server response.
 
 The network errors will bubble up from the DZRNetworkRequest. This means that if
 the caller wants to catch error, it does not have to set also the 
 -[DZRNetworkRequest dataCompletionBlock] just for the sake of catching the network
 error. It just have to take care of all the errors in the JSONCompletionBlock.
 */
@property (nonatomic, copy) void(^JSONCompletionBlock)(id JSON, NSError* error);
@end

/*!
 This is a specialized request to POST URL encoded content and get back a JSON response.
 
 The caller sets the postContent to specify the POST payload. It will be converted
 automatically to URL encoded form before being sent to the server. The JSON response
 comes back trough the -(DZRJSONRequest JSONCompletionBlock] callback.
 */
@interface DZRJSONPostRequest : DZRJSONRequest
/*!
 Data to be sent as POST content after having being URL encoded.
 */
@property (nonatomic, strong) NSDictionary *postContent;
/*!
 Initilize the post request.
 
 !param urlString The string representation of the URL to request.
 !param postContent POST payload.
 */
- (id)initWithURLString:(NSString *)urlString andPostContent:(NSDictionary*)postContent;
@end

/*!
 This is a specialized request to issue a DELETE request and get back a JSON response.
 */
@interface DZRJSONDeleteRequest : DZRJSONRequest
/*!
 Initilize the DELETE request.
 
 !param urlString The string representation of the URL to request.
 !param params some more parameters that will be encoded as query string.
 */
- (id)initWithURLString:(NSString *)urlString andParams:(NSDictionary*)params;
@end

/*!
 This is a specialized request for an image.
 
 The DZRNetworkRequest implementation will still call the -[DZRNetworkRequest dataCompletionBlock],
 just before the call to imageCompletionBlock is called.
 */
@interface DZRImageRequest : DZRNetworkRequest
/*!
 The completion block to be called with the results of parsing the server response.
 
 The network errors will bubble up from the DZRNetworkRequest. This means that if
 the caller wants to catch error, it does not have to set also the
 -[DZRNetworkRequest dataCompletionBlock] just for the sake of catching the network
 error. It just have to take care of all the errors in the imageCompletionBlock.
 */
@property (nonatomic, copy) void(^imageCompletionBlock)(UIImage* image, NSError* error);
@end
