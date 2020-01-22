#ifndef DEVICETEXTURE
#define DEVICETEXTURE

/*#include <stdint.h>
#include <iostream>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>
#include "helper.hpp"
#include <string.h> 
#include "struct.hpp"
*/
 //these are included in device
#include "device.hpp"
#include "imageCreator.hpp"




struct Texture {
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;
    VkBuffer tiStagingBuffer;
    VkDeviceMemory tiStagingBufferMemory;
    std::vector<VkDescriptorSet> descriptorSets;
    VkBuffer tBuffer;
    VkDeviceMemory tBufferMemory;
  
};

class DeviceTexture : public Device {
    private:
    ImageCreator imageCreator;

    public:
    int max_texture_count=2;
   

    uint32_t tInd = 0; //changed for texture
    Texture texture[2]; //changed for texture
   

    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
  


    
    void createGraphicsPipeline(); //changed for texture
    
    void createCommandBuffers(); //changed for texture
    
    void createVertexBuffer(); //changed for texture
    void createDescriptorSetLayout();
    void createIndexBuffer();
    void createCommandPool(VkSurfaceKHR surface);
    
    void createDescriptorPool(); //changed for texture
    void createDescriptorSets(); //changed for texture
    void createTextureImage(std::string path); //changed for texture
    void createTextureImageView(); //changed for texture
    void createTextureSampler(); //changed for texture
    void recreateSwapChain(GLFWwindow* window, VkSurfaceKHR surface);
    VkImageView createImageView(VkImage image, VkFormat format);
    void createImageViews();
    
    //changed for texture 
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    
};

#endif


