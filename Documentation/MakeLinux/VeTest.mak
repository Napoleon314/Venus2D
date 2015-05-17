VPATH = ../../../../Tests/$(ProjectName)

CFLAGS = $(PROJECT_FLAGS)
CFLAGS += -DVE_PLATFORM_LINUX -DVE_STATIC_LIB -DVE_USER

ifeq ($(Configuration),Debug)
CFLAGS += -O0 -g -Wall -DVE_DEBUG -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Release)
CFLAGS += -O2 -g -Wall -DVE_RELEASE -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Shipping)
CFLAGS += -O3 -g -Wall -DVE_SHIPPING
endif

ifeq ($(PlatformName),i386)
CFLAGS += -march=pentium4 -mmmx -DVE_CPU_X86 -m32
YASM_PLATFORM = elf32
endif

ifeq ($(PlatformName),amd64)
CFLAGS += -DVE_CPU_X64 -m64
YASM_PLATFORM = elf64
endif

CFLAGS += -I$(VENUS3D_PATH)/SDK/Include

CFLAGS += -L$(VENUS3D_PATH)/SDK/Linux/$(PlatformName)/$(Configuration)

CFLAGS += $(patsubst $(VENUS3D_PATH)/SDK/Linux/$(PlatformName)/$(Configuration)/lib%.a,-l%,$(wildcard $(VENUS3D_PATH)/SDK/Linux/$(PlatformName)/$(Configuration)/*.a))

CFLAGS += -ldl -lX11 -lXrandr -lpthread -lzlib -lzziplib -lcurllib -lrtmp -lidn -lrt

CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti

TARGET = $(ProjectName)

CXX_OBJS = $(patsubst $(VPATH)/%.cpp,%.o,$(wildcard $(VPATH)/*.cpp))
ASM_OBJS = $(patsubst $(VPATH)/%.asm,%.o,$(wildcard $(VPATH)/*.asm))

OBJS += $(CXX_OBJS)
OBJS += $(ASM_OBJS)

HEADERS = $(patsubst $(VPATH)/%,%,$(wildcard $(VPATH)/*.h))

$(TARGET) : $(OBJS) $(patsubst $(VENUS3D_PATH)/SDK/Linux/$(PlatformName)/$(Configuration)/%.a,%.a,$(wildcard $(VENUS3D_PATH)/SDK/Linux/$(PlatformName)/$(Configuration)/*.a))
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAGS)

.PHONY : clean

clean :
	$(RM) $(TARGET) $(OBJS)

$(CXX_OBJS) : $(HEADERS)

%.o : %.asm
	yasm -f $(YASM_PLATFORM) $^
