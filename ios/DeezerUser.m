#import "DeezerUser.h"

@implementation DeezerUser

#pragma mark - NSObject

- (id)init {
  if (self = [super init]) {
    
  }
  return self;
}


#pragma mark - Singleton methods
static DeezerUser* _sharedUser = nil;

+ (DeezerUser*)currentUser {
  if (_sharedUser == nil) {
    _sharedUser = [[super alloc] init];
  }

  return _sharedUser;
}

@end