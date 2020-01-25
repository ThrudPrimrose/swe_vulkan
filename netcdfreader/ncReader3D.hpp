#ifndef NCREADER
#define NCREADER

#include "ncReader.hpp"

class NcReader3D : public NcReader {
    private:

    int yOf = 0;
    int maxUsedInt = 0;
    float maxCor = 2.f;
  

   
    glm::vec3 generateColor(int xOf,int yOf);
    float generateCoordinate(int xOf, int yOf);
    void generateFirstVertexLine(std::vector<Vertex3D> &v, 
    std::vector<uint32_t> &i);
    void generateSecondaryVertexLine(std::vector<Vertex3D> &v, 
    std::vector<uint32_t> &i);
    void updateVertexLine(std::vector<Vertex3D> &v);


    public:
    void generateVertexArray(std::vector<Vertex3D> &v, 
    std::vector<uint32_t> &i, bool setDynamicMaxH);

    bool updateVertexArray(std::vector<Vertex3D> &v);
};

#endif