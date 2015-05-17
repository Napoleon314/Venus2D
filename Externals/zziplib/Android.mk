LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := zziplib
LOCAL_CFLAGS := -O2 -w -DVE_PLATFORM_ANDROID
LOCAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/%.c,%.c,$(wildcard $(LOCAL_PATH)/*.c))
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_STATIC_LIBRARIES := zlib

include $(BUILD_STATIC_LIBRARY)

$(call import-module,Externals/zlib)
