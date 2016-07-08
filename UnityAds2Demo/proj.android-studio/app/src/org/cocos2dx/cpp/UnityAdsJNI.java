package org.cocos2dx.cpp;

import android.app.Activity;
import android.util.Log;
import com.unity3d.ads.UnityAds;

/**
 * Created by solomonli on 7/8/16.
 */
public class UnityAdsJNI {
    private static String gameId = "18030";
    public static Activity activity;
    public static UnityAdsListener unityAdsListener;

    public static void UnityAdsInitialize(){
        Log.d("[UnityAds Demo]", "UnityAdsInitialize");
        UnityAds.initialize(activity, gameId, unityAdsListener);
    }

    public static boolean UnityAdsIsReady(String placementId) {
        Log.d("[UnityAds Demo]", "UnityAdsIsReady");
        return UnityAds.isReady(placementId);
    }

    public static void UnityAdsShow(String placementId) {
        Log.d("[UnityAds Demo]", "showUnityAds");
        UnityAds.show(activity, placementId);
    }

//    public static native void reward(String placementId);
}
