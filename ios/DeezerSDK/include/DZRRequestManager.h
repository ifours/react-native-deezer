//
//  DZRRequestManager.h
//  dsearch
//
//  Created by guillaume faure on 14/01/2014.
//  Copyright (c) 2014 guillaume faure. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "DZRNetworkRequest.h"

@class DeezerConnect;

/*!
 Manage network requests.
 
 This class is intended as a entry point for all the network trafic for requesting content
 from the deezer API. The network calls are made on an operation queue. By default the Deezer
 SDK manage its own queue. It enqueues DZRRequestOperations.
 */

@interface DZRRequestManager : NSObject

/// @name Configuration

@property (nonatomic, strong) DeezerConnect *dzrConnect;

/// @name Create instance

/*!
 The application's default network manager.
 
 This is a singleton method. Anywhere in the model classes where you have to pass
 a DZRRequestManager as parameter, if you pass nil instead, the default manager
 will be used.
 
 @return The default manager.
 */
+ (instancetype)defaultManager;

/*!
 Create a sub-manager.
 
 The sub-manager is added to the cancelables of the parent manager. Canceling the
 parent manager cascade to all its cancelables (Requests or sub-managers).

 !see cancel.
 @return A new manager configured as sub-manager of the current instance.
 */
- (DZRRequestManager*)subManager;

/// @name Manage requests

/*!
 Schedules a request on the manager.
 
 The request is added to the requests scheduled by this manager. The way the
 manager will handle the requests depends on the slots currently opened, the
 -[DZRNetworkRequest priority] and the requests waiting queue.
 
 !param request The request to schedule on this manager.
 */
- (void)addRequest:(DZRNetworkRequest *)request;

/*!
 Cancels all the cancelable objects owned by this manager.
 
 Cancelables items are DZRNetworkRequest and sub DZRRequestManager.
 */
- (void)cancel;

/*!
 Prevent further requests to be scheduled.
 */
- (void)pause;

/*!
 Resume the scheduling if requests.
 */
- (void)resume;
@end
