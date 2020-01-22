#!/bin/sh

echo "clone dependecies:"
cd ~/

echo "creating libraries folder:"
[ -d libraries ] && echo "libraries folder do exist"

[ -d libraries ] || mkdir libraries

cd libraries

echo "trying to clone stb: "
folder="stb"
url="https://github.com/nothings/stb.git"
if ! git clone "${url}" "${folder}" 2>/dev/null && [ -d "${folder}" ] ; then
    echo "Clone failed because the folder ${folder} exists"
fi

echo="trying to clone imgui:"
folder="imgui"
url="https://github.com/ocornut/imgui.git"
if ! git clone "${url}" "${folder}" 2>/dev/null && [ -d "${folder}" ] ; then
    echo "Clone failed because the folder ${folder} exists"
fi

echo="trying to clone tinyobjloader:"
folder="tinyobjloader"
url="https://github.com/syoyo/tinyobjloader.git"
if ! git clone "${url}" "${folder}" 2>/dev/null && [ -d "${folder}" ] ; then
    echo "Clone failed because the folder ${folder} exists"
fi

echo "dependencies cloned"
echo "you need to install vulkanSDK by hand!!"
echo "and change the makefile!!"