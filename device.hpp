#ifndef DEVICE
#define DEVICE

#include <stdint.h>
#include <iostream>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>
#include "helper.hpp"
#include <string.h> 
#include "struct.hpp"


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "imageCreator.hpp"



const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};
class Device {
    private:
    ImageCreator imageCreator;

    public:
    const int MAX_FRAMES_IN_FLIGHT = 2;
    size_t currentFrame = 0;
    

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice logicDevice;
    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;

    uint32_t WIDTH;
    uint32_t HEIGHT;

    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;

    GLFWwindow* window;
    VkBuffer vertexBuffer;
    VkMemoryRequirements memRequirements;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    void pickPhysicalDevice(VkInstance instance,VkSurfaceKHR surface);
    void cleanupSwapChain();
    void recreateSwapChain(GLFWwindow* window, VkSurfaceKHR surface);
    void createLogicalDevice(bool enableValidationLayers,
    std::vector<const char*> validationLayers, VkSurfaceKHR surface);
    void createSwapChain(VkSurfaceKHR surface);
    VkImageView createImageView(VkImage image, VkFormat format);
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createSyncObjects();
    void createCommandBuffers();
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);   
    void createIndexBuffer();
    void createVertexBuffer();
    void createCommandPool(VkSurfaceKHR surface);
    void createFramebuffers();
    void createDescriptorSetLayout();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();


    VkShaderModule createShaderModule(const std::vector<char>& code);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
    bool isDeviceSuitable(VkPhysicalDevice device,VkSurfaceKHR surface);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
    std::vector<const char*> getRequiredExtensions(bool enableValidationLayers);
    bool checkValidationLayerSupport(bool enableValidationLayers,const std::vector<const char*> validationLayers);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    
};

#endif


