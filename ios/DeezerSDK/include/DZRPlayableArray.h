//
//  DZRPlayableArray.h
//  Deezer
//
//  Created by GFaure on 05/05/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DZRObject.h"
#import "DZRObjectList.h"

/*!
 A DZRPlayableArray is the most basic implementation of DZRPlayable.
 
 This implementation of DZRPlayalbe simply wraps an DZRObjectsList of DZRTracks and can
 be used to conviniently implement DZRPlayable not provided by the model.
 */
@interface DZRPlayableArray : NSObject <DZRPlayableRandomAccessIterator, DZRPlayable>
- (void)setTracks:(DZRObjectList*)tracks error:(NSError*)error;
@end
