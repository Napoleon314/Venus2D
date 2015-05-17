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

cd Binaries/Linux/$1/$2
make -f ../../../../Builds/Linux/VeTest.mak PlatformName=$1 Configuration=$2 ProjectName=$3 VENUS3D_PATH=../../../.. $4
