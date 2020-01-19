#ifndef IMAGECREATOR
#define IMAGECREATOR

#include <vulkan/vulkan.h>

#include <stb_image.h>
#include <stdexcept>

class ImageCreator {
    private:
    uint32_t findMemoryTypeX(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
    public:
    void createImage(uint32_t width, uint32_t height, 
    VkFormat format, VkImageTiling tiling, 
    VkImageUsageFlags usage, VkMemoryPropertyFlags properties, 
    VkImage& image, VkDeviceMemory& imageMemory,
    VkDevice device, VkPhysicalDevice physicalDevice);
};

#endif