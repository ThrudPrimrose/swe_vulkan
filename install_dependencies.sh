#!/bin/sh

echo "clone dependecies:"
cd ~/

echo "creating libraries folder:"

if [ -d "libraries" ] 
then
	echo "libraries folder exist"
else
	echo "create libraries"
	mkdir libraries
fi


cd libraries

echo "trying to clone stb: "

if [ -d "stb" ]
then
	echo "stb already cloned"
else
	echo "clone stb"
	folder="stb"
	url="https://github.com/nothings/stb.git"
	git clone ${url} ${folder}
fi

if [ -d "imgui" ]
then
	echo "imgui already cloned"
else
	echo "clone imgui"
	folder="imgui"
	url="https://github.com/ocornut/imgui.git"
	git clone ${url} ${folder}
fi


if [ -d "tinyobjloader" ]
then
	echo "tinyobjloader already cloned"
else
	folder="tinyobjloader"
	url="https://github.com/syoyo/tinyobjloader.git"
	git clone ${url} ${folder}
fi

version=1.2.148.1
if [ -f "vulkan.tar.gz" ]
then
	echo "vulkan already downloaded"
else
	echo "download vulkan"
	curl https://sdk.lunarg.com/sdk/download/${version}/linux/vulkansdk-linux-x86_64-${version}.tar.gz -o vulkan.tar.gz
fi

if [ -d "vulkansdk" ]
then
	echo "vulkan sdl already installed"
else
	tar -xzvf vulkan.tar.gz
	mv ${PWD}/${version} "${PWD}/vulkansdk"
fi





