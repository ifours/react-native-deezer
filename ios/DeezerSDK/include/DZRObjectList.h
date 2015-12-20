//
//  DZRObjectList.h
//  Deezer
//
//  Created by GFaure on 06/05/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DZRRequestManager;

/*!
 A list of model objects.
 
 It can be though as the implementation of an "asynchronous array". This is a 
 bounded collection of model objects. Elements can be directly accessed by indexes.
 The model will take care of fetching the elements from the network as needed.
 */
@interface DZRObjectList : NSObject
/*!
 Access an element by index.
 
 !param index The index of the requested element.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call once it got the
   result or an error occurred.
 */
- (void)objectAtIndex:(NSUInteger)index
          withManager:(DZRRequestManager *)manager
             callback:(void (^)(id obj, NSError *error))callback;
/*!
 Gather the elements from a set of indexes;
 
 !warning The caller should be careful in the use of this method as its use
   with a indexes with a high count can have a significant performance impact.
 
 !param indexes An set of the requested indexes.
 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call once it got the
   result or an error occurred.
 */
- (void)objectsAtIndexes:(NSIndexSet *)indexes withManager:(DZRRequestManager *)manager callback:(void (^)(NSArray *objs, NSError *error))callback;
/*!
 Gather all elements of the collections in an NSArray.

 !warning The caller should be careful in the use of this method as its use on
   a collection with a high count can have a significant performance impact.

 !param manager A request manager the model will use to schedule network requests.
   If nil, the default request manager is used.
 !param callback The callback the caller wants the model to call once it got the
   result or an error occurred.
 */
- (void)allObjectsWithManager:(DZRRequestManager *)manager callback:(void (^)(NSArray *objs, NSError *error))callback;
/*!
 The number of elements in this collection.
 
 @return an integer representing the number of elements in this collection.
 */
- (NSUInteger)count;
@end
