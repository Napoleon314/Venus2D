cd ../..
if [ ! -e Binaries ]; then
	mkdir Binaries
fi
if [ ! -e Binaries/Macosx ]; then
	mkdir Binaries/Macosx
fi
if [ ! -e Binaries/Macosx/$1 ]; then
	mkdir Binaries/Macosx/$1
fi

if [ ! -e SDK ]; then
	mkdir SDK
fi

if [ ! -e SDK/Include ]; then
	mkdir SDK/Include
fi

if [ ! -e SDK/Macosx ]; then
	mkdir SDK/Macosx
fi

if [ ! -e SDK/Macosx/$1 ]; then
	mkdir SDK/Macosx/$1
fi

if [ ! -e SDK/Macosx/VeCocoa ]; then
	mkdir SDK/Macosx/VeCocoa
fi

cd Binaries/Macosx/$1
make -f ../../../Builds/Macosx/VeCoreLib.mak Configuration=$1 ProjectName=$2 $3
if [ "$#" = "2" ]; then
	make -f ../../../Builds/Macosx/VeCoreLib.mak Configuration=$1 ProjectName=$2 copy_to_sdk
fi
