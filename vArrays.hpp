#ifndef VARRAYS
#define VARRAYS
#include "struct.hpp"
#include <iostream>

void genereateFirstVertexLine(std::vector<Vertex> &v, 
std::vector<uint16_t> &i);

const std::vector<Vertex> land_vertices = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.9f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.9f, 0.9f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f, 0.9f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
};

const std::vector<Vertex> water_vertices = {
    {{-0.7f, -0.7f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{-0.5f, -0.7f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.7f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
};

const std::vector<Vertex> vertices4 = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{0.0f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    
    {{0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}
    
};

const std::vector<Vertex> vertices2 = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};

const std::vector<uint16_t> indices3 = {
    0, 1, 2, 2, 3, 0,
    4,5,6,6,7,4
};


const std::vector<uint16_t> land_indices = {
    0, 1, 2, 2, 3, 0
};


const std::vector<uint16_t> water_indices = {
    4, 5, 6, 6, 7, 4
};

const std::vector<uint16_t> indices4 = {
    0,2,3,3,1,0,
    2,4,5,5,3,2
};

#endif