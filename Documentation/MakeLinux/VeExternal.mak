VPATH = ../../../../Externals/$(ProjectName)

CFLAGS = $(PROJECT_FLAGS)
CFLAGS += -DVE_PLATFORM_LINUX -DVE_STATIC_LIB

ifeq ($(Configuration),Debug)
CFLAGS += -O0 -g -DVE_DEBUG -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Release)
CFLAGS += -O2 -g -DVE_RELEASE -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Shipping)
CFLAGS += -O3 -DVE_SHIPPING
endif

ifeq ($(PlatformName),i386)
CFLAGS += -march=pentium4 -mmmx -DVE_CPU_X86 -m32
YASM_PLATFORM = elf32
endif

ifeq ($(PlatformName),amd64)
CFLAGS += -DVE_CPU_X64 -m64
YASM_PLATFORM = elf64
endif

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
ifneq ($(wildcard ../../../../Externals/$(ProjectName)/$(ProjectName)/*.h),)
	cp -uv ../../../../Externals/$(ProjectName)/$(ProjectName)/*.h ../../../../SDK/Include/Externals/$(ProjectName)
else
ifneq ($(wildcard ../../../../Externals/$(ProjectName)/*.h),)
	cp -uv ../../../../Externals/$(ProjectName)/*.h ../../../../SDK/Include/Externals
endif
endif
ifneq ($(wildcard *.a),)
	cp -uv *.a ../../../../SDK/Linux/$(PlatformName)/$(Configuration)
endif

