//
//  DZRArtist.h
//  dsearch
//
//  Created by guillaume faure on 15/01/2014.
//  Copyright (c) 2014 guillaume faure. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "DZRObject.h"

@class DZRRequestManager;

/*!
 A class representing an artist in Deezer's model.
 
 Please refer to the documentation of [Deezer's web services for artists](http://developers.deezer.com/api/artist). for
 more information.
 */
@interface DZRArtist : DZRObject <DZRIllustratable, DZRCommentable, DZRRadioStreamable>
@end
