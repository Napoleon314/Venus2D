cd ../../..

if [ ! -e SDK ]; then
	mkdir SDK
fi

if [ ! -e SDK/Include ]; then
	mkdir SDK/Include
fi

if [ ! -e SDK/Include/Externals ]; then
	mkdir SDK/Include/Externals
fi

if [ -e Externals/$1/$1 ]; then
	if [ ! -e SDK/Include/Externals/$1 ]; then
		mkdir SDK/Include/Externals/$1
	fi
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

if [ -e Externals/$1/$1 ]; then
	cp -uv Externals/$1/$1/*.h SDK/Include/Externals/$1
else
	cp -uv Externals/$1/*.h SDK/Include/Externals
fi

cp -uv Binaries/Linux/$2/$3/lib$1.a SDK/Linux/$2/$3
