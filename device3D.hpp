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
    std::vector<Vertex3D> vertices = two_squares_vertices;
    std::vector<uint16_t> indices = two_squares_indices;

    
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