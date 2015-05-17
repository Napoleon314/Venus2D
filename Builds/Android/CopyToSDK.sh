if [ ! -e ../../../../SDK ]; then
	mkdir ../../../../SDK
fi

if [ ! -e ../../../../SDK/Include ]; then
	mkdir ../../../../SDK/Include
fi

if [ ! -e ../../../../SDK/Android ]; then
	mkdir ../../../../SDK/Android
fi


if [ ! -e ../../../../SDK/Android/$1 ]; then
	mkdir ../../../../SDK/Android/$1
fi

if [ ! -e ../../../../SDK/Android/$1/$2 ]; then
	mkdir ../../../../SDK/Android/$1/$2
fi

if [ ! -e ../../../../SDK/Android/$1/$2/$3 ]; then
	mkdir ../../../../SDK/Android/$1/$2/$3
fi

cp ../../../../Source/VePower/Ve*.h ../../../../SDK/Include
cp ../../../../Source/VePower/Ve*.inl ../../../../SDK/Include
cp ../../../../Source/VeMain/Ve*.h ../../../../SDK/Include
cp ../../../../Source/VeMain/Ve*.inl ../../../../SDK/Include

cp obj/local/$2/libVe*.a ../../../../SDK/Android/$1/$2/$3
cp obj/local/$2/lib*lib.a ../../../../SDK/Android/$1/$2/$3
