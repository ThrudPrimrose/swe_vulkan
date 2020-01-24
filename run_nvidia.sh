#!/bin/sh

echo "source ~/vulkan/1.1.130.0/setup-env.sh"
source ~/vulkan/1.1.130.0/setup-env.sh 
echo "export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json"
export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json

if [ $1 == c ] 
then
	if [ $2 == twod ] 
	then
	    echo "compile 2D and run:"
	    make clean
	    make twod
	    make twodrun
	fi
	if [ $2 == thrid ]
	then 
	    echo "compile 3D and run:"
	    make clean
	    make thid
	    make thidrun
	else
	    echo "compile and run:"
	    make clean
	    make run
	fi
else
	if [ $2 == twod ] 
	then
	    echo "First->" $1
	    echo "Second->" $2
	    echo "only 2D run:"
	    make twodrun
	fi
	if [ $2 == thrid ]
	then
	    echo "First->" $1
	    echo "Second->" $2
	    echo "only 3D run:"
	    make thridrun
	else
	    echo "First->" $1
	    echo "only run:"
	    make run
	fi
fi
