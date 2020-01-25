#ifndef DEVICE3D
#define DEVICE3D

#include "device.hpp"
#include "netcdfreader/ncReader3D.hpp"

class Device3D : public Device {
    private:
    NcReader3D ncReader3D; //this variant not like in swe has to be initialized

    public:
    //in texture we initialized these per texture
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    std::vector<Vertex3D> vertices;
    std::vector<uint32_t> indices;
    VkFormat depthFormat;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    
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

    //For depth buffering
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, 
    VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);
    void createDepthResources();

};


#endif 