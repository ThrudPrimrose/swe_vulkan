#ifndef NCREADERLIVE
#define NCREADERLIVE

#include "ncReader.hpp"
#include "../../tools/help.hh"
#include <cmath>

class NcReaderLive : public NcReader {
    protected:

    int yOf = 0;
    int maxUsedInt = 0;
    float maxCor = 1.f;
    float maxBforGreen = 0.f;
    float minBforP = -1.0f;
    float bathOffset = -2.f;
    int bCount; //this is inclusive 0 so bCount n means there are n+1 b vertices

    glm::vec3 purpuru = {0.62352,0.372549,0.623529};
   
    glm::vec4 generateColor(
        const Float2D *h, const Float2D *b,int xOf,int yOf);
    float generateCoordinate(
        const Float2D *h, const Float2D *b,int xOf, int yOf);
    void generateFirstVertexLine(
        const Float2D *h, const Float2D *b,
        std::vector<Vertex3DwB> &v,std::vector<uint32_t> &i);
    void generateSecondaryVertexLine(
        const Float2D *h, const Float2D *b,
        std::vector<Vertex3DwB> &v, std::vector<uint32_t> &i);
    void updateVertexLine(
        const Float2D *h, const Float2D*b,
        std::vector<Vertex3DwB> &v);

    void generateFirstBathyLine(
        const Float2D *b, 
        std::vector<Vertex3DwB> &v, std::vector<uint32_t> &i);
    void generateSecondaryBathyLine(
       const Float2D *b,
        std::vector<Vertex3DwB> &v, std::vector<uint32_t> &i);

    float generateBathCoordinate(const Float2D *b,int xOf, int yOf);
    glm::vec3 generateBathColor(const Float2D *b,int xOf,int yOf);

    public:
    void generateVertexArray(
        const Float2D *h, const Float2D *b,
        std::vector<Vertex3DwB> &v,std::vector<uint32_t> &i, bool setDynamicMaxH);

    void updateVertexArray(
       const Float2D *h, const Float2D *b,
        std::vector<Vertex3DwB> &v);
    void updateMaxHandB(const Float2D *h, const Float2D *b);
    void readAndInit(int nxi, int nyi);
};


#endif