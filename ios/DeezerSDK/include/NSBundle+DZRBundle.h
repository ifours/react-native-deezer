//
//  NSBundle+DZRBundle.h
//  Deezer
//
//  Created by GFaure on 10/06/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import <Foundation/Foundation.h>
@class UIImage;

/*! Access SDK bundeld resources */
@interface NSBundle (DZRBundle)
/*! Singleton method to get a handle on the resources bundle. */
+ (NSBundle*)dzrBundle;
/*! Load images from the bundle.
 
 Images are cached and requesting several time the image should provide the same
 pointer.
 
 !param name The name of the requested image.
 */
- (UIImage*)imageNamed:(NSString*)name;
@end
