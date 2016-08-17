# Using UnityAds SDK 2.0 Wrapper for Cocos2dx

In this guide, we assume you already familiar with all Cocos2dx, iOS or Android platform development. So we mainly cover Unity Ads and the Wrapper for Cocos2dx content.

If you are interested in iOS native and Android integration guide, please check out this: 
[https://github.com/Applifier/Unity-Ads-SDK-2.0-Integration-Examples]


We are using **Android Studio** or **XCode** for this tutorial.

###[To Get Started](#start)
  1. Create a Game Project in the [Unity Ads Dashboard](https://dashboard.unityads.unity3d.com)
  2. Download Unity Ads 2.0 for [iOS](https://github.com/Unity-Technologies/unity-ads-ios/releases) or [Android](https://github.com/Unity-Technologies/unity-ads-android/releases).

###[Android Setup](#android-header)
  1. [Import Unity Ads](#a1)
  2. [Add listener & callbacks](#a2)

###[iOS Setup](#ios-header)
  1. [Import Unity Ads](#i1)
  2. [Add delegate & callbacks](#i1)

###[Use UnityAds Wrapper API in Cocos2dx](#ccdx-header)
  1. [Wrapper Files](#c1)
  2. [Initialize Unity Ads](#c2)
  2. [Show an Ad](#c3)
  3. [Add rewarded integration](#c4)
  
---
 
<a name="start"/>
# To Get Started

### Create a Game Project in the [Unity Ads Dashboard](https://dashboard.unityads.unity3d.com)

Log into the [Unity ads dashboard](https://dashboard.unityads.unity3d.com) using your [Unity3D account](https://unity3d.com).

Create a new game project, and enable test mode  
  1. Click new game, and name the project
  2. Select "Google Play Store", check the box "This game has not been published yet"
  3. Select "Not targeted for children under 13", unless your game *specifically* targets children.
  4. Click continue
  
> Please note that test mode can be toggled under (add screenshot)

At this point you should see a unique (7-digit) game ID that can be used to initialize Unity Ads in your project.

Download the [Unity Ads 2.0 for Android](https://github.com/Unity-Technologies/unity-ads-android/releases).

---


<a name="android-header" />
#Android Integration

Example project is available [here](https://github.com/Applifier/Unity-Ads-SDK-2.0-Integration-Examples/tree/master/Android)

<a name="a1"/>
### 1. Import Unity Ads
From the downloaded Unity Ads 2.0 folder, locate **unity-ads.aar** and import using Android Studio's AAR import tool.



<a name="a2"/>
### 2. Add Listener & Callbacks


For dependency separation purpose, we create **UnityAdsListener** and **UnityAdsJNI** classes for callbacks and expose API to C layer.

#### Callbacks
In **UnityAdsListener.java**, we make this class implements **IUnityAdsListener** interface, and implement all necessary methods.

```Java
import com.unity3d.ads.IUnityAdsListener;
import com.unity3d.ads.UnityAds;
import com.unity3d.ads.log.DeviceLog;

/**
 * Created by solomonli on 7/8/16.
 */
public class UnityAdsListener implements IUnityAdsListener {

    @Override
    public void onUnityAdsReady(final String placementId) {
        DeviceLog.debug("[UnityAds Demo] onUnityAdsReady for placement: " + placementId);
    }

    @Override
    public void onUnityAdsStart(String placementId) {
        DeviceLog.debug("[UnityAds Demo] onUnityAdsStart for placement: " + placementId);
    }

    @Override
    public void onUnityAdsFinish(String placementId, UnityAds.FinishState result) {
        DeviceLog.debug("[UnityAds Demo] onUnityAdsFinish with FinishState: " + result.name() + " for placement: " + placementId);
        UnityAdsJNI.reward(placementId);
    }

    @Override
    public void onUnityAdsError(UnityAds.UnityAdsError error, String message) {
        DeviceLog.debug("[UnityAds Demo] onUnityAdsError with message: " + message);
    }
}
```

#### APIs
In **UnityAdsJNI.java**, we try to implement all interfaces Unity Ads SDK exposes to developers, except those really useless for Cocos2dx layer.

Method list below:

```Java
void UnityAdsInitialize(String gameId, boolean testMode)

boolean UnityAdsIsReady(String placementId)

void UnityAdsShow(String placementId)

boolean UnityAdsGetDebugMode()

String UnityAdsGetPlacementState(String placementId)

String UnityAdsGetVersion()

boolean UnityAdsIsInitialized()

boolean UnityAdsIsSupported()

void UnityAdsSetDebugMode(boolean debugMode)

```

For detail implementation, you can find from the wrapper project. As this tutorial is mainly focus on Cocos2dx wrapper usage, this file you can just copy to your Android Studio and modify it.


#### Bind them up
In **AppActivity.java** (or any activity that will show ads), don't forget to instantiate UnityAdsListener, and assign the Activity and listener to **UnityAdsJNI** class.

```java  
    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        final UnityAdsListener unityAdsListener = new UnityAdsListener();
        UnityAdsJNI.activity = this;
        UnityAdsJNI.unityAdsListener = unityAdsListener;
    }
```


<a name="ios-header"/>
#iOS integration

--- 


<a name="i1"/>
### 1. Import Unity Ads
From the downloaded Unity Ads 2.0 folder, locate **UnityAds.framework**.

Drag-and-drop **UnityAds.framework** into your XCode project (and copy it).

<a name="i2"/>
### 2. Add UnityAdsBridge Objective C++ class

Create **UnityAdsBridge** class, and rename the implementation file to **UnityAdsBridge.mm**. You can simple use these files from this project for they are part of the wrapper.


**UnityAdsBridge.h** source code

```ObjC
	@interface UnityAdsBridge : UIViewController<UnityAdsDelegate>
	
	+ (UIViewController* ) viewController;
	
	@end
```

In **UnityAdsBridge.mm** source code, we have 2 parts which are **UnityAdsDelegate** and api exposed.

**UnityAdsDelegate** part
```ObjC 

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
    if(state == kUnityAdsFinishStateCompleted) {
        auto scene = cocos2d::Director::getInstance()->getRunningScene()->getChildren().at(1);
        if (typeid(*scene) == typeid(HelloWorld)) {
            HelloWorld* gameScene = static_cast<HelloWorld*>(scene);
            const char *placementIdC = [placementId UTF8String];
            gameScene->rewardPlayer(placementIdC);
        }
    }
}

@end

```

API part. This implementation is trying to expose almost all APIs from **UnityAds** class, but except those useless for C++ layer

```ObjC

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
    return [UnityAds getDebugMode];
}

std::string UnityAdsGetPlacementState(const char* parameter) {
    NSLog(@"[UnityAds] UnityAdsGetPlacementState");
    UnityAdsPlacementState state = [UnityAds getPlacementState];
    switch(state){
        case kUnityAdsPlacementStateReady:
            return "kUnityAdsPlacementStateReady";
        case kUnityAdsPlacementStateNoFill:
            return "kUnityAdsPlacementStateNoFill";
        case kUnityAdsPlacementStateWaiting:
            return "kUnityAdsPlacementStateWaiting";
        case kUnityAdsPlacementStateDisabled:
            return "kUnityAdsPlacementStateDisabled";
        case kUnityAdsPlacementStateNotAvailable:
            return "kUnityAdsPlacementStateNotAvailable";
    }
}

std::string UnityAdsGetVersion() {
    NSLog(@"[UnityAds] UnityAdsGetVersion");
    std::string ret = std::string([[UnityAds getVersion] UTF8String]);
    return ret;
}

bool UnityAdsIsInitialized() {
    NSLog(@"[UnityAds] UnityAdsIsInitialized");
    return [UnityAds isInitialized];
}

bool UnityAdsIsSupported() {
    NSLog(@"[UnityAds] UnityAdsIsSupported");
    return [UnityAds isSupported];
}

void UnityAdsSetDebugMode(bool debugMode) {
    NSLog(@"[UnityAds] UnityAdsSetDebugMode");
    [UnityAds setDebugMode:debugMode];
}

```

<a name="ccdx-header"/>
#Use UnityAds Wrapper API in Cocos2dx

<a name="c1"/>
### 1. The Wrapper File
In this wrapper project, we are using the wrapper file `UnityAdsNativeAPI.h` to expose Unity Ads API .

The implementations of this file have been put under iOS and Android separate projects.

To use this wrapper file, we simply include `UnityAdsNativeAPI.h` in where you would like to use it. In this sample game, we include this API file in `HelloWorldScene.h` file.


<a name="c2"/>
### 2. Initialize Unity Ads

In order not to muddle the game logic, we put Unity Ads initialize code in a separate function.

Declare the function in `HelloWorldScene.h` file.

```C
	void initUnityAdsFunc();
```

Implement the initialization function in `HelloWorldScene.cpp` file.

```C
void HelloWorld::initUnityAdsFunc()
{
    const char* gameId = "1055529"; // for Android

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	    gameId = "1076532";
	#endif
    
    UnityAdsInit(gameId, false);
}
```

> Note: "YOUR_GAME_ID" is a 7-digit number from the [Unity Ads dashboard](https://dashboard.unityads.unity3d.com). (For example, "1091553")


Call the initialization function when game init, just after layer just initialized.

```C
	......
	
    if ( !Layer::init() )
    {
        return false;
    }

    this->initUnityAdsFunc();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    ......
```


<a name="c3"/>
### 3. Show an Ad

In order not to muddle the game logic, we put Unity Ads show an ad code in a separate function.

Declare the function in `HelloWorldScene.h` file.
```C
	void showUnityAdsFunc(Ref* pSender);
```

Implement the show an ad function in `HelloWorldScene.cpp` file.

```C
void HelloWorld::showUnityAdsFunc(Ref* pSender)
{
    const char* zoneString = "rewardedVideo";
    
    if(UnityAdsIsReady(zoneString)) {
        UnityAdsShow(zoneString);
    } else {
        CCLOG("[UnityAds cpp test] yet cannot show");
    }
}
```

Add a button enabling the player to show an ad, after adding the close button.

```C
	......
	
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Add show ad button
    auto showAdItem = MenuItemImage::create(
                                           "UnityChan_logo.png",
                                           "UnityChan_logo.png",
                                           CC_CALLBACK_1(HelloWorld::showUnityAdsFunc, this));

    showAdItem->setPosition(Vec2(origin.x + showAdItem->getContentSize().width + 20,
                                origin.y + showAdItem->getContentSize().height + 20));

    menu->addChild(showAdItem, 1);
    
```

When tapping on this button, it will call `showUnityAdsFunc` function.


<a name="c4"/>
### 4. Add rewarded integration

In order not to muddle the game logic, we put Unity Ads reward code in a separate function.

Declare the function in `HelloWorldScene.h` file.
```C
	void rewardPlayer(const char *placementId);
```

Implement the reward function in `HelloWorldScene.cpp` file.

```C
void HelloWorld::rewardPlayer(const char *placementId)
{

    CCLOG("[UnityAds cpp test] rewarded");
    const char* targetStr = "rewardedVideo";
    if(strcmp(placementId, targetStr) == 0){
        if(titleLabel){
            const char* text = "Congrats!";
            titleLabel->setString(text);
        }
    }
}
```

This function is for iOS or Android layer to call, we already exposed this in `UnityAdsBridge.mm` and `UnityAdsJNI.cpp`.


---
