VULKAN_SDK_PATH = /home/thrud/vulkan/1.1.130.0/x86_64
STB_INCLUDE_PATH = /home/thrud/libraries/stb
TINYOBJ_INCLUDE_PATH = /home/thrud/libraries/tinyobjloader
IMGUI_INCLUDE_PATH = /home/thrud/libraries/imgui

CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include -I$(STB_INCLUDE_PATH) -I$(TINYOBJ_INCLUDE_PATH) -O3
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

VulkanTest: 
	source ~/vulkan/1.1.130.0/setup-env.sh 
	export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json
	g++ $(CFLAGS) -o VulkanTest device.cpp creator.cpp gui.cpp struct.cpp imageCreator.cpp $(LDFLAGS)

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

ruin: goliath
	./goliath

goliath: 
	source ~/vulkan/1.1.130.0/setup-env.sh 
	export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json
	g++ $(CFLAGS) -o goliath goliath.cpp  $(LDFLAGS)

clean:
	rm -f VulkanTest

tidy:
	rm -f goliath
