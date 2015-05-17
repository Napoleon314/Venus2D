LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= curllib
LOCAL_CFLAGS := -O2 -w -DVE_PLATFORM_ANDROID -DHAVE_CONFIG_H -DBUILDING_LIBCURL -DCURL_STATICLIB -DVE_PLATFORM_IOS
LOCAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/%.c,%.c,$(wildcard $(LOCAL_PATH)/*.c))
LOCAL_C_INCLUDES := $(LOCAL_PATH)/Android
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

include $(BUILD_STATIC_LIBRARY)
