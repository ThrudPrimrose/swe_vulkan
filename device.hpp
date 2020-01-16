#ifndef DEVICE
#define DEVICE

#include <stdint.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>
#include "helper.hpp"

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class QueueFamilyIndices {
    public:
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily; //nani?

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class device {
    private: 
    public:
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice logicDevice;
        VkQueue gQueue; //initialized here because it created with logical device
        VkBool32 presentSupport = false;
        VkQueue presentQueue;
        VkSurfaceKHR surface;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        
        void pickPhysDevice(VkInstance instance);
        bool isDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        void createLogicalDevice(bool vallayer);
        void setSurface(VkSurfaceKHR i_surface);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void createSwapChain();
        void createImageViews();
        void createGraphicsPipeline();
        VkShaderModule createShaderModule(const std::vector<char>& code);
        ~device();
};

#endif


