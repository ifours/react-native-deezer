#import <Foundation/Foundation.h>

@protocol DeezerSessionDelegate;

FOUNDATION_EXPORT NSString *const DeezerConnectPermissionBasicAccess;
FOUNDATION_EXPORT NSString *const DeezerConnectPermissionEmail;
FOUNDATION_EXPORT NSString *const DeezerConnectPermissionOfflineAccess;
FOUNDATION_EXPORT NSString *const DeezerConnectPermissionManageLibrary;
FOUNDATION_EXPORT NSString *const DeezerConnectPermissionDeleteLibrary;
FOUNDATION_EXPORT NSString *const DeezerConnectPermissionListeningHistory;

/*! DeezerConnect allows to initialize the SDK and let user log in their Deezer account.
 
 Initializing the SDK with a call to initWithAppId:andDelegate: should be the very
 first thing you do in you application. It **must** be done before you use any
 functionnality of the Deezer's SDK.
 */
@interface DeezerConnect : NSObject

/// @name Initialization

/*! Initialize an instance of DeezerConnect.
 
 The application needs to pass in its identifier and the delegate in charge of 
 handling the session events.
 
 !param appId The application identifier, it can be retreived at http://developers.deezer.com/
    in the page reserved to the applications.
 !param delegate The delegate in charge of handling session events.
 */
- (id)initWithAppId:(NSString *)appId andDelegate:(id<DeezerSessionDelegate>)delegate;

/// @name Session management

/*! The access token used by the SDK to communicate with Deezer's webservices. */
@property (nonatomic, copy)     NSString*                   accessToken;
/*! The token expriration date */
@property (nonatomic, strong)   NSDate*                     expirationDate;
/*! The application identifier.
 
 This identifier is accessible at http://developers.deezer.com/ in the developer account.
 */
@property (nonatomic, copy)     NSString*                   appId;
/*! The logged in user identifier (if any) */
@property (nonatomic, copy)     NSString*                   userId;

/*! 
 Launches identification process. The caller should pass in the list of
 rights the application requests on the user account. 
 
 The permissions are constant strings. Here is the list of possible values:
 
 - DeezerConnectPermissionBasicAccess
 - DeezerConnectPermissionEmail
 - DeezerConnectPermissionOfflineAccess
 - DeezerConnectPermissionManageLibrary
 - DeezerConnectPermissionDeleteLibrary
 - DeezerConnectPermissionListeningHistory
 
 Please refer to http://developers.deezer.com/api/permissions for more information
 about these permisions.
 
    [connect authorize:@[DeezerConnectPermissionBasicAccess, DeezerConnectPermissionOfflineAccess]]
 
 !param permissions An array of permission the application requests from the user.
 */
- (void)authorize:(NSArray *)permissions;
/*! Logout the currently logged in user. */
- (void)logout;
/*! Test the validity of the values set to accessToken, expirationDate and userId. */
- (BOOL)isSessionValid;

/*! The delegate in charge of handling session events (login, logout, ...) */
@property (nonatomic, weak)     id<DeezerSessionDelegate>   sessionDelegate;

@end

#pragma mark Delegate protocol

/*! The application should implement this delegate to receive session callbacks.
 
 Set it as the -[DeezerConnect sessionDelegate]
 */
@protocol DeezerSessionDelegate <NSObject>
@optional
/*! Called when the user successfully logged in.
 
 Token and expiration date are automatically set to the DeezerConnect object.
 At this point, the application can access these information and should save them
 int the application's keychain for late use.
 
 If the application does not save the information, it will have to ask the user
 to login again at next application launch.
 */
- (void)deezerDidLogin;
/*! Called when the indentification process did not complete.
 
 The user can have dismiss the login screen or some error could have accured.
 
 !param cancelled Set to true if the user dismiss the login window, false if 
 the identification process encountered an error.
 */
- (void)deezerDidNotLogin:(BOOL)cancelled;
/*! Called when the user logged out.
 
 The application should delete any saved credential associated with the logged
 out user.
 */
- (void)deezerDidLogout;
@end
