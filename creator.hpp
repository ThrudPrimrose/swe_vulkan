#ifndef CREATOR
#define CREATOR

#include <vulkan/vulkan.h>
#include "gui.hpp"
#include "debug_tools.hpp"
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include "device.hpp"


class Creator {
public:
    void run();
    Creator();

private:
    gui interface;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    device gDevice;

    bool val_layer;

    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();
};



#endif