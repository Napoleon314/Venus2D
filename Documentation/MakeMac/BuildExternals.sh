make -f VeExternals.mak $1 EXT_LIB=zlib
make -f VeExternals.mak $1 EXT_LIB=zziplib PROJECT_FLAGS="-I../../../Externals/zlib -I../../../Externals/zziplib"