VPATH = ../../../Source/$(ProjectName)

CFLAGS = $(PROJECT_FLAGS)
CFLAGS += -DVE_PLATFORM_OSX -DVE_STATIC_LIB

ifeq ($(Configuration),Debug)
CFLAGS += -O0 -g -Wall -DVE_DEBUG -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Release)
CFLAGS += -O2 -g -Wall -DVE_RELEASE -DVE_MEM_DEBUG
endif

ifeq ($(Configuration),Shipping)
CFLAGS += -O3 -g -Wall -DVE_SHIPPING
endif

CFLAGS += -DVE_CPU_X64
YASM_PLATFORM = macho64

CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti

TARGET_LIB = lib$(ProjectName).a

CXX_OBJS = $(patsubst $(VPATH)/%.cpp,%.o,$(wildcard $(VPATH)/*.cpp))
ASM_OBJS = $(patsubst $(VPATH)/%.asm,%.o,$(wildcard $(VPATH)/*.asm))

OBJS += $(CXX_OBJS)
OBJS += $(ASM_OBJS)

HEADERS = $(patsubst $(VPATH)/%,%,$(wildcard $(VPATH)/*.h))

$(TARGET_LIB) : $(OBJS)
	$(AR) -crv $(TARGET_LIB) $(OBJS)

.PHONY : clean

clean :
	$(RM) $(TARGET_LIB) $(OBJS)

$(CXX_OBJS) : $(HEADERS)

%.o : %.asm
	yasm -f $(YASM_PLATFORM) $^
	
.PHONY : copy_to_sdk

copy_to_sdk :
ifneq ($(wildcard ../../../Source/$(ProjectName)/Ve*.h),)
	cp ../../../Source/$(ProjectName)/Ve*.h ../../../SDK/Include
endif
ifneq ($(wildcard ../../../Source/$(ProjectName)/Ve*.inl),)
	cp ../../../Source/$(ProjectName)/Ve*.inl ../../../SDK/Include
endif
ifneq ($(wildcard ../../../Source/$(ProjectName)/Macosx/Ve*),)
	cp ../../../Source/$(ProjectName)/Macosx/Ve* ../../../SDK/Macosx/VeCocoa
endif
ifneq ($(wildcard *.a),)
	cp *.a ../../../SDK/Macosx/$(Configuration)
endif
