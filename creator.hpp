#ifndef CREATOR
#define CREATOR

#include <vulkan/vulkan.h>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <string>
#include <string.h>
#include "gui.hpp"
#include "device.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
//its not sued here,
//but if not defined here, results in undefined references to bodies
//when included in device -> results in multiple definitions
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const bool enableValidationLayers = true;

class Creator {
public:
    void run();
    

private:
    Gui gui;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    Device dev;

    int height=600;
    int width=800;

    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();
    void drawFrame();
    void updateUniformBuffer(uint32_t currentImage);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, 
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    bool checkValidationLayerSupport();
    void setupDebugMessenger();
    std::vector<const char*> getRequiredExtensions();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance
    , const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo
    , const VkAllocationCallbacks* pAllocator
    , VkDebugUtilsMessengerEXT* pDebugMessenger);

};



#endif