#ifndef NCREADER
#define NCREADER

#include "ncReader.hpp"
#include <cmath>

class NcReader3D : public NcReader {
    private:

    int yOf = 0;
    int maxUsedInt = 0;
    float maxCor = 1.f;
    float maxBforGreen = 0.f;
    float minBforP = -1.0f;
    float bathOffset = -2.f;

    glm::vec3 purpuru = {0.62352,0.372549,0.623529};
   
    glm::vec3 generateColor(int xOf,int yOf);
    float generateCoordinate(int xOf, int yOf);
    void generateFirstVertexLine(std::vector<Vertex3D> &v, 
    std::vector<uint32_t> &i);
    void generateSecondaryVertexLine(std::vector<Vertex3D> &v, 
    std::vector<uint32_t> &i);
    void updateVertexLine(std::vector<Vertex3D> &v);

    void generateFirstBathyLine(std::vector<Vertex3D> &v, 
    std::vector<uint32_t> &i);
    void generateSecondaryBathyLine(std::vector<Vertex3D> &v, 
    std::vector<uint32_t> &i);
    float generateBathCoordinate(int xOf, int yOf);
    glm::vec3 generateBathColor(int xOf,int yOf);

    public:
    void generateVertexArray(std::vector<Vertex3D> &v, 
    std::vector<uint32_t> &i, bool setDynamicMaxH);

    bool updateVertexArray(std::vector<Vertex3D> &v);
    void updateMaxHandB();
};

#endif