#include "struct.hpp"

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