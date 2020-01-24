#ifndef NCREADER
#define NCREADER

#include "ncReader.hpp"

class NcReader2D : public NcReader {
    private:

    float start = -1.f; //best to begin from -1
    float end = 1.f; //limit of the array , best to normalize to 1
    
    //this are for print 
    //have nothing to do with dx and dy from swe netcdfreader
    float dx = 0.5f; //distance between two cells in x
    float dy = 0.5f; //distance between two cells in y
    
    float sX = -1.f; //begin loc for sX
    float sY = -1.f; //begin loc for sY
    int yOf = 0;
    int maxUsedInt = 0;
    float maxHforWhite = 22.0;

   
    glm::vec3 generateColor(int xOf,int yOf);
    void generateFirstVertexLine(std::vector<Vertex> &v, 
    std::vector<uint16_t> &i);
    void generateSecondaryVertexLine(std::vector<Vertex> &v, 
    std::vector<uint16_t> &i);
    void updateVertexLine(std::vector<Vertex> &v);
    void resetValues();

    public:
    void generateVertexArray(std::vector<Vertex> &v, 
    std::vector<uint16_t> &i, bool setDynamicMaxH);

    bool updateVertexArray(std::vector<Vertex> &v);
    void updateMaxH();

    void generateValues();
};

#endif