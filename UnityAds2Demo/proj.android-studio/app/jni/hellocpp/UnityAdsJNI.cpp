//
// Created by Solomon Li on 7/8/16.
//

#include "UnityAdsNativeAPI.h"
#include <android/log.h>
#include "HelloWorldScene.h"
#include "AppDelegate.h"
#include "cocos2d.h"

#define LOG_TAG    "UnityAdsJNI"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define CLASS_NAME "org/cocos2dx/cpp/UnityAdsJNI"

using namespace cocos2d;


#ifdef __cplusplus
extern "C" {
#endif

    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_UnityAdsJNI_reward (JNIEnv * env, jobject jobj, jstring zoneid)
    {
        char* ret = NULL;
		ret = jstringTostring(env, zoneid);

        LOGD("placement id = %s", ret);

        auto scene = Director::getInstance()->getRunningScene()->getChildren().at(1);

        if (typeid(*scene) == typeid(HelloWorld)) {
            static_cast<HelloWorld*>(scene)->rewardPlayer(ret);
        } else {
            LOGD("gameScene is still NULL");
        }
    }

	static char* jstringTostring(JNIEnv* env, jstring jstr)
	{
		char* rtn = NULL;

		// convert jstring to byte array
		jclass clsstring = env->FindClass("java/lang/String");
		jstring strencode = env->NewStringUTF("utf-8");
		jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
		jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
		jsize alen =  env->GetArrayLength(barr);
		jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);

		// copy byte array into char[]
		if (alen > 0)
		{
			rtn = new char[alen + 1];
			memcpy(rtn, ba, alen);
			rtn[alen] = 0;
		}
		env->ReleaseByteArrayElements(barr, ba, 0);

		return rtn;
	}

	static std::string jstringToStdstring(JNIEnv* env, jstring jstr) {

        char* cstring = NULL;
        cstring = jstringTostring(env, jstr);
        //std::string returnString;
        //returnString = std::string str(cstring);
        std::string str(cstring);
        return str;
	}

    void UnityAdsInit(const char* parameter, bool testMode) {

        JniMethodInfo methodInfo;

        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "UnityAdsInitialize", "(Ljava/lang/String;Z)V"))
        {
            LOGD("Failed to find static method of UnityAdsInitialize");
            return;
        }

        jstring gameId = methodInfo.env->NewStringUTF(parameter);

        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, gameId, testMode);
    }

    bool UnityAdsIsReady(const char *parameter)
    {

        JniMethodInfo methodInfo;

        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "UnityAdsIsReady", "(Ljava/lang/String;)Z"))
        {
            LOGD("Failed to find static method of UnityAdsIsReady");
            return false;
        }

        jstring placementId = methodInfo.env->NewStringUTF(parameter);
        jboolean ans = (jboolean)methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, placementId);

        bool ret = false;
        if(JNI_TRUE == ans)ret = true;
        return ret;
    }

    void UnityAdsShow(const char *parameter)
    {

        JniMethodInfo methodInfo;

        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "UnityAdsShow", "(Ljava/lang/String;)V"))
        {
            LOGD("Failed to find static method of UnityAdsShow");
            return;
        }

        jstring placementId = methodInfo.env->NewStringUTF(parameter);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, placementId);

    }

    bool UnityAdsGetDebugMode() {
        JniMethodInfo methodInfo;

        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "UnityAdsGetDebugMode", "()Z"))
        {
            LOGD("Failed to find static method of UnityAdsGetDebugMode");
            return false;
        }

        jboolean ans = (jboolean)methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);

        bool ret = false;
        if(JNI_TRUE == ans)ret = true;
        return ret;
    }

    std::string UnityAdsGetPlacementState(const char* parameter) {

        JniMethodInfo methodInfo;

        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "UnityAdsGetPlacementState", "(Ljava/lang/String;)Ljava/lang/String"))
        {
            LOGD("Failed to find static method of UnityAdsGetPlacementState");
            return false;
        }

        jstring placementId = methodInfo.env->NewStringUTF(parameter);
        jstring ans = (jstring)methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, placementId);

        std::string returnString;
        returnString = jstringToStdstring(methodInfo.env, ans);

        return returnString;
    }

    std::string UnityAdsGetVersion() {

        JniMethodInfo methodInfo;

        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "UnityAdsGetVersion", "()Ljava/lang/String"))
        {
            LOGD("Failed to find static method of UnityAdsGetVersion");
            return false;
        }
        jstring ans = (jstring)methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);

        std::string returnString;
        returnString = jstringToStdstring(methodInfo.env, ans);

        return returnString;
    }

    bool UnityAdsIsInitialized() {
        JniMethodInfo methodInfo;

        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "UnityAdsIsInitialized", "()Z"))
        {
            LOGD("Failed to find static method of UnityAdsIsInitialized");
            return false;
        }

        jboolean ans = (jboolean)methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);

        bool ret = false;
        if(JNI_TRUE == ans)ret = true;
        return ret;
    }

    bool UnityAdsIsSupported() {
        JniMethodInfo methodInfo;

        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "UnityAdsIsSupported", "()Z"))
        {
            LOGD("Failed to find static method of UnityAdsIsSupported");
            return false;
        }

        jboolean ans = (jboolean)methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);

        bool ret = false;
        if(JNI_TRUE == ans)ret = true;
        return ret;
    }

    void UnityAdsSetDebugMode(bool testMode) {
        JniMethodInfo methodInfo;

        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "UnityAdsSetDebugMode", "(Z;)V"))
        {
            LOGD("Failed to find static method of UnityAdsSetDebugMode");
            return;
        }

        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, testMode);
    }

#ifdef __cplusplus
}
#endif
