//
// Created by GFaure on 19/06/2014.
// Copyright (c) 2014 Deezer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DZRCancelable.h"

@interface DZRGenericCancelable : NSObject <DZRCancelable>
@property (nonatomic, assign) BOOL canceled;

- (void)addCancelable:(id<DZRCancelable>)child;
@end