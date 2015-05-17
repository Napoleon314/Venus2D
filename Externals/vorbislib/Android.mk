LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := vorbislib
LOCAL_CFLAGS := -O2 -w -DVE_PLATFORM_ANDROID
LOCAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/lib/%.c,lib/%.c,$(wildcard $(LOCAL_PATH)/lib/*.c))
LOCAL_C_INCLUDES := $(LOCAL_PATH)/lib
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_STATIC_LIBRARIES := ogglib

include $(BUILD_STATIC_LIBRARY)

$(call import-module,Externals/ogglib)
