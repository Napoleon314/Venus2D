all :
	$(MAKE) corelibs

corelibs :
	sh ./BuildCoreLibs.sh $(PARAM)

.PHONY : clean

clean :
	$(MAKE) corelibs PARAM=clean
