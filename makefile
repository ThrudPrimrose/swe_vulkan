VULKAN_SDK_PATH = /home/$$USERNAME/vulkan/1.1.130.0/x86_64
STB_INCLUDE_PATH = /home/$$USERNAME/libraries/stb
TINYOBJ_INCLUDE_PATH = /home/$$USERNAME/libraries/tinyobjloader
IMGUI_INCLUDE_PATH = /home/$$USERNAME/libraries/imgui
IMGUI_EXMPL_INCLUDE_PATH = /home/$$USERNAME/libraries/imgui/examples
NETCDF = /usr/local

CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include -I$(STB_INCLUDE_PATH) -I$(TINYOBJ_INCLUDE_PATH)  -I$(IMGUI_INCLUDE_PATH) -I$(IMGUI_EXMPL_INCLUDE_PATH) -I$(NETCDF)/include -O3
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib  -L$(TINYOBJ_INCLUDE_PATH) -L$(NETCDF)/lib ` pkg-config --static --libs glfw3` -lvulkan 

VulkanTest: 
	g++ -Wl,-rpath=/usr/local/lib $(CFLAGS)  -letcdf $(LDFLAGS) -o VulkanTest *.cpp  

.PHONY: test clean

test: VulkanTest
	./VulkanTest

run:
	make
	make test

ruin: goliath
	./goliath

goliath: 
	g++ -Wl,-rpath=/usr/local/lib $(CFLAGS) -o goliath goliath.cpp  -lnetcdf $(LDFLAGS)

clean:
	rm -f VulkanTest
	rm -f twod

tidy:
	rm -f goliath

twod:
	g++ -Wl,-rpath=/usr/local/lib -D TWOD $(CFLAGS) -lnetcdf $(LDFLAGS) -o twod *.cpp  
	./twod
