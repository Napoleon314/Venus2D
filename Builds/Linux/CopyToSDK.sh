cd ../../..

if [ ! -e SDK ]; then
	mkdir SDK
fi

if [ ! -e SDK/Include ]; then
	mkdir SDK/Include
fi

if [ ! -e SDK/Linux ]; then
	mkdir SDK/Linux
fi

if [ ! -e SDK/Linux/$2 ]; then
	mkdir SDK/Linux/$2
fi

if [ ! -e SDK/Linux/$2/$3 ]; then
	mkdir SDK/Linux/$2/$3
fi

cp -uv Source/$1/Ve*.h SDK/Include
cp -uv Binaries/Linux/$2/$3/lib$1.$4 SDK/Linux/$2/$3
