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
#import "HelloWorldScene.h"

@implementation UnityAdsBridge

+ (UIViewController* ) viewController {
    
    UIApplication* app = [UIApplication sharedApplication];
    AppController* controller = (AppController*)[app delegate];
    UIViewController* rootController = [controller.window rootViewController];
    return rootController;
}

#pragma mark -
#pragma mark UnityAdsDelegate

- (void)unityAdsReady:(NSString *)placementId {
    NSLog(@"[UnityAds delegate] unityAdsReady with placementId=%@", placementId);
}
- (void)unityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message{
    NSLog(@"[UnityAds delegate] unityAdsDidError with message=%@ , and error=%ld", message, error);
}
- (void)unityAdsDidStart:(NSString *)placementId{
}
- (void)unityAdsDidFinish:(NSString *)placementId
          withFinishState:(UnityAdsFinishState)state{
    auto scene = cocos2d::Director::getInstance()->getRunningScene()->getChildren().at(1);
    if (typeid(*scene) == typeid(HelloWorld)) {
        HelloWorld* gameScene = static_cast<HelloWorld*>(scene);
        const char *placementIdC = [placementId UTF8String];
        gameScene->rewardPlayer(placementIdC);
    }
    
}

@end



#pragma mark -
#pragma mark Unity Ads Native API Implementation

void UnityAdsInit (const char *gameIdParameter, bool testMode) {
    
    NSLog(@"[UnityAds] UnityAdsInit");
    
    UnityAdsBridge* bridge = [UnityAdsBridge new];
    NSString* gameId = [NSString stringWithFormat:@"%s", gameIdParameter];
    [UnityAds initialize:gameId delegate:bridge testMode:testMode];
}
bool UnityAdsIsReady (const char *parameter){
    NSString* placementId = [NSString stringWithFormat:@"%s", parameter];
    NSLog(@"[UnityAds] UnityAdsIsReady for placement=%@", placementId);
    return [UnityAds isReady:placementId];
}
void UnityAdsShow (const char *parameter){
    NSString* placementId = [NSString stringWithFormat:@"%s", parameter];
    [UnityAds show:[UnityAdsBridge viewController] placementId:placementId];
}

bool UnityAdsGetDebugMode() {
    NSLog(@"[UnityAds] UnityAdsGetDebugMode");
    return false;
}

std::string UnityAdsGetPlacementState(const char* parameter) {
    NSLog(@"[UnityAds] UnityAdsGetDebugMode");
    return "";
}

std::string UnityAdsGetVersion() {
    NSLog(@"[UnityAds] UnityAdsGetDebugMode");
    return "";
}

bool UnityAdsIsInitialized() {
    NSLog(@"[UnityAds] UnityAdsGetDebugMode");
    return false;
}
bool UnityAdsIsSupported() {
    NSLog(@"[UnityAds] UnityAdsGetDebugMode");
    return false;
}
void UnityAdsSetDebugMode(bool debugMode) {
    NSLog(@"[UnityAds] UnityAdsGetDebugMode");
}
