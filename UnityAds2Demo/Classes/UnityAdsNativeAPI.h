//
// Created by Solomon Li on 7/8/16.
//

#ifndef UNITYADS2DEMO_UNITYADSJNI_H
#define UNITYADS2DEMO_UNITYADSJNI_H


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include <jni.h>
    #include "platform/android/jni/JniHelper.h"
#endif

/* implement these functions with sdk api of different platforms */
#ifdef __cplusplus
extern "C" {
#endif

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_UnityAdsJNI_reward (JNIEnv *, jobject, jstring s);
        static char* jstringTostring(JNIEnv* env, jstring jstr);
        static std::string jstringToStdstring(JNIEnv* env, jstring jstr);

        // Unity Ads required methods
        extern void UnityAdsInit(const char* parameter, bool testMode);
        extern bool UnityAdsIsReady (const char* parameter);
        extern void UnityAdsShow (const char* parameter);

        // Unity Ads assist methods
        extern bool UnityAdsGetDebugMode();
        extern std::string UnityAdsGetPlacementState(const char* parameter);
        extern std::string UnityAdsGetVersion();
        extern bool UnityAdsIsInitialized();
        extern bool UnityAdsIsSupported();
        extern void UnityAdsSetDebugMode(bool debugMode);

    #endif
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        // Unity Ads required methods
        void UnityAdsInit (const char *parameter, bool testMode);
        bool UnityAdsIsReady (const char *parameter);
        void UnityAdsShow (const char *parameter);
    
        // Unity Ads assist methods
        bool UnityAdsGetDebugMode();
        std::string UnityAdsGetPlacementState(const char* parameter);
        std::string UnityAdsGetVersion();
        bool UnityAdsIsInitialized();
        bool UnityAdsIsSupported();
        void UnityAdsSetDebugMode(bool debugMode);
    #endif

#ifdef __cplusplus
}
#endif


#endif //UNITYADS2DEMO_UNITYADSJNI_H
