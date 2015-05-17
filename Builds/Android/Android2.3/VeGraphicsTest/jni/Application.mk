ifeq ($(Configuration),Debug)
APP_ABI := $(CPU)
APP_PLATFORM := android-9
APP_OPTIM := debug
endif
ifeq ($(Configuration),Release)
APP_ABI := $(CPU)
APP_PLATFORM := android-9
APP_OPTIM := release
endif
ifeq ($(Configuration),Shipping)
APP_ABI := $(CPU)
APP_PLATFORM := android-9
APP_OPTIM := release
endif
