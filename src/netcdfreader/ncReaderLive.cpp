#ifdef LIVE
#include "ncReaderLive.hpp"

   //generate from squares -> the vertices
    //and corresponding vertices
    //the color changes with the color
    //
    void NcReaderLive::generateFirstVertexLine(
        const Float2D *h, const Float2D *b,
        std::vector<Vertex3DwB> &v, std::vector<uint32_t> &i){
    if(generatedValues!=true){
      std::cout<<"Having dx and dy as null will create an infiinte loop and kill the program"<<std::endl;
    }
    //std::cout<<"uwu i' a bug1"<<std::endl;
    //first square is 
    //std::cout<<"uwu i' a bug2"<<std::endl;
    maxUsedInt+=1;

    for (int i=0; i<nx; i++){ 
      glm::vec4 color = generateColor(h,b,i,yOf);
      float z = generateCoordinate(h,b,i,yOf);
      Vertex3DwB tmp ={{i*dx+start, sY,z}, color, {1.f,1.f}};
      v.push_back(tmp);

    }
    yOf+=1;
    sY+=dy;
    for (int j=0; j<nx; j++){
      glm::vec4 color = generateColor(h,b,j,yOf);
      float z = generateCoordinate(h,b,j,yOf);
      Vertex3DwB tmp ={{j*dx+start, sY, z}, color, {1.f,1.f}};
      v.push_back(tmp);
    }
    //curmaxUsedInt ==9
    for (int j=0; j<nx-1; j++){
      std::vector x = {maxUsedInt+j, maxUsedInt+j+1, 
      maxUsedInt+nx+j+1, maxUsedInt+nx+j+1, 
      maxUsedInt+nx+j, maxUsedInt+j};
      i.insert(i.end(),x.begin(),x.end());
    }

    sY+=dy;
    yOf+=1;
    maxUsedInt+=2*nx-1;
}


void NcReaderLive::generateSecondaryVertexLine(
    const Float2D *h, const Float2D *b,
    std::vector<Vertex3DwB> &v, std::vector<uint32_t> &i){
  //maxUsedInt - nX willbe the corresponding vertexIndex
    maxUsedInt+=1;
    for (int i=0; i<nx; i++){ 
      glm::vec4 color = generateColor(h,b,i,yOf);
      float z = generateCoordinate(h,b,i,yOf);
      Vertex3DwB tmp ={{i*dx+start, sY, z}, color, {1.f,1.f}};
      v.push_back(tmp);
    }
    for (int j=0; j<nx-1;j++){
      //(5,6,11,11,10,5)
      //nx=5, maxUsedInt before pattern = 9
      std::vector x = {maxUsedInt-nx+j,
      maxUsedInt-nx+1+j, maxUsedInt+1+j,maxUsedInt+1+j, 
      maxUsedInt+j,maxUsedInt-nx+j};
      i.insert(i.end(),x.begin(),x.end());
    }
    maxUsedInt+=nx-1; 
    yOf+=1;
    sY+=dy;
}



void NcReaderLive::generateVertexArray(
    const Float2D *h, const Float2D *b,
    std::vector<Vertex3DwB> &v, std::vector<uint32_t> &i, bool setDynamicMaxH){
  if (setDynamicMaxH){
    updateMaxHandB(h,b);
  }
  //its important to draw bathymetry first
  //because otherwise blending will be to black
  maxUsedInt=0;
  sY=start;
  yOf=0;
  generateFirstBathyLine(b,v,i);
  //std::cout<<"what1"<<std::endl;
  while(yOf<ny){
    generateSecondaryBathyLine(b,v,i);
    //std::cout<<"what2"<<std::endl;
  }

  sY=start;
  yOf=0;
  bCount=maxUsedInt+1;
  //std::cout<<"bcount:"<<bCount<<std::endl;
  //maxUsedInt+=1;

  generateFirstVertexLine(h,b,v,i);
  //std::cout<<"what3"<<std::endl;
  while(yOf<ny){
    //generate secondary line changes value of yOf
    generateSecondaryVertexLine(h,b,v,i);
    //std::cout<<"what4"<<std::endl;
  }
  sY = start;
  yOf =0;
  
  
}

void NcReaderLive::updateVertexArray(
    const Float2D *h, const Float2D *b,
    std::vector<Vertex3DwB> &v){
    maxGeneratedTime+=1;
    yOf=0;
    sY=start;
   
    //reset values before updating
    while(yOf<ny){
      //update secondary line changes value of yOf
      updateVertexLine(h,b,v);
    }
    sY = start;
    yOf =0;
  
}

void NcReaderLive::updateVertexLine(
    const Float2D *h, const Float2D *b,
    std::vector<Vertex3DwB> &v){ 
  for (int i=0; i<nx; i++){
    //check to save time
      //water height has changed
      
      //get the 4 indices
      //i,yof
      //index of i,yof == nx*yOf + i
      glm::vec4 novaColor = generateColor(h,b,i,yOf);
      float z = generateCoordinate(h,b,i,yOf); 
      v[bCount +1+ nx*yOf + i].color = novaColor;
      v[bCount +1+ nx*yOf + i].pos[2] = z;
  }
  yOf += 1;
}



glm::vec4 NcReaderLive::generateColor(
    const Float2D *h_v, const Float2D *b_v,int xOf,int yOf){
    float h= (*h_v)[xOf][yOf];
    float b= (*b_v)[xOf][yOf];
    float hb = h+b;             //effective height
    bool isWet = (h > 0);       //checking b doesn't work with wetting

    float scaleWet = maxHforWhite;//20.f;  //more than this limit stays same color
    float scaleDry = maxBforGreen;//3000.f;
    
    glm::vec4 color = {1.f, 0.f, 1.f,1.f};  //default pink
    
    if(!isWet){
        //function starts steep, but doesn"t change much for values near limit
        float factor = std::min(std::max(( (float)pow(1.f - b/scaleDry, 2.f) ),0.f),1.f);
        glm::vec3 col1 = {35.f/256, 66.f/256, 6.f/256};      //dark green  #214206
        glm::vec3 col2 = {183.f/256, 234.f/256, 176.f/256};  //light green #b7eab0
        
        color[0] = factor * col1[0] + (1.f-factor) * col2[0];
        color[1] = factor * col1[1] + (1.f-factor) * col2[1];
        color[2] = factor * col1[2] + (1.f-factor) * col2[2];
        
    }else{
        if (hb > 0) {
            float factor = std::min(std::max(( (float)pow(1.f - hb/scaleWet, 2.f) ),0.f),1.f);
            glm::vec3 col1 = slateblue; //{236.f/256, 230.f/256, 213.f/256};  //light grey #ece6d5
            glm::vec3 col2 = white;     //dark red   #8c031c
            
            color[0] = factor * col1[0] + (1.f-factor) * col2[0];
            color[1] = factor * col1[1] + (1.f-factor) * col2[1];
            color[2] = factor * col1[2] + (1.f-factor) * col2[2];
            
        } else {
            float factor = std::min(std::max(( (float)pow(1.f - hb/scaleWet, 2.f) ),0.f),1.f);
            glm::vec3 col1 = slateblue;  //light grey #ece6d5
            glm::vec3 col2 = white;      //dark blue  #032b5c
            
            color[0] = factor * col1[0] + (1.f-factor) * col2[0];
            color[1] = factor * col1[1] + (1.f-factor) * col2[1];
            color[2] = factor * col1[2] + (1.f-factor) * col2[2];
        }
    }

    if(!isWet){
      color[3] =1.f; //no blend
    }else{
      color[3] =.42f; //is half reasonable?
    }
    return color;
}



/*
  glm::vec3 limegreen = {0.196, 0.874, 0.196};
  glm::vec3 cyan = {0.08,0.92,0.97};
  glm::vec3 white = {0.97,0.97,0.97};
  glm::vec3 red = {0.97,0.08,0.08};
    */

float NcReaderLive::generateCoordinate(
    const Float2D *h_v, const Float2D *b_v,int xOf, int yOf){
    if ((*b_v)[xOf][yOf]>=0){
      float b = (*b_v)[xOf][yOf];
      return min(b,maxBforGreen)*(maxCor/(maxBforGreen));
    }else{
      float b = (*b_v)[xOf][yOf];
      float h = (*h_v)[xOf][yOf];
      float l = min(b+h,maxHforWhite)*(maxCor/maxHforWhite);
      //std::cout<<"we are generating coordinates and it is:"<<l<<std::endl;
      return l;
    }
    return -1;
}

void NcReaderLive::updateMaxHandB(const Float2D *h, const Float2D *b){
  if(!init){
    std::cout<<"calling this function before the initialization will cause bugs"<<std::endl;
  }
  float maxH;
  float maxB;
  float minB;
  if((*b)[0][0]<0){
      //std::cout<<"uwu im a bug"<<std::endl;
      float hi = (*h)[0][0];
      float bi = (*b)[0][0];
    maxH = hi+bi;
    maxB = 0.f;
    minB = (*b)[0][0];
  }else{
    maxH = 0.f;
    maxB = (*b)[0][0];
    minB = 0.f;
  }
 
  for(int i=0; i<ny;i++){
    for(int j=0; j<nx;j++){
        if ((*b)[i][j]>0){
        (*b)[i][j] > maxB ? maxB = (*b)[i][j] : maxB=maxB;
        }else{
        (*b)[i][j] < minB ? minB = (*b)[i][j] : minB=minB;
        (*h)[i][j] + (*b)[i][j] > maxH  && (*b)[i][j]<0 ? maxH=(*h)[i][j]+
        (*b)[i][j] : maxH=maxH ;
        }
    }
  }
  maxHforWhite = maxH;
  maxBforGreen = maxB;
  minBforP = minB;
  
  bathOffset = (maxCor * -minB) / maxB;
  if(maxB<=0){
      bathOffset = 2;
  }
  bathOffset*=-1;
  //std::cout<<"Dynamic max height is: "<<maxHforWhite<<std::endl;
  //std::cout<<"Dynamic max bathymetry is: "<<maxBforGreen<<std::endl;
  //std::cout<<"Dynamic min bathymetry is: "<<minBforP<<std::endl;
  std::cout<<"Bath offset:"<<bathOffset<<std::endl;
}


void NcReaderLive::generateFirstBathyLine(
    const Float2D *b,
    std::vector<Vertex3DwB> &v, std::vector<uint32_t> &i){
    if(generatedValues!=true){
      std::cout<<"Having dx and dy as null will create an infiinte loop and kill the program"<<std::endl;
    }
    //std::cout<<"uwu i' a bug1"<<std::endl;
    //first square is 
    //std::cout<<"uwu i' a bug2"<<std::endl;
    sY=start;
    yOf=0;
    maxUsedInt=0;

    for (int i=0; i<nx; i++){ 
      glm::vec3 color = generateBathColor(b,i,yOf);
      float z = generateBathCoordinate(b,i,yOf);
       glm::vec4 realcolor = {color,1.f};
      Vertex3DwB tmp ={{i*dx+start, sY,z+bathOffset}, realcolor, {1.f,1.f}};
      v.push_back(tmp);
      std::cout<<"coordinate:"<<i*dx+start<<", "<<sY<<", "<<z+bathOffset<<std::endl;

    }
    yOf+=1;
    sY+=dy;
    for (int j=0; j<nx; j++){
      float z = generateBathCoordinate(b,j,yOf);
      glm::vec3 color = generateBathColor(b,j,yOf);
      glm::vec4 realcolor = {color,1.f};
      Vertex3DwB tmp ={{j*dx+start, sY, z+bathOffset},realcolor, {1.f,1.f}};
      v.push_back(tmp);
       std::cout<<"coordinate:"<<j*dx+start<<", "<<sY<<", "<<z+bathOffset<<std::endl;

    }
    //curmaxUsedInt ==9
    for (int j=0; j<nx-1; j++){
      std::vector x = {maxUsedInt +j, maxUsedInt +j+1, 
      maxUsedInt +nx+j+1, maxUsedInt +nx+j+1, maxUsedInt +nx+j, 
      maxUsedInt +j};
      i.insert(i.end(),x.begin(),x.end());
    }

    sY+=dy;
    yOf+=1;
    maxUsedInt+=2*nx-1;
}


void NcReaderLive::generateSecondaryBathyLine(
    const Float2D *b,
    std::vector<Vertex3DwB> &v, std::vector<uint32_t> &i){
    maxUsedInt+=1;
    for (int i=0; i<nx; i++){ 
      float z = generateBathCoordinate(b,i,yOf);
      glm::vec3 color = generateBathColor(b,i,yOf);
      glm::vec4 realcolor = {color,1.f};
      Vertex3DwB tmp ={{i*dx+start, sY, z+bathOffset}, realcolor, {1.f,1.f}};
      v.push_back(tmp);
    }
    for (int j=0; j<nx-1;j++){
      //(5,6,11,11,10,5)
      //nx=5, maxUsedInt before pattern = 9
    
      std::vector x = {maxUsedInt-nx+j,
      maxUsedInt-nx+1+j, maxUsedInt+1+j,maxUsedInt+1+j, 
      maxUsedInt+j,maxUsedInt-nx+j};
      i.insert(i.end(),x.begin(),x.end());
    }
    yOf+=1;
    sY+=dy;
    maxUsedInt+=nx-1;
}

float NcReaderLive::generateBathCoordinate(
    const Float2D *b,
    int i,int yOf){
  if((*b)[i][yOf]>=0){
    return 0.f;
  }else{
    float bv = (*b)[i][yOf];
    //std::cout<<(*b)[i][yOf]<<std::endl;
    //std::cout<<"b:"<<b<<"maxCor: "<<maxCor<< "minB: "<<minBforP<<std::endl;
    float z = (-bv*maxCor) /minBforP;
    //std::cout<<z<<std::endl;
    return z*=2.2;
  }
}


glm::vec3 NcReaderLive::generateBathColor(
    const Float2D *bv,
    int xOf,int yOf){
  //std::cout<<b_vec[yOf*nx + xOf]<<" "<<minBforP<<std::endl;
  if((*bv)[xOf][yOf]>minBforP){
    //std::cout<<"im in"<<std::endl;
    glm::vec3 tmp = purpuru;
    //glm::vec3 purpuru = {0.62352,0.372549,0.623529};
    float scale = ((*bv)[xOf][yOf]-minBforP)/minBforP;
    if(scale<0){scale*=-1;}
    tmp[0]= scale*0.63;
    tmp[1]= 0.7*scale*0.372549;
    tmp[2]= scale*0.62;
    return tmp;
  }else{
    //should not reach here
    return purpuru;
  }
}

void NcReaderLive::readAndInit(int nxi, int nyi){
  std::cout<<"New Device getting its input from the SWE's provisional result."<<std::endl;
  std::cout<<"There is readAndInit is actually just an assign function but for"<<std::endl;
  std::cout<<"for naming purposes it will remain with this name"<<std::endl;
  nx=nxi;
  ny=nyi;
  int divide;
      if (nx<ny){
        divide = nx;
      }else if (ny<nx){
        divide = ny;
      }

      dx = (end-start)/divide;
      dy = (end-start)/divide;
      maxGeneratedTime=0;
    
      generatedValues=true;
    init=true;
    std::cout<<"nx is: "<< nx <<std::endl;
    std::cout<<"ny is: "<< ny <<std::endl;
    //std::cout<<" is: "<<  <<std::endl;
    //std::cout<<" is: "<<  <<std::endl;
    
}
#endif