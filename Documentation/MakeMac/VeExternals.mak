all :
	$(MAKE) -f VeExternals.mak d
	$(MAKE) -f VeExternals.mak r
	$(MAKE) -f VeExternals.mak s

d :
	sh ./BuildExternal.sh Debug $(EXT_LIB)

cd :
	sh ./BuildExternal.sh Debug $(EXT_LIB) clean

rd :
	$(MAKE) -f VeExternals.mak cd
	$(MAKE) -f VeExternals.mak d

r :
	sh ./BuildExternal.sh Release $(EXT_LIB)

cr :
	sh ./BuildExternal.sh Release $(EXT_LIB) clean

rr :
	$(MAKE) -f VeExternals.mak cr
	$(MAKE) -f VeExternals.mak r

s :
	sh ./BuildExternal.sh Shipping $(EXT_LIB)

cs :
	sh ./BuildExternal.sh Shipping $(EXT_LIB) clean

rs :
	$(MAKE) -f VeExternals.mak cs
	$(MAKE) -f VeExternals.mak s

.PHONY : clean

clean :
	$(MAKE) -f VeExternals.mak cd
	$(MAKE) -f VeExternals.mak cr
	$(MAKE) -f VeExternals.mak cs
