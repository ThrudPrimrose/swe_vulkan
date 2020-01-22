#!/bin/sh

echo "source ~/vulkan/1.1.130.0/setup-env.sh"
source ~/vulkan/1.1.130.0/setup-env.sh 
echo "export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json"
export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json

if [ $1 == c ] 
then
    echo "compile and run:"
    make clean
    make run
else
    echo "First->" $1
    echo "only run:"
    make run
fi

