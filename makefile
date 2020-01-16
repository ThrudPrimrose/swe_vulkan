VULKAN_SDK_PATH = /home/thrud/vulkan/1.1.130.0/x86_64
STB_INCLUDE_PATH = /home/thrud/libraries/stb
TINYOBJ_INCLUDE_PATH = /home/thrud/libraries/tinyobjloader

CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include -I$(STB_INCLUDE_PATH) -I$(TINYOBJ_INCLUDE_PATH) 
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

VulkanTest: creator.cpp
	source ~/vulkan/1.1.130.0/setup-env.sh 
	export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json
	g++ $(CFLAGS) -o VulkanTest creator.cpp gui.cpp device.cpp $(LDFLAGS) -O3

.PHONY: test clean

test: VulkanTest
	source ~/vulkan/1.1.130.0/setup-env.sh 
	export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json
	export QT_X11_NO_MITSHM=1
	export LIBOVERLAY_SCROLLBAR=0
	./VulkanTest

run:
	make
	make test

clean:
	rm -f VulkanTest
