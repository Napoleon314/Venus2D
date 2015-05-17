ARCH = $(shell getconf LONG_BIT)

all :
	$(MAKE) -f VeExternals.mak d$(ARCH)
	$(MAKE) -f VeExternals.mak r$(ARCH)
	$(MAKE) -f VeExternals.mak s$(ARCH)
	
d :
	$(MAKE) -f VeExternals.mak d$(ARCH)

cd :
	$(MAKE) -f VeExternals.mak cd$(ARCH)
	
rd :
	$(MAKE) -f VeExternals.mak rd$(ARCH)
	
r :
	$(MAKE) -f VeExternals.mak r$(ARCH)

cr :
	$(MAKE) -f VeExternals.mak cr$(ARCH)
	
rr :
	$(MAKE) -f VeExternals.mak rr$(ARCH)
	
s :
	$(MAKE) -f VeExternals.mak s$(ARCH)

cs :
	$(MAKE) -f VeExternals.mak cs$(ARCH)
	
rs :
	$(MAKE) -f VeExternals.mak rs$(ARCH)

d32 :
	sh ./BuildExternal.sh i386 Debug $(EXT_LIB)

cd32 :
	sh ./BuildExternal.sh i386 Debug $(EXT_LIB) clean

rd32 :
	$(MAKE) -f VeExternals.mak cd32
	$(MAKE) -f VeExternals.mak d32

r32 :
	sh ./BuildExternal.sh i386 Release $(EXT_LIB)

cr32 :
	sh ./BuildExternal.sh i386 Release $(EXT_LIB) clean

rr32 :
	$(MAKE) -f VeExternals.mak cr32
	$(MAKE) -f VeExternals.mak r32

s32 :
	sh ./BuildExternal.sh i386 Shipping $(EXT_LIB)

cs32 :
	sh ./BuildExternal.sh i386 Shipping $(EXT_LIB) clean

rs32 :
	$(MAKE) -f VeExternals.mak cs32
	$(MAKE) -f VeExternals.mak s32

d64 :
	sh ./BuildExternal.sh amd64 Debug $(EXT_LIB)

cd64 :
	sh ./BuildExternal.sh amd64 Debug $(EXT_LIB) clean

rd64 :
	$(MAKE) -f VeExternals.mak cd64
	$(MAKE) -f VeExternals.mak d64

r64 :
	sh ./BuildExternal.sh amd64 Release $(EXT_LIB)

cr64 :
	sh ./BuildExternal.sh amd64 Release $(EXT_LIB) clean

rr64 :
	$(MAKE) -f VeExternals.mak cr64
	$(MAKE) -f VeExternals.mak r64

s64 :
	sh ./BuildExternal.sh amd64 Shipping $(EXT_LIB)

cs64 :
	sh ./BuildExternal.sh amd64 Shipping $(EXT_LIB) clean

rs64 :
	$(MAKE) -f VeExternals.mak cs64
	$(MAKE) -f VeExternals.mak s64

.PHONY : clean

clean :
	$(MAKE) -f VeExternals.mak cd$(ARCH)
	$(MAKE) -f VeExternals.mak cr$(ARCH)
	$(MAKE) -f VeExternals.mak cs$(ARCH)
