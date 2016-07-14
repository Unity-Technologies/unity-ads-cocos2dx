package org.cocos2dx.cpp;

import android.app.Activity;
import android.util.Log;
import com.unity3d.ads.UnityAds;
import com.unity3d.ads.log.DeviceLog;

/**
 * Created by solomonli on 7/8/16.
 */
public class UnityAdsJNI {

    public static Activity activity;
    public static UnityAdsListener unityAdsListener;

    public static native void reward(String placementId);

    // Need update: pass in test mode and game id
    public static void UnityAdsInitialize(String gameId, boolean testMode){
        DeviceLog.debug("[UnityAds Demo] UnityAdsInitialize");
        if(gameId == null || gameId.isEmpty()){
            DeviceLog.debug("[UnityAds Demo] UnityAdsInitialize failed, no gameId specified");
            return;
        }
        UnityAds.initialize(activity, gameId, unityAdsListener, testMode);
    }

    public static boolean UnityAdsIsReady(String placementId) {
        DeviceLog.debug("[UnityAds Demo] UnityAdsIsReady");
        if(placementId == null || placementId.isEmpty()){
            return UnityAds.isReady();
        }
        return UnityAds.isReady(placementId);
    }

    public static void UnityAdsShow(String placementId) {
        DeviceLog.debug("[UnityAds Demo] UnityAdsShow");
        if(placementId == null || placementId.isEmpty()) {
            UnityAds.show(activity);
        } else {
            UnityAds.show(activity, placementId);
        }
    }

    // Other methods, excluded methods that are unreasonable to expose to cpp layer

    public static boolean UnityAdsGetDebugMode(){
        DeviceLog.debug("[UnityAds Demo] UnityAdsGetDebugMode");
        return UnityAds.getDebugMode();
    }

    public static String UnityAdsGetPlacementState(String placementId) {
        if(placementId == null || placementId.isEmpty()) {
            return UnityAds.getPlacementState().toString();
        }
        return UnityAds.getPlacementState(placementId).toString();
    }

    public static String UnityAdsGetVersion() {
        return UnityAds.getVersion();
    }

    public static boolean UnityAdsIsInitialized() {
        return UnityAds.isInitialized();
    }

    public static boolean UnityAdsIsSupported() {
        return UnityAds.isSupported();
    }

    public static void UnityAdsSetDebugMode(boolean debugMode) {
        UnityAds.setDebugMode(debugMode);
    }
}
