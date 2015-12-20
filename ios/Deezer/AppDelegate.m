/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import "AppDelegate.h"

#import "RCTRootView.h"
#import "DeezerSession.h"
#import "DeezerPlayer.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  NSURL *jsCodeLocation;

  jsCodeLocation = [NSURL URLWithString:@"http://localhost:8081/index.ios.bundle?platform=ios&dev=true"];
//  jsCodeLocation = [[NSBundle mainBundle] URLForResource:@"main" withExtension:@"jsbundle"];

  RCTRootView *rootView = [[RCTRootView alloc] initWithBundleURL:jsCodeLocation
                                                      moduleName:@"Deezer"
                                               initialProperties:nil
                                                   launchOptions:launchOptions];

  self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
  UIViewController *rootViewController = [UIViewController new];
  rootViewController.view = rootView;
  self.window.rootViewController = rootViewController;
  [self.window makeKeyAndVisible];
  
//  [application becomeFirstResponder];
  
  return YES;
}

#pragma mark - Remote Player methods
- (void)remoteControlReceivedWithEvent:(UIEvent *)event {
  switch (event.subtype) {
    case UIEventSubtypeRemoteControlPlay:
      [[DeezerPlayer sharedPlayer] play];
      break;
    case UIEventSubtypeRemoteControlPause:
      [[DeezerPlayer sharedPlayer] pause];
      break;
    case UIEventSubtypeRemoteControlNextTrack:
      [[DeezerPlayer sharedPlayer] nextTrack];
      break;
    case UIEventSubtypeRemoteControlPreviousTrack:
      [[DeezerPlayer sharedPlayer] previosTrack];
      break;
    case UIEventSubtypeRemoteControlTogglePlayPause:
      [[DeezerPlayer sharedPlayer] isPlaying] ?
        [[DeezerPlayer sharedPlayer] pause] :
        [[DeezerPlayer sharedPlayer] play];
    default:
      break;
  }
}

//- (void)applicationDidBecomeActive:(UIApplication *)application {
//  [[DeezerPlayer sharedPlayer] play];
//}

//- (void)applicationWillResignActive:(UIApplication *)application {
//  [[DeezerPlayer sharedPlayer] pause];
//}

- (void)applicationDidEnterBackground:(UIApplication *)application {
  bgTask = [application beginBackgroundTaskWithExpirationHandler:^{
    [application endBackgroundTask:bgTask];
    bgTask = UIBackgroundTaskInvalid;
  }];
  dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    [application endBackgroundTask:bgTask];
    bgTask = UIBackgroundTaskInvalid;
  });
}

@end
