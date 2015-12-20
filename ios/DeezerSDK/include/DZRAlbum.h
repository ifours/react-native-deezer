//
//  DZRAlbum.h
//  dsearch
//
//  Created by guillaume faure on 15/01/2014.
//  Copyright (c) 2014 guillaume faure. All rights reserved.
//

#import "DZRObject.h"

/*!
 A class representing an album in Deezer's model.
 
 Please refer to the documentation of [Deezer's web services for album](http://developers.deezer.com/api/album). for
 more information.
 */
@interface DZRAlbum : DZRObject <DZRPlayable, DZRIllustratable, DZRRatable, DZRCommentable>
@end
