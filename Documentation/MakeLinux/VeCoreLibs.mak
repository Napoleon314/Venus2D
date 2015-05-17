ARCH = $(shell getconf LONG_BIT)

all :
	$(MAKE) -f VeCoreLibs.mak d$(ARCH)
	$(MAKE) -f VeCoreLibs.mak r$(ARCH)
	$(MAKE) -f VeCoreLibs.mak s$(ARCH)
	
d :
	$(MAKE) -f VeCoreLibs.mak d$(ARCH)

cd :
	$(MAKE) -f VeCoreLibs.mak cd$(ARCH)
	
rd :
	$(MAKE) -f VeCoreLibs.mak rd$(ARCH)
	
r :
	$(MAKE) -f VeCoreLibs.mak r$(ARCH)

cr :
	$(MAKE) -f VeCoreLibs.mak cr$(ARCH)
	
rr :
	$(MAKE) -f VeCoreLibs.mak rr$(ARCH)
	
s :
	$(MAKE) -f VeCoreLibs.mak s$(ARCH)

cs :
	$(MAKE) -f VeCoreLibs.mak cs$(ARCH)
	
rs :
	$(MAKE) -f VeCoreLibs.mak rs$(ARCH)

d32 :
	sh ./BuildCoreLib.sh i386 Debug $(CORE_LIB)

cd32 :
	sh ./BuildCoreLib.sh i386 Debug $(CORE_LIB) clean

rd32 :
	$(MAKE) -f VeCoreLibs.mak cd32
	$(MAKE) -f VeCoreLibs.mak d32

r32 :
	sh ./BuildCoreLib.sh i386 Release $(CORE_LIB)

cr32 :
	sh ./BuildCoreLib.sh i386 Release $(CORE_LIB) clean

rr32 :
	$(MAKE) -f VeCoreLibs.mak cr32
	$(MAKE) -f VeCoreLibs.mak r32

s32 :
	sh ./BuildCoreLib.sh i386 Shipping $(CORE_LIB)

cs32 :
	sh ./BuildCoreLib.sh i386 Shipping $(CORE_LIB) clean

rs32 :
	$(MAKE) -f VeCoreLibs.mak cs32
	$(MAKE) -f VeCoreLibs.mak s32

d64 :
	sh ./BuildCoreLib.sh amd64 Debug $(CORE_LIB)

cd64 :
	sh ./BuildCoreLib.sh amd64 Debug $(CORE_LIB) clean

rd64 :
	$(MAKE) -f VeCoreLibs.mak cd64
	$(MAKE) -f VeCoreLibs.mak d64

r64 :
	sh ./BuildCoreLib.sh amd64 Release $(CORE_LIB)

cr64 :
	sh ./BuildCoreLib.sh amd64 Release $(CORE_LIB) clean

rr64 :
	$(MAKE) -f VeCoreLibs.mak cr64
	$(MAKE) -f VeCoreLibs.mak r64

s64 :
	sh ./BuildCoreLib.sh amd64 Shipping $(CORE_LIB)

cs64 :
	sh ./BuildCoreLib.sh amd64 Shipping $(CORE_LIB) clean

rs64 :
	$(MAKE) -f VeCoreLibs.mak cs64
	$(MAKE) -f VeCoreLibs.mak s64

.PHONY : clean

clean :
	$(MAKE) -f VeCoreLibs.mak cd$(ARCH)
	$(MAKE) -f VeCoreLibs.mak cr$(ARCH)
	$(MAKE) -f VeCoreLibs.mak cs$(ARCH)
