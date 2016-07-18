#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, strong) UIWindow *window;
@property(nonatomic, readonly) RootViewController* viewController;

@end

