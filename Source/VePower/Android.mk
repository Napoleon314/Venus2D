LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := VePower

LOCAL_MODULE_FILENAME := libVePower

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_LDLIBS := -llog -landroid

LOCAL_C_INCLUDES := $(LOCAL_PATH)
										
ifeq ($(Configuration),Debug)
LOCAL_CFLAGS := -O0 -Wall -Werror -DVE_DEBUG -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Release)
LOCAL_CFLAGS := -O2 -Wall -Werror -DVE_RELEASE -DVE_MEM_DEBUG
endif

LOCAL_CFLAGS += -DVE_PLATFORM_ANDROID -DVE_STATIC_LIB -DVE_CPU_ARM

LOCAL_CXXFLAGS := $(LOCAL_CFLAGS) -fno-exceptions -fno-rtti

LOCAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/%.cpp,%.cpp,$(wildcard $(LOCAL_PATH)/*.cpp))

LOCAL_STATIC_LIBRARIES := android_native_app_glue raknetlib

include $(BUILD_STATIC_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,Externals/curllib)
$(call import-module,Externals/zziplib)
$(call import-module,Externals/raknetlib)