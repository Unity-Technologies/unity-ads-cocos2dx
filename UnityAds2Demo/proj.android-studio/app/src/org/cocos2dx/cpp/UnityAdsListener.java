package org.cocos2dx.cpp;

import android.util.Log;

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
