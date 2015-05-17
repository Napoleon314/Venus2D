all :
	$(MAKE) corelibs
	$(MAKE) tests

corelibs :
	sh ./BuildCoreLibs.sh $(PARAM)

tests :
	sh ./BuildCoreLibs.sh $(PARAM)
	sh ./BuildTests.sh $(PARAM)

.PHONY : clean

clean :
	$(MAKE) tests PARAM=clean
	$(MAKE) corelibs PARAM=clean
