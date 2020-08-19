#ifndef STRUCT
#define STRUCT

#include <vector>
#include <vulkan/vulkan.h>
#include <array>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;
    static  VkVertexInputBindingDescription getBindingDescription(); 
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};

struct Vertex3D {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    static  VkVertexInputBindingDescription getBindingDescription(); 
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};

struct Vertex3DwB {
    glm::vec3 pos;
    glm::vec4 color;
    glm::vec2 texCoord;
    static  VkVertexInputBindingDescription getBindingDescription(); 
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};

struct VertexTexture {
    glm::vec2 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    static  VkVertexInputBindingDescription getBindingDescription(); 
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};


#endif