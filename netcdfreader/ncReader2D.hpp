#ifndef NCREADER
#define NCREADER

#include "ncReader.hpp"

class NcReader2D : public NcReader {
    private:

    int yOf = 0;
    int maxUsedInt = 0;
  

   
    glm::vec3 generateColor(int xOf,int yOf);
    void generateFirstVertexLine(std::vector<Vertex> &v, 
    std::vector<uint32_t> &i);
    void generateSecondaryVertexLine(std::vector<Vertex> &v, 
    std::vector<uint32_t> &i);
    void updateVertexLine(std::vector<Vertex> &v);
  
    public:
    void generateVertexArray(std::vector<Vertex> &v, 
    std::vector<uint32_t> &i, bool setDynamicMaxH);

    bool updateVertexArray(std::vector<Vertex> &v);
 
};

#endif