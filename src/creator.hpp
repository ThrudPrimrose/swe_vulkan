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
#include <chrono>

#ifdef TWOD
    #include "device2D.hpp"
    #include "netcdfreader/ncReader2D.hpp"
#else
    #ifdef THRID
        #include "device3D.hpp"
        #include "netcdfreader/ncReader3D.hpp"
    #else
        #include "deviceTexture.hpp"
    #endif
#endif 

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
    
    #ifdef TWOD
        Device2D dev;
    #else
        #ifdef THRID
            Device3D dev;
        #else
            DeviceTexture dev;
        #endif
    #endif 

    int textureCount = 2; //total count of textures to be loaded
    //device loads textures with functions of 0 zero arguments
    //but the functions depends on tInd count
    //which governed by creator through appropriate calls
    std::vector<std::string> textureNames = {"textures/ground.png", 
    "textures/water.png"};
    int height=600;
    int width=800;

    float rotSpeed = 90.0f;
    float lookX = -0.5f;
    float lookY = -0.5f;
    float lookZ = 5.0f;
    float angle = 60.0f;

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point now;

    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();
    void drawFrame();
    void updateUniformBuffer(uint32_t currentImage);
    void changeView(MoveInfo move_msg);

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