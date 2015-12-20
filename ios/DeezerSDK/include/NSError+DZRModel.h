//
//  DZRError.h
//  Deezer
//
//  Created by GFaure on 25/04/2014.
//  Copyright (c) 2014 Deezer. All rights reserved.
//

#import <Foundation/Foundation.h>

/// @name user info's dictionary keys.

extern NSString * const DZRModelErrorDomain;

/*!
 Deezer's model error codes.
 
 They are associated with the DZRModelErrorDomain. Please refer to the corresponing
 methods of NSError(DZRModel) for more information.
 */
typedef NS_ENUM(NSUInteger, DZRModelError) {
    /*! Some error occured while dealing with some aspect of the model */
    DZRModelGenericError,
    /*! The API Returned an object of a type that this SDK does not know about */
    DZRModelUnknownTypeError,
    /*! The API returned a malformated JSON representation of an object */
    DZRModelNotADeezerObjectError,
    /*! An error occured while parsing the JSON */
    DZRModelPartialParseError,
    /*! An unkwnow property have been requested */
    DZRModelUnknownObjectPropertyError,
    /*! An error occured while parsing some property of a Deezer object */
    DZRModelPropertyParsingError,
    /*! A ghost object was requested a property that was not defined on it */
    DZRModelUndefinedPropertyOnGhostObjectError,
    /*! An argument passed to one of the DZRModel methods was invalid */
    DZRModelArgumentError,
};

/*! Errors relative to model objects.
 
 Theses error are created in the demain `DZRModelErrorDomain` and their code
 are one of DZRModelError
 */
@interface NSError (DZRModel)
/*! A generic error in the model.
 
 Generate an error with domain `DZRModelErrorDomain` and code `DZRModelGenericError`.
 
 !param description Guets assigned to the `NSLocalizedDescriptionKey` user info's key.
 */
+ (NSError*)genericErrorWithDescription:(NSString *)description;
/*! The API Returned an object of a type that this SDK does not know about.
 
 Generate an error with domain `DZRModelErrorDomain` and code `DZRModelUnknownTypeError`.
 
 !param JSON Gets assigned to the `DZROriginalJSONKey` user info's key.
 */
+ (NSError*)unknownTypeErrorWithJSON:(NSDictionary *)JSON;
/*! The API returned a malformated JSON representation of an object.
 
 Generate an error with domain `DZRModelErrorDomain` and code `DZRModelNotADeezerObjectError`.
 
 !param JSON Gets assigned to the `DZROriginalJSONKey` user info's key.
 */
+ (NSError*)notADeezerObjectErrorWithJSON:(NSDictionary *)JSON;
/*! An error occured while parsing the JSON.
 
 Generate an error with domain `DZRModelErrorDomain` and code `DZRModelPartialParseError`.
 
 !param errors Gets assigned to the `DZROriginalErrorsKey` user info's key. The errors are
 flattened (if one of the error is also a `DZRModelPartialParseError`, it is replaced
 by its original errors).
 */
+ (NSError*)partialParseErrorWithErrors:(NSArray *)errors;
/*! An unkwnow property have been requested.
 
 Generate an error with domain `DZRModelErrorDomain` and code `DZRModelUnknownObjectPropertyError`.
 
 !param property Gets assigned to the `DZRRequestedPropertyKey` user info's key.
 */
+ (NSError*)unknownObjectPropertyErrorWithPropertyName:(NSString *)property;
/*! An error occured while parsing some property of a Deezer object.
 
 Generate an error with domain `DZRModelErrorDomain` and code `DZRModelPropertyParsingError`.
 
 !param objectID Gets assigned to the `DZRObjectIDKey` user info's key.
 !param objectType Gets assigned to the `DZRObjectTypeKey` user info's key.
 !param property Gets assigned to the `DZRPropertyKey` user info's key.
 !param error Gets assigned to the `DZROriginalErrorsKey` user info's key.
 */
+ (NSError*)propertyParsingErrorWithObjectID:(NSString*)objectID
                                  objectType:(NSString*)objectType
                                propertyName:(NSString*)property
                                parsingError:(NSError *)error;
/*! A ghost object was requested a property that was not defined on it.
 
 Generate an error with domain `DZRModelErrorDomain` and code `DZRModelUndefinedPropertyOnGhostObjectError`.
 
 !param objectType Gets assigned to the `DZRObjectTypeKey` user info's key.
 !param property Gets assigned to the `DZRPropertyKey` user info's key.
 */
+ (NSError*)undefinedPropertyOnGhostObjectWithObjectType:(NSString*)objectType
                                            propertyName:(NSString *)property;

+ (NSError*)argumentErrorWithMessage:(NSString*)format, ...;
@end


#pragma mark user info's dictionary keys.

extern NSString * const DZROriginalErrorsKey;
extern NSString * const DZROriginalJSONKey;
extern NSString * const DZRRequestedPropertyKey;
extern NSString * const DZRPropertyKey;
extern NSString * const DZRObjectIDKey;
extern NSString * const DZRObjectTypeKey;

#pragma mark API Errors.

extern NSString * const DZRAPIErrorDomain;

/*! Error domain for errors returned by Deezer servers.
 
 These errors are associated with the domain `DZRAPIErrorDomain` and error codes
 are the ones documented in the Deezer's webservices documentation.
 Please refer to http://developers.deezer.com/api/errors for more information.
 */
@interface NSError (DZRAPI)
/*! Generate an API error from the JSON returned by the web services.
 
 !param JSON Gets assigned to the `DZROriginalJSONKey` user info's key.
 */
+ (NSError*)APIErrorWithJSON:(id)JSON;
+ (BOOL)isAPIError:(NSDictionary*)JSON;
@end
