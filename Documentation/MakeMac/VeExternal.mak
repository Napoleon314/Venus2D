ifneq ($(wildcard ../../../Externals/$(ProjectName)/$(ProjectName)),)
VPATH = ../../../Externals/$(ProjectName)/$(ProjectName)
else
VPATH = ../../../Externals/$(ProjectName)
endif

CFLAGS = $(PROJECT_FLAGS)
CFLAGS += -DVE_PLATFORM_OSX -DVE_STATIC_LIB

ifeq ($(Configuration),Debug)
CFLAGS += -O0 -g -DVE_DEBUG -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Release)
CFLAGS += -O2 -g -DVE_RELEASE -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Shipping)
CFLAGS += -O3 -g -DVE_SHIPPING
endif

CFLAGS += -DVE_CPU_X64
YASM_PLATFORM = macho64

CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti

TARGET_LIB = lib$(ProjectName).a

C_OBJS = $(patsubst $(VPATH)/%.c,%.o,$(wildcard $(VPATH)/*.c))
CXX_OBJS = $(patsubst $(VPATH)/%.cpp,%.o,$(wildcard $(VPATH)/*.cpp))

OBJS += $(C_OBJS)
OBJS += $(CXX_OBJS)

$(TARGET_LIB) : $(OBJS)
	$(AR) -crv $(TARGET_LIB) $(OBJS)

.PHONY : clean

clean :
	$(RM) $(TARGET_LIB) $(OBJS)
	
.PHONY : copy_to_sdk

copy_to_sdk :
	@echo $(HEADERS)
ifneq ($(wildcard ../../../Externals/$(ProjectName)/*.h),)
	cp ../../../Externals/$(ProjectName)/*.h ../../../SDK/Include/Externals
endif
ifneq ($(wildcard ../../../Externals/$(ProjectName)/$(ProjectName)/*.h),)
	cp ../../../Externals/$(ProjectName)/$(ProjectName)/*.h ../../../SDK/Include/Externals/$(ProjectName)
endif
ifneq ($(wildcard *.a),)
	cp *.a ../../../SDK/Macosx/$(Configuration)
endif
