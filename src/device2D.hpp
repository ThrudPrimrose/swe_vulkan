#ifndef DEVICE2D
#define DEVICE2D

#include "device.hpp"
#include "netcdfreader/ncReader2D.hpp"

class Device2D : public Device {
    private:
    NcReader2D ncReader2D; //this variant not like in swe has to be initialized

    public:
    //in texture we initialized these per texture
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    
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
    bool updateArrays();
    void createGraphicsPipeline();

};

#endif
