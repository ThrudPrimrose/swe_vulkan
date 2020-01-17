#ifndef CREATOR
#define CREATOR

#include <vulkan/vulkan.h>
#include "gui.hpp"
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include "device.hpp"
#include "debug_tools.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;


class Creator {
public:
    void run();
    Creator();

private:
    gui interface;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    device gDevice;
    
    size_t currentFrame = 0;

    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();
    void drawFrame(device gDevice);
};



#endif