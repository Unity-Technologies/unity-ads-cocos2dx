package org.cocos2dx.cpp;

import android.util.Log;

import com.unity3d.ads.IUnityAdsListener;
import com.unity3d.ads.UnityAds;

/**
 * Created by solomonli on 7/8/16.
 */
public class UnityAdsListener implements IUnityAdsListener {

    @Override
    public void onUnityAdsReady(final String placementId) {
        Log.d("[UnityAds Demo]", "onUnityAdsReady for placement=" + placementId);
    }

    @Override
    public void onUnityAdsStart(String placementId) {
        Log.d("[UnityAds Demo]", "onUnityAdsStart for placement=" + placementId);
    }

    @Override
    public void onUnityAdsFinish(String placementId, UnityAds.FinishState result) {
        Log.d("[UnityAds Demo]", "onUnityAdsFinish with FinishState=" + result.name() + " for placement=" + placementId);
    }

    @Override
    public void onUnityAdsError(UnityAds.UnityAdsError error, String message) {
        Log.d("[UnityAds Demo]", "onUnityAdsError with message=" + message);
    }
}
