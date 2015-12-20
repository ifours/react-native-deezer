#import "DZRModel.h"

@interface DeezerUser : NSObject

@property (nonatomic, strong) DZRUser *currentUser;

+ (DeezerUser*)currentUser;

@end


