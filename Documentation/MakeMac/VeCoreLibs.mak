all :
	$(MAKE) -f VeCoreLibs.mak d
	$(MAKE) -f VeCoreLibs.mak r
	$(MAKE) -f VeCoreLibs.mak s

d :
	sh ./BuildCoreLib.sh Debug $(CORE_LIB)

cd :
	sh ./BuildCoreLib.sh Debug $(CORE_LIB) clean

rd :
	$(MAKE) -f VeCoreLibs.mak cd
	$(MAKE) -f VeCoreLibs.mak d

r :
	sh ./BuildCoreLib.sh Release $(CORE_LIB)

cr :
	sh ./BuildCoreLib.sh Release $(CORE_LIB) clean

rr :
	$(MAKE) -f VeCoreLibs.mak cr
	$(MAKE) -f VeCoreLibs.mak r

s :
	sh ./BuildCoreLib.sh Shipping $(CORE_LIB)

cs :
	sh ./BuildCoreLib.sh Shipping $(CORE_LIB) clean

rs :
	$(MAKE) -f VeCoreLibs.mak cs
	$(MAKE) -f VeCoreLibs.mak s

.PHONY : clean

clean :
	$(MAKE) -f VeCoreLibs.mak cd
	$(MAKE) -f VeCoreLibs.mak cr
	$(MAKE) -f VeCoreLibs.mak cs
