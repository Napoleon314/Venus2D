cd ../..
if [ ! -e Binaries ]; then
	mkdir Binaries
fi
if [ ! -e Binaries/Linux ]; then
	mkdir Binaries/Linux
fi
if [ ! -e Binaries/Linux/$1 ]; then
	mkdir Binaries/Linux/$1
fi

if [ ! -e Binaries/Linux/$1/$2 ]; then
	mkdir Binaries/Linux/$1/$2
fi

if [ ! -e SDK ]; then
	mkdir SDK
fi

if [ ! -e SDK/Include ]; then
	mkdir SDK/Include
fi

if [ ! -e SDK/Linux ]; then
	mkdir SDK/Linux
fi

if [ ! -e SDK/Linux/$1 ]; then
	mkdir SDK/Linux/$1
fi

if [ ! -e SDK/Linux/$1/$2 ]; then
	mkdir SDK/Linux/$1/$2
fi

cd Binaries/Linux/$1/$2
make -f ../../../../Builds/Linux/VeCoreLib.mak PlatformName=$1 Configuration=$2 ProjectName=$3 $4
if [ "$#" = "3" ]; then
	make -f ../../../../Builds/Linux/VeCoreLib.mak PlatformName=$1 Configuration=$2 ProjectName=$3 copy_to_sdk
fi
