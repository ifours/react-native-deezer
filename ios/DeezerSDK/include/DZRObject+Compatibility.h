//
//  DZRObject+Compatibility.h
//  Deezer
//
//  Created by GFaure on 15/09/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import "DZRObject.h"

@interface DZRObject (Compatibility)
+ (DZRObject*)objectFromJSONData:(NSData*)JSONData error:(NSError**)error;
@end
