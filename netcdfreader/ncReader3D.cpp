#include "ncReader3D.hpp"

//should be called only afger readAndInit function
    void NcReader3D::generateValues(){
      if(!init){
        std::cout<<"if the initialization is not done, generate values will most probably wont worj and this may indicate a bug"<<std::endl;
      }
      dx = (end-start)/nx;
      dy = (end-start)/ny;
      generatedValues=true;
    }

    //generate from squares -> the vertices
    //and corresponding vertices
    //the color changes with the color
    //
    void NcReader3D::generateFirstVertexLine(std::vector<Vertex3D> &v, 
std::vector<uint16_t> &i){
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
      Vertex3D tmp ={{i*dx, sY,0.f}, color, {0.f,0.f}};
      v.push_back(tmp);

    }
    for (int j=0; j<nx; j++){
      glm::vec3 color = generateColor(j,yOf);
      Vertex3D tmp ={{j*dx, sY+dy, 0.f}, color, {1.f,1.f}};
      v.push_back(tmp);
    }
    //curmaxUsedInt ==9
    for (int j=0; j<nx-1; j++){
      std::vector x = {j, j+1, nx+j+1, nx+j+1, nx+j, j};
      i.insert(i.end(),x.begin(),x.end());
    }
    sX=0.f;
    sY+=dy;
    yOf+=1;
    maxUsedInt=2*nx-1;
}

void NcReader3D::generateSecondaryVertexLine(std::vector<Vertex3D> &v, 
std::vector<uint16_t> &i){
  //maxUsedInt - nX willbe the corresponding vertexIndex
  yOf+=1;
  sY+=dy;
    for (int i=0; i<nx; i++){ 
      glm::vec3 color = generateColor(i,yOf);
      Vertex3D tmp ={{i*dx, sY, 0.f}, color, {1.f,1.f}};
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
    sX=0; 
}



void NcReader3D::generateVertexArray(std::vector<Vertex3D> &v, 
std::vector<uint16_t> &i, bool setDynamicMaxH){
  if (setDynamicMaxH){
    updateMaxH();
  }
  generateFirstVertexLine(v,i);
  /*while(yOf<ny-1){
    //generate secondary line changes value of yOf
    generateSecondaryVertexLine(v,i);
  }
  */
  
}

bool NcReader3D::updateVertexArray(std::vector<Vertex3D> &v){
    /*maxGeneratedTime+=1;
    if(maxGeneratedTime>curtime){
      std::cout<<"end of simulation reached"<<std::endl;
      return true;
    }
    resetValues();
    //reset values before updating
    while(yOf<ny-1){
      //update secondary line changes value of yOf
      updateVertexLine(v);
    }
    resetValues();
    return false;
    */
   return true;
}

void NcReader3D::updateVertexLine(std::vector<Vertex3D> &v){ 
  for (int i=0; i<nx-1; i++){
    //check to save time
    if (abs(getWaterHeight(i,yOf,maxGeneratedTime),
    getWaterHeight(i,yOf,maxGeneratedTime-1))>0.1){
      //water height has changed
      
      //get the 4 indices
      //i,yof
      //index of i,yof == nx*yOf + i
      glm::vec3 novaColor = generateColor(i,yOf); 
      v[nx*yOf + i].color = novaColor;
      //i+1,yof
      novaColor = generateColor(i+1,yOf);
      v[nx*yOf +i +1].color = novaColor;
      //i,yof+1
      novaColor = generateColor(i,yOf+1);
      v[nx*(yOf+1) +i].color = novaColor;
      //i+1,yof+1
      novaColor = generateColor(i+1,yOf+1);
      v[nx*(yOf+1) +i +1 ].color = novaColor;
    }
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

void NcReader3D::resetValues(){
    yOf=0;
    sX=0.f;
    sY=0.f;
    maxUsedInt=0;
    //Dx dy should remain same;
}



void NcReader3D::updateMaxH(){
  if(!init){
    std::cout<<"calling this function before the initialization will cause bugs"<<std::endl;
  }
  float max = h_vec[0] +b_vec[0];
  for(int i=0; i<nx*ny;i++){
    h_vec[i] +b_vec[i]> max ? max=h_vec[i]+b_vec[i] : max=max ;
  }
  maxHforWhite = max;
  std::cout<<"Dynamic max height is: "<<maxHforWhite<<std::endl;
}