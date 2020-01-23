#include "vArrays.hpp"

void genereateFirstVertexLine(std::vector<Vertex> &v, 
std::vector<uint16_t> &i){
    float start =0.f;
    float end =10.f;
    float dx = (end-start)/10;
    float sY = 0.f;
    std::cout<<"uwu i' a bug1"<<std::endl;

    float sX = 0.0f; //means start X

    int maxUsedInt = 0;
    //first square is 
    std::cout<<"uwu i' a bug2"<<std::endl;
    
    Vertex tmp = {{sX, sY}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}};
    v.push_back(tmp);
    tmp ={{sX, sY+dx}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}};
    v.push_back(tmp);
    tmp ={{sX+dx, sY}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}};
    v.push_back(tmp);
    tmp ={{sX+dx, sY+dx}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}};
    v.push_back(tmp);
    maxUsedInt = 3; //means we will used 4 and 5 on next square
    //first rechteck
    std::vector vec = {0,2,3,3,1,0};
    i.insert(i.end(),vec.begin(),vec.end());
    std::cout<<"uwu i' a bug3"<<std::endl;

    sX += dx;

    while(sX<end){
        v.push_back({{sX+dx, sY}, {0.1f, 0.1f, 1.0f}, {0.0f, 1.0f}});
        v.push_back({{sX+dx, sY+dx}, {0.1f, 0.1f, 1.0f}, {0.0f, 1.0f}});
        std::vector tmp = {maxUsedInt-1, maxUsedInt+1, 
        maxUsedInt+2,maxUsedInt+2,maxUsedInt,maxUsedInt-1};
        maxUsedInt+=2;
        i.insert(i.end(),tmp.begin(),tmp.end());

        sX+=dx;
    }
    std::cout<<"uwu i' a bug"<<std::endl;
}
