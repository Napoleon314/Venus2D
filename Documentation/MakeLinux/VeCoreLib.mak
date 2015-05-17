VPATH = ../../../../Source/$(ProjectName)

CFLAGS = $(PROJECT_FLAGS)
CFLAGS += -DVE_PLATFORM_LINUX -DVE_STATIC_LIB

ifeq ($(Configuration),Debug)
CFLAGS += -O0 -g -Wall -DVE_DEBUG -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Release)
CFLAGS += -O2 -g -Wall -DVE_RELEASE -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Shipping)
CFLAGS += -O3 -Wall -DVE_SHIPPING
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

CXX_OBJS = $(patsubst $(VPATH)/%.cpp,%.o,$(wildcard $(VPATH)/*.cpp))
ASM_OBJS = $(patsubst $(VPATH)/%.asm,%.o,$(wildcard $(VPATH)/*.asm))

OBJS += $(CXX_OBJS)
OBJS += $(ASM_OBJS)

HEADERS = $(patsubst $(VPATH)/%,%,$(wildcard $(VPATH)/*.h))

$(TARGET_LIB) : $(OBJS)
	$(AR) -crv $(TARGET_LIB) $(OBJS)
#	$(LD) -shared -fpic -o x.so $(OBJS) 

.PHONY : clean

clean :
	$(RM) $(TARGET_LIB) $(OBJS)

$(CXX_OBJS) : $(HEADERS)

%.o : %.asm
	yasm -f $(YASM_PLATFORM) $^

.PHONY : copy_to_sdk

copy_to_sdk :
ifneq ($(wildcard ../../../../Source/$(ProjectName)/Ve*.h),)
	cp -uv ../../../../Source/$(ProjectName)/Ve*.h ../../../../SDK/Include
endif
ifneq ($(wildcard ../../../../Source/$(ProjectName)/Ve*.inl),)
	cp -uv ../../../../Source/$(ProjectName)/Ve*.inl ../../../../SDK/Include
endif
ifneq ($(wildcard *.a),)
	cp -uv *.a ../../../../SDK/Linux/$(PlatformName)/$(Configuration)
endif

