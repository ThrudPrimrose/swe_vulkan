#!/bin/sh

echo "source ~/vulkan/1.1.130.0/setup-env.sh"
source ~/vulkan/1.1.130.0/setup-env.sh 
echo "export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json"
export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json
echo "compile and run:"
make run 


