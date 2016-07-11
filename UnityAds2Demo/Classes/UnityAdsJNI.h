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
        extern void UnityAdsInit ();
        extern bool UnityAdsIsReady (const char *parameter);
        extern void UnityAdsShow (const char *parameter);
    #endif

#ifdef __cplusplus
}
#endif


#endif //UNITYADS2DEMO_UNITYADSJNI_H
