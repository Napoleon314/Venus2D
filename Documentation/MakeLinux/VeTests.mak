ARCH = $(shell getconf LONG_BIT)

all :
	$(MAKE) -f VeTests.mak d$(ARCH)
	$(MAKE) -f VeTests.mak r$(ARCH)
	$(MAKE) -f VeTests.mak s$(ARCH)

d :
	$(MAKE) -f VeTests.mak d$(ARCH)

cd :
	$(MAKE) -f VeTests.mak cd$(ARCH)
	
rd :
	$(MAKE) -f VeTests.mak rd$(ARCH)
	
r :
	$(MAKE) -f VeTests.mak r$(ARCH)

cr :
	$(MAKE) -f VeTests.mak cr$(ARCH)
	
rr :
	$(MAKE) -f VeTests.mak rr$(ARCH)
	
s :
	$(MAKE) -f VeTests.mak s$(ARCH)

cs :
	$(MAKE) -f VeTests.mak cs$(ARCH)
	
rs :
	$(MAKE) -f VeTests.mak rs$(ARCH)

d32 :
	sh ./BuildTest.sh i386 Debug $(TEST)

cd32 :
	sh ./BuildTest.sh i386 Debug $(TEST) clean

rd32 :
	$(MAKE) -f VeTests.mak cd32
	$(MAKE) -f VeTests.mak d32

r32 :
	sh ./BuildTest.sh i386 Release $(TEST)

cr32 :
	sh ./BuildTest.sh i386 Release $(TEST) clean

rr32 :
	$(MAKE) -f VeTests.mak cr32
	$(MAKE) -f VeTests.mak r32

s32 :
	sh ./BuildTest.sh i386 Shipping $(TEST)

cs32 :
	sh ./BuildTest.sh i386 Shipping $(TEST) clean

rs32 :
	$(MAKE) -f VeTests.mak cs32
	$(MAKE) -f VeTests.mak s32

d64 :
	sh ./BuildTest.sh amd64 Debug $(TEST)

cd64 :
	sh ./BuildTest.sh amd64 Debug $(TEST) clean

rd64 :
	$(MAKE) -f VeTests.mak cd64
	$(MAKE) -f VeTests.mak d64

r64 :
	sh ./BuildTest.sh amd64 Release $(TEST)

cr64 :
	sh ./BuildTest.sh amd64 Release $(TEST) clean

rr64 :
	$(MAKE) -f VeTests.mak cr64
	$(MAKE) -f VeTests.mak r64

s64 :
	sh ./BuildTest.sh amd64 Shipping $(TEST)

cs64 :
	sh ./BuildTest.sh amd64 Shipping $(TEST) clean

rs64 :
	$(MAKE) -f VeTests.mak cs64
	$(MAKE) -f VeTests.mak s64

.PHONY : clean

clean :
	$(MAKE) -f VeTests.mak cd$(ARCH)
	$(MAKE) -f VeTests.mak cr$(ARCH)
	$(MAKE) -f VeTests.mak cs$(ARCH)
