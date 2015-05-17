LOCAL_PATH := $(VENUS_PATH)/Source/VePower

include $(CLEAR_VARS)

LOCAL_MODULE := VePower

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

LOCAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/%.cpp,%.cpp,$(wildcard $(LOCAL_PATH)/*.cpp))

LOCAL_STATIC_LIBRARIES := android_native_app_glue zziplib curllib lualib raknetlib

include $(BUILD_STATIC_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,Externals/zziplib)
$(call import-module,Externals/curllib)
$(call import-module,Externals/lualib)
$(call import-module,Externals/raknetlib)
