//
//  DZRRadio.h
//  Deezer
//
//  Created by GFaure on 24/04/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import "DZRObject.h"
#import "DZRObjectList.h"

@class DZRRequestManager;

/*!
 A class representing a radio in Deezer's model.
 
 Please refer to the documentation of [Deezer's web services for radios](http://developers.deezer.com/api/radio). for
 more information.
 
 In addition, this class offrers some useful class methods to request DZRRadio objects.
 */
@interface DZRRadio : DZRObject <DZRPlayable, DZRIllustratable, DZRFlowable>
/*!
 Requests the list of Deezer's radios.
 
 Allows the caller to requets for a list of radios provided by Deezer. The model
 on success, will hand a DZRObjectList containing DZRRadio objects.
 
 !param manager A request manager the model will use to schedule network request.
   If nil the default manager will be used.
 !param callback A callback the model will call once it have retrieved the
   list of radios.
 */
+ (void)radiosWithRequestManager:(DZRRequestManager*)manager callback:(void(^)(DZRObjectList*, NSError*))callback;
/*!
 Requests a list of radios grouped by genre.
 
 !param manager A request manager the model will use to schedule network request.
   If nil the default manager will be used.
 !param callback A callback the model will call once it have retrieved the
   list of radios.
 */
+ (void)radiosByGenreWithRequestManager:(DZRRequestManager*)manager callback:(void(^)(DZRObjectList*, NSError*))callback;
/*!
 Requets a list of only the popular radios.
 
 !param manager A request manager the model will use to schedule network request.
   If nil the default manager will be used .
 !param callback A callback the model will call once it have retrieved the
   list of radios.
 */
+ (void)topRadiosWithRequestManager:(DZRRequestManager*)manager callback:(void(^)(DZRObjectList*, NSError*))callback;
@end
