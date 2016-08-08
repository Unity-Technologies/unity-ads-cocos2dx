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
  1. [Import Unity Ads](i1)
  2. [Add delegate & callbacks](i1)

###[Cocos2dx Integration](#ccdx-header)
  1. [Initialize Unity Ads](c1)
  2. [Show an Ad](c1)
  3. [Add rewarded integration](c1)
  
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
#iOS integration (Swift)

--- 

<a name="i1"/>
### 1. Import Unity Ads
From the downloaded Unity Ads 2.0 folder, locate **UnityAds.framework**.

Drag-and-drop **UnityAds.framework** into your XCode project (and copy it).

<a name="i2"/>
### 2. Add Delegate & Callbacks
In **ViewController.m** (or any ViewController that will show ads), import the UnityAds namespace.

```Swift
import UnityAds
```
Make the **ViewController** a **UnityAdsDelegate** and add the four `@required` callbacks.

```swift 

import UnityAds

class ViewController: UIViewController, UnityAdsDelegate {

  override func viewDidLoad() {
    super.viewDidLoad()
  }

  func unityAdsReady(placementId: String) {
    //Called when Unity Ads is ready to show an ad
  }

  func unityAdsDidStart(placementId: String) {
    //Called when Uniy Ads begins playing a video
  }

  func unityAdsDidFinish(placementId: String, withFinishState state: UnityAdsFinishState) {
    //Called when a video completes
  }
  
  func unityAdsDidError(error: UnityAdsError, withMessage message: String) {
  }
}
```

<a name="i3"/>
### 3. Initialize Unity Ads
Initialize Unity Ads by calling `UnityAds.initialize("YOUR_GAME_ID", delegate: self)`

> Note: "YOUR_GAME_ID" is a 7-digit number from the [Unity Ads dashboard](https://dashboard.unityads.unity3d.com). (For example, "1091553")

```swift
 override func viewDidLoad() {
    super.viewDidLoad()
    UnityAds.initialize("YOUR_GAME_ID", delegate: self)
  }
```

<a name="i4"/>
### 4. Show an Ad
In the example project, a button is used to show an ad.

```swift
@IBAction func AdButtonPressed() {
  if(UnityAds.isReady("rewardedVideo")){ //check that a video is ready & the placement is valid
    UnityAds.show(self, placementId: "rewardedVideo")
  }
}

```
> note: By default, leaving the *placement* option blank will show an ad with the default **"video"** placement. (5-second skip)
> Find more information on placements in our [docs](http://unityads.unity3d.com/help/monetization/placements).

<a name="i5"/>
### 5. Reward the Player
The callback `unityAdsDidFinish(...)` is called when a video finishes.

Use `unityAdsDidFinish(...)` to reward the player if they watched the entire ad.

```swift
func unityAdsDidFinish(placementId: String, withFinishState state: UnityAdsFinishState) {
  if(state != .Skipped){
    //video was not skipped, reward the player!
    rewardUserForWatchingAnAd()
  }
}
```

Example project is available [here](https://github.com/Applifier/Unity-Ads-SDK-2.0-Integration-Examples/tree/master/ios)

---
