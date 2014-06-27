LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/C2DXShareSDK/Android/ShareSDKUtils.cpp \
				   ../../Classes/C2DXShareSDK/C2DXShareSDK.cpp \
				   ../../Classes/C2DXShareSDK/Android/JSON/CCJSONConverter.cpp \
				   ../../Classes/C2DXShareSDK/Android/JSON/cJSON/cJSON.c \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/SelectMode.cpp \
                   ../../Classes/NormalMode.cpp \
                    ../../Classes/IIIFingerMode.cpp \
                   ../../Classes/Areas.cpp \
                   ../../Classes/Enemys.cpp \
                   ../../Classes/Peoples.cpp \
                   ../../Classes/GameOver.cpp 



LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
				    $(LOCAL_PATH)/../../Classes/C2DXShareSDK \
                    $(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android \
					$(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android/JSON \
					$(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android/JSON/cJSON

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static

LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
#加入这两句build_native.py就不报错
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)

#加入这两句build_native.py就不报错
$(call import-module,extensions)