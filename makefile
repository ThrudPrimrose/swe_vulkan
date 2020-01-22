VULKAN_SDK_PATH = /home/$$USERNAME/vulkan/1.1.130.0/x86_64
STB_INCLUDE_PATH = /home/$$USERNAME/libraries/stb
TINYOBJ_INCLUDE_PATH = /home/$$USERNAME/libraries/tinyobjloader
IMGUI_INCLUDE_PATH = /home/$$USERNAME/libraries/imgui
IMGUI_EXMPL_INCLUDE_PATH = /home/$$USERNAME/libraries/imgui/examples

CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include -I$(STB_INCLUDE_PATH) -I$(TINYOBJ_INCLUDE_PATH)  -I$(IMGUI_INCLUDE_PATH) -I$(IMGUI_EXMPL_INCLUDE_PATH) -O3
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib  -L$(TINYOBJ_INCLUDE_PATH) ` pkg-config --static --libs glfw3` -lvulkan

VulkanTest: 
	g++ $(CFLAGS) $(LDFLAGS) -o VulkanTest *.cpp 

.PHONY: test clean

test: VulkanTest
	./VulkanTest

run:
	make
	make test

ruin: goliath
	./goliath

goliath: 
	g++ $(CFLAGS) -o goliath goliath.cpp  $(LDFLAGS)

clean:
	rm -f VulkanTest
	rm -f twod

tidy:
	rm -f goliath

twod:
	g++ -D TWOD $(CFLAGS) $(LDFLAGS) -o twod *.cpp
	./twod
