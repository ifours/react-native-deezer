//
//  DeezerConnect+Compatibility.h
//  Deezer
//
//  Created by GFaure on 15/09/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import "DeezerConnect.h"
#import "DeezerRequestDelegate.h"

@interface DeezerConnect (Compatibility)
/**
 * Create a DeezerRequest
 * @param servicePath
 *          The request URL, ex: @"user/me"
 *
 * @param params
 *          The parameter(s) of the request. May be nil, if there is no parameter.
 *
 * @param httpMethod
 *          The type of http method (GET, POST, DELETE).
 *          Check-out enum type HttpMethod into DeezerRequestDelegate.h.
 *
 * @param responseFormat
 *          The output format type (JSON, XML...)
 *          Check-out enum type ResponseFormat into DeezerRequestDelegate.h.
 *
 * @param delegate
 *          Callback interface for notifying the application when the request is finished.
 *          (succeeded or failed).
 *
 * @return DeezerRequest*
 *          A pointer to DeezerRequest object.
 */
- (DeezerRequest*)createRequestWithServicePath:(NSString*)servicePath
                                        params:(NSDictionary*)params
                                    httpMethod:(HttpMethod)httpMethod
                                responseFormat:(ResponseFormat)responseFormat
                                      delegate:(id<DeezerRequestDelegate>)delegate;

/*
 * Same as above with responseFormat set to JSON
 */
- (DeezerRequest*)createRequestWithServicePath:(NSString*)servicePath
                                        params:(NSDictionary*)params
                                    httpMethod:(HttpMethod)httpMethod
                                      delegate:(id<DeezerRequestDelegate>)delegate;
/*
 * Same as above with httpMethod set to GET
 */
- (DeezerRequest*)createRequestWithServicePath:(NSString*)servicePath
                                        params:(NSDictionary*)params
                                      delegate:(id<DeezerRequestDelegate>)delegate;


/**
 * Create a DeezerRequest
 * @param requestURL
 *          The request URL
 *
 * @param params
 *          The parameter(s) of the request. May be nil, if there is no parameter.
 *
 * @param httpMethod
 *          The type of http method (GET, POST, DELETE).
 *          Check-out enum type HttpMethod into DeezerRequestDelegate.h.
 *
 * @param responseFormat
 *          The output format type (JSON, XML...)
 *          Check-out enum type ResponseFormat into DeezerRequestDelegate.h.
 *
 * @param delegate
 *          Callback interface for notifying the application when the request is finished.
 *          (succeeded or failed).
 *
 * @return DeezerRequest*
 *          A pointer to DeezerRequest object.
 */
- (DeezerRequest*)createRequestWithUrl:(NSString*)url
                                params:(NSDictionary*)params
                            httpMethod:(HttpMethod)httpMethod
                        responseFormat:(ResponseFormat)responseFormat
                              delegate:(id<DeezerRequestDelegate>)delegate;

/*
 * Same as above with responseFormat set to JSON
 */
- (DeezerRequest*)createRequestWithUrl:(NSString*)url
                                params:(NSDictionary*)params
                            httpMethod:(HttpMethod)httpMethod
                              delegate:(id<DeezerRequestDelegate>)delegate;

/*
 * Same as above with httpMethod set to GET
 */
- (DeezerRequest*)createRequestWithUrl:(NSString*)url
                                params:(NSDictionary*)params
                              delegate:(id<DeezerRequestDelegate>)delegate;

/**
 * Use this method to launch a synchronous request.
 * @param syncRequest
 *          The request to launch.
 *
 */
- (void)launchSyncRequest:(DeezerRequest*)request;

/**
 * Use this method to launch an ASynchronous request.
 * @param syncRequest
 *          The request to launch.
 *
 */
- (void)launchAsyncRequest:(DeezerRequest*)request;

/**
 * Cancel  an asyn request
 * @param syncRequest
 *          The request to cancel.
 *
 */
- (void)cancel:(DeezerRequest*)request;
@end
