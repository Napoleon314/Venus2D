VENUS_PATH := $(call my-dir)/../../../../..

include $(VENUS_PATH)/Builds/Android/Android2.3/VePower/Android.mk
include $(VENUS_PATH)/Builds/Android/Android2.3/VeMain/Android.mk

LOCAL_PATH := $(VENUS_PATH)/Tests/VeGraphicsTest

include $(CLEAR_VARS)

LOCAL_MODULE := VeGraphicsTest

ifeq ($(Configuration),Debug)
LOCAL_CFLAGS := -O0 -Wall -Werror -DVE_DEBUG -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Release)
LOCAL_CFLAGS := -O2 -Wall -Werror -DVE_RELEASE -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Shipping)
LOCAL_CFLAGS := -O3 -Wall -Werror -DVE_SHIPPING
endif

LOCAL_CFLAGS += -DVE_PLATFORM_ANDROID -DVE_STATIC_LIB -DVE_CPU_ARM

LOCAL_CXXFLAGS := $(LOCAL_CFLAGS) -fno-exceptions -fno-rtti

LOCAL_C_INCLUDES := $(VENUS_PATH)/Source/VePower $(VENUS_PATH)/Source/VeMain

LOCAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/%.cpp,%.cpp,$(wildcard $(LOCAL_PATH)/*.cpp))

LOCAL_STATIC_LIBRARIES := VeMain VePower android_native_app_glue 

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lOpenSLES

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)

BuildAll:
	ndk-build
	bash ../../CopyResource.sh
	bash ../../CopyToSDK.sh Android-9 $(CPU) $(Configuration)
	