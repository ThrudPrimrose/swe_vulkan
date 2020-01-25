#include "ncReader2D.hpp"



    //generate from squares -> the vertices
    //and corresponding vertices
    //the color changes with the color
    //
    void NcReader2D::generateFirstVertexLine(std::vector<Vertex> &v, 
std::vector<uint32_t> &i){
    if(generatedValues!=true){
      std::cout<<"Having dx and dy as null will create an infiinte loop and kill the program"<<std::endl;
    }
    //std::cout<<"uwu i' a bug1"<<std::endl;
    //first square is 
    //std::cout<<"uwu i' a bug2"<<std::endl;
    if(maxGeneratedTime>=curtimestep){
      std::cout<<"nothing to draw anymore"<<std::endl;
      return;
    }

    for (int i=0; i<nx; i++){ 
      glm::vec3 color = generateColor(i,yOf);
      Vertex tmp ={{i*dx+start, sY}, color};
      v.push_back(tmp);

    }
    sY+=dy;
    yOf+=1;
    for (int j=0; j<nx; j++){
      glm::vec3 color = generateColor(j,yOf);
      Vertex tmp ={{j*dx+start, sY}, color};
      v.push_back(tmp);
    }
    //curmaxUsedInt ==9
    for (int j=0; j<nx-1; j++){
      std::vector x = {j, j+1, nx+j+1, nx+j+1, nx+j, j};
      i.insert(i.end(),x.begin(),x.end());
    }

    sY+=dy;
    yOf+=1;
    maxUsedInt=2*nx-1;
}

void NcReader2D::generateSecondaryVertexLine(std::vector<Vertex> &v, 
std::vector<uint32_t> &i){
  //maxUsedInt - nX willbe the corresponding vertexIndex
    for (int i=0; i<nx; i++){ 
      glm::vec3 color = generateColor(i,yOf);
      Vertex tmp ={{i*dx+start, sY}, color};
      v.push_back(tmp);
    }
    for (int j=0; j<nx-1;j++){
      //(5,6,11,11,10,5)
      //nx=5, maxUsedInt before pattern = 9
      maxUsedInt+=1;
      std::vector x = {maxUsedInt-nx,
      maxUsedInt-nx+1, maxUsedInt+1,maxUsedInt+1, 
      maxUsedInt,maxUsedInt-nx};
      i.insert(i.end(),x.begin(),x.end());
    }
    maxUsedInt+=1;
    yOf+=1;
    sY+=dy;

}



void NcReader2D::generateVertexArray(std::vector<Vertex> &v, 
std::vector<uint32_t> &i, bool setDynamicMaxH){
  if (setDynamicMaxH){
    updateMaxH();
  }
  generateFirstVertexLine(v,i);
  while(yOf<ny){
    //generate secondary line changes value of yOf
    generateSecondaryVertexLine(v,i);
  }
  sY=start;
  yOf = 0;
  maxUsedInt=0;
  
}

bool NcReader2D::updateVertexArray(std::vector<Vertex> &v){
    maxGeneratedTime+=1;
    //std::cout<<"mT: "<<curtimestep<<"curT: "<<maxGeneratedTime<<std::endl;
    if(maxGeneratedTime>curtimestep){
      std::cout<<"end of simulation reached"<<std::endl;
      return true;
    }
  
    //reset values before updating
    yOf=0;
    sY=start;
    maxUsedInt=0;
    while(yOf<ny){
      //update secondary line changes value of yOf
      updateVertexLine(v);
    }
    sY = start;
    yOf = 0;
    maxUsedInt=0;
    
    return false;
}

void NcReader2D::updateVertexLine(std::vector<Vertex> &v){ 
  for (int i=0; i<nx; i++){
    //check to save time
   
      //water height has changed
      
      //get the 4 indices
      //i,yof
      //index of i,yof == nx*yOf + i
      glm::vec3 novaColor = generateColor(i,yOf); 
      v[nx*yOf + i].color = novaColor;
    
  }
  yOf += 1;
}

glm::vec3 NcReader2D::generateColor(int xOf,int yOf){
    if(getBathymetry(xOf,yOf)>0){
      return limegreen;
    }else{
      float tph = getWaterHeight(xOf,yOf) + getBathymetry(xOf,yOf);
      if (tph<=0.1 && tph >=-0.1){
        return cyan;
      }else
      if (tph>=maxHforWhite){
        return red;
      }else{
        //interpolate color with height
        float feelofred = min(tph,maxHforWhite)/maxHforWhite;
        return {feelofred,1.0-feelofred,1.0-feelofred};
      }
    }
    //should not reach here
    return white;
}


