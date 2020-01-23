#ifndef DEVICE2D
#define DEVICE2D

#include "device.hpp"

class Device2D : public Device {
    public:
    //in texture we initialized these per texture
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    NcReader ncReader; //this variant not like in swe has to be initialized

    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;

    void createGraphicsPipeline();
    
    void createCommandBuffers();

    void createVertexBuffer();
    void createIndexBuffer();
    void createCommandPool(VkSurfaceKHR surface);

    void createDescriptorPool();
    void createDescriptorSets();
    void createDescriptorSetLayout();
    void recreateSwapChain(GLFWwindow* window, 
    VkSurfaceKHR surface);
    void createImageViews();
    void initArrays();

};

#endif
