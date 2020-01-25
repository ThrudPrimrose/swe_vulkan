#include "ncReader3D.hpp"


    //generate from squares -> the vertices
    //and corresponding vertices
    //the color changes with the color
    //
    void NcReader3D::generateFirstVertexLine(std::vector<Vertex3D> &v, 
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
      float z = generateCoordinate(i,yOf);
      Vertex3D tmp ={{i*dx+start, sY,z}, color, {1.f,1.f}};
      v.push_back(tmp);

    }
    yOf+=1;
    sY+=dy;
    for (int j=0; j<nx; j++){
      glm::vec3 color = generateColor(j,yOf);
      float z = generateCoordinate(j,yOf);
      Vertex3D tmp ={{j*dx+start, sY, z}, color, {1.f,1.f}};
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

void NcReader3D::generateSecondaryVertexLine(std::vector<Vertex3D> &v, 
std::vector<uint32_t> &i){
  //maxUsedInt - nX willbe the corresponding vertexIndex

    for (int i=0; i<nx; i++){ 
      glm::vec3 color = generateColor(i,yOf);
      float z = generateCoordinate(i,yOf);
      Vertex3D tmp ={{i*dx+start, sY, z}, color, {1.f,1.f}};
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



void NcReader3D::generateVertexArray(std::vector<Vertex3D> &v, 
std::vector<uint32_t> &i, bool setDynamicMaxH){
  if (setDynamicMaxH){
    updateMaxH();
  }
  generateFirstVertexLine(v,i);
  while(yOf<ny){
    //generate secondary line changes value of yOf
    generateSecondaryVertexLine(v,i);
  }
  sY = start;
  yOf =0;
  maxUsedInt=0;
  
  
}

bool NcReader3D::updateVertexArray(std::vector<Vertex3D> &v){
    maxGeneratedTime+=1;
    if(maxGeneratedTime>curtimestep){
      std::cout<<"end of simulation reached"<<std::endl;
      return true;
    }
   
    //reset values before updating
    while(yOf<ny){
      //update secondary line changes value of yOf
      updateVertexLine(v);
    }
    sY = start;
    yOf =0;
    maxUsedInt=0;
  
    return false;
}

void NcReader3D::updateVertexLine(std::vector<Vertex3D> &v){ 
  for (int i=0; i<nx; i++){
    //check to save time
      //water height has changed
      
      //get the 4 indices
      //i,yof
      //index of i,yof == nx*yOf + i
      glm::vec3 novaColor = generateColor(i,yOf);
      float z = generateCoordinate(i,yOf); 
      v[nx*yOf + i].color = novaColor;
      v[nx*yOf + i].pos[2] = z;
  }
  yOf += 1;
}

glm::vec3 NcReader3D::generateColor(int xOf,int yOf){
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
        return {feelofred,1.0-feelofred*0.8,1.0-feelofred*0.8};
      }
    }
    //should not reach here
    return white;
}

float NcReader3D::generateCoordinate(int xOf, int yOf){
    
    if (b_vec[yOf*nx + xOf]>=0){
      float b = b_vec[yOf*nx + xOf];
      return min(b,maxHforWhite)*(2*maxCor/maxHforWhite);
    }else{
      float b = b_vec[yOf*nx + xOf];
      float h = h_vec[maxGeneratedTime*ny*nx + yOf*nx + xOf];
      float l = min(b+h,maxHforWhite)*(maxCor/maxHforWhite);
      //std::cout<<"we are generating coordinates and it is:"<<l<<std::endl;
      return l;
    }
    return -1;
}

