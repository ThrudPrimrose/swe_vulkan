#ifndef STRUCT
#define STRUCT

#include <vector>
#include <vulkan/vulkan.h>
#include <array>
#include <glm/glm.hpp>

struct Vertex {
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


//Some Small VertexArrays Used for testung
const std::vector<Vertex> land_vertices = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.9f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.9f, 0.9f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f, 0.9f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
};

const std::vector<Vertex> water_vertices = {
    {{-0.7f, -0.7f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, -0.7f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.7f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
};

const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.9f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.9f, 0.9f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f, 0.9f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.7f, -0.7f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, -0.7f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.7f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
};


const std::vector<uint16_t> land_indices = {
    0, 1, 2, 2, 3, 0
};


const std::vector<uint16_t> water_indices = {
    4, 5, 6, 6, 7, 4
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4
};

/*
const std::vector<std::vector<uint16_t>> indices = {
    land_indices,water_indices
};

const std::vector<std::vector<Vertex>> vertices = {
    land_vertices,water_vertices
};
*/


#endif