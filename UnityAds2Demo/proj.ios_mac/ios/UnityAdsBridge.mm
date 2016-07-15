//
//  UnityAdsBridge.m
//  UnityAds2Demo
//
//  Created by Solomon Li on 7/15/16.
//
//

#import "UnityAdsNativeAPI.h"
#import "UnityAdsBridge.h"
#import "AppController.h"

@implementation UnityAdsBridge

#pragma mark -
#pragma mark Unity Ads Native API Implementation

void UnityAdsInit (const char *gameIdParameter, bool testMode) {
    NSLog(@"[UnityAds] UnityAdsInit");
    UIApplication* app = [UIApplication sharedApplication];
    AppController* controller = (AppController*)[app delegate];
    UIViewController* rootController = [controller.window rootViewController];
    
//    NSString* gameId = [NSString stringWithFormat:@"%s", gameIdParameter];
//    [[UnityAds sharedInstance] startWithGameId:gameId andViewController:rootController];
//    [[UnityAds sharedInstance] setDelegate:controller];
}
bool UnityAdsIsReady (const char *parameter){
    return false;
}
void UnityAdsShow (const char *parameter){
}


#pragma mark -
#pragma mark UnityAdsDelegate

- (void)unityAdsReady:(NSString *)placementId {
}
- (void)unityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message{
}
- (void)unityAdsDidStart:(NSString *)placementId{
}
- (void)unityAdsDidFinish:(NSString *)placementId
          withFinishState:(UnityAdsFinishState)state{
}

@end
