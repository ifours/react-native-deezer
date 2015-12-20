#import <Foundation/Foundation.h>
#import "DZRNetworkRequest.h"

#define DeezerRequest DZRNetworkRequest

/**
 * Enum to describe the request's response format.
 */
typedef enum {
	ResponseFormat_JSON  = 0,
	ResponseFormat_JSONP = 1,
	ResponseFormat_XML   = 2,
	ResponseFormat_PHP   = 3
} ResponseFormat;

/**
 * Enum to describe the http request's type.
 */
typedef enum {
	HttpMethod_GET      = 0,
	HttpMethod_POST     = 1,
	HttpMethod_DELETE   = 2,
} HttpMethod;


/**
 * Your application must implement this delegate to receive request callbacks.
 */
@protocol DeezerRequestDelegate <NSObject>

@required

/**
 * Mandatory.
 * Called when a request finished correctly.
 *
 * @param request
 *        The Deezer request which finished. 
 
 * @param response
 *        NSData representing response of the request 
 */
- (void)request:(DeezerRequest *)request didReceiveResponse:(NSData *)response;

/**
 * Mandatory.
 * Called when a request failed.
 *
 * @param request
 *        The Deezer request which failed.
 *
 * @param error
 *        The error.
 */
- (void)request:(DeezerRequest *)request didFailWithError:(NSError *)error;


@optional

/**
 * Called when request is starting.
 *
 * @param request
 *        The Deezer request which started.
 */
- (void)requestDidStartLoading:(DeezerRequest *)request;

@end
