#include "ncReader.hpp"

    ncRead::ncRead() {
        i = 5.4;
        double tmp = i - 1.2;
        tmp *= 10;
        std::cout<<tmp<<std::endl;
        print("print");
        //error("this is error");
        
        name="t1000x500_00.nc";
        
        initArrays();
        
        createVertices(0);
        
        createIndices();
        
    }
    
    
     /*! \fn void initArrays(const char* name)
    * \brief Initializes the dynamic arrays and reads from netcdf file
    * 
    * Is only called from the constructor
    */
    void ncRead::initArrays(){
        int ncid;
        int e;
        print("opne netcdf file: "<<name);
        e = nc_open(name,NC_NOWRITE,&ncid); if(e!=0)error(e);
        int numofdim;
        int numofvar;
        int numofattr;
        int numofunl;
        e = nc_inq(ncid,&numofdim,&numofvar,&numofattr,&numofunl); if(e!=0)error(e);
        print("numofdim:"<<numofdim<<" numofvar:"<<numofvar);
        
        
        int xid;
        size_t xsize;
        char xname;
        int yid;
        size_t ysize;
        char yname;
        int tid;
        size_t tsize;
        char tname;     
        //std::cout<<name<<std::endl;
        e = nc_inq_dimid(ncid,"x",&xid); if(e!=0)error(e);print("read x");
        e = nc_inq_dim(ncid,xid,&xname,&xsize); if(e!=0)error(e);
        e = nc_inq_dimid(ncid,"y",&yid); if(e!=0)error(e);print("read y");
        e = nc_inq_dim(ncid,yid,&yname,&ysize); if(e!=0)error(e);
        e = nc_inq_dimid(ncid,"t",&tid); if(e!=0)error(e);print("read t");
        e = nc_inq_dim(ncid,tid,&tname,&tsize); if(e!=0)error(e);
        print("xsize:"<<xsize<<" ysize:"<<ysize<<" tsize:"<<tsize);
        
        
        nx = static_cast<int>(xsize);
        ny = static_cast<int>(ysize);
        nt = static_cast<int>(tsize);
        
        
        hs = new float[nt*ny*nx];
        bs = new float[ny*nx];
        ts = new float[nt];
        xcor = new float[nx];
        ycor = new float[ny];
        
        //temporary id
        int bid;
        
        e = nc_inq_varid(ncid,"h",&bid); if(e!=0)error(e);
        e = nc_get_var_float(ncid, bid, hs); if(e!=0)error(e);

        e = nc_inq_varid(ncid,"b" ,&bid); if(e!=0)error(e);
        e = nc_get_var_float(ncid, bid, bs); if(e!=0)error(e);

        e = nc_inq_varid(ncid,"t" ,&bid); if(e!=0)error(e);
        e = nc_get_var_float(ncid, bid, ts); if(e!=0)error(e);
        
        e = nc_inq_varid(ncid,"x",&bid); if(e!=0)error(e);
        e = nc_get_var_float(ncid, bid, xcor); if(e!=0)error(e);
        //std::cout<<name<<std::endl;
        e = nc_inq_varid(ncid,"y",&bid); if(e!=0)error(e);
        e = nc_get_var_float(ncid, bid, ycor); if(e!=0)error(e);
        
//         for(int i=0; i<nx + 3; i++){
//             std::cout<<ycor[i]<<", ";
//         }
        
    }
    
    

    /*! \fn float getH(int x, int y, int t)
    * \brief Returns hs[y][x][t] from the netcdf array
    * 
    * \param x x-coordinate index
    * \param y y-coordinate index
    * \param t timestep index
    * \return hs[y][x][t]
    */
    float ncRead::getH(int x, int y, int t){
        return hs[x + nx*y + nx*ny*t];
    }

     /*! \fn float getB(int x, int y, int t)
    * \brief Returns bs[y][x][t] from the netcdf array
    * 
    * \param x x-coordinate index
    * \param y y-coordinate index
    * \param t timestep index
    * \return bs[y][x][t]
    */
    float ncRead::getB(int x, int y, int t){
        return bs[x + nx*y + nx*ny*t];
    }
    
     /*! \fn float isWet(int x, int y, int t)
    * \brief Checks if ncVertex is wet
    * 
    * \param x x-coordinate index
    * \param y y-coordinate index
    * \param t timestep index
    * \return h > 0
    */
    bool ncRead::isWet(int x, int y, int t){
        return getH(x,y,t) > 0;
    }
    
    
    
    
    void ncRead::setPos(float* pos, int x, int y, int t){
        pos[0] = xcor[x];
        pos[1] = ycor[y];
    }
    
    // not used yet
    void ncRead::setPos3D(float* pos, int x, int y, int t){
        float h = getH(x,y,t);
        float b = getB(x,y,t);
        float hb = h+b;             //effective height
        bool isWet = (h > 0);
        
        float scaleDry = xcor[1] - xcor[0];  //scale according to grid distance
        float scaleWet = scaleDry * 2000.f;  //scale tsunami waves higher to be more visible
        
        pos[0] = xcor[x];
        pos[1] = ycor[y];
        if (isWet) {
            pos[2] = scaleWet * hb;
        } else {
            pos[2] = scaleDry * hb;
        }
    }
    
    // colors the ncVertex according to height
    void ncRead::setColor(float* color, int x, int y, int t){
        float h = getH(x,y,t);
        float b = getB(x,y,t);
        float hb = h+b;             //effective height
        bool isWet = (h > 0);
        
        float scaleWet = 20.f;  //more than this value stays same color
        float scaleDry = 3000.f;
        
        if (!isWet) {
            float factor = pow(1.f - 1.f/scaleDry*b, 3);
            float col1[3] = {35.f/256, 66.f/256, 6.f/256};      //dark green  #214206
            float col2[3] = {183.f/256, 234.f/256, 176.f/256};  //light green #b7eab0
            
            color[0] = factor * col1[0] + (1-factor) * col2[0];
            color[1] = factor * col1[1] + (1-factor) * col2[1];
            color[2] = factor * col1[2] + (1-factor) * col2[2];
        }
        if (isWet) {
            if (hb > 0) {
                float factor = pow(1.f - 1.f/scaleWet*hb, 3);
                float col1[3] = {236.f/256, 230.f/256, 213.f/256};  //light grey #ece6d5
                float col2[3] = {140.f/256, 3.f/256, 28.f/256};     //dark red   #8c031c
                
                color[0] = factor * col1[0] + (1-factor) * col2[0];
                color[1] = factor * col1[1] + (1-factor) * col2[1];
                color[2] = factor * col1[2] + (1-factor) * col2[2];
            } else {
                float factor = pow(1.f + 1.f/scaleWet*hb, 3);
                float col1[3] = {236.f/256, 230.f/256, 213.f/256};  //light grey #ece6d5
                float col2[3] = {3.f/256, 43.f/256, 92.f/256};      //dark blue  #032b5c
                
                color[0] = factor * col1[0] + (1-factor) * col2[0];
                color[1] = factor * col1[1] + (1-factor) * col2[1];
                color[2] = factor * col1[2] + (1-factor) * col2[2];
            }
        }
    }
    
    // linearly maps lowest x (or y) coordinate to 0, and highest to 1
    void ncRead::setTexCoord(float* coord, int x, int y){
        float x_min = xcor[0];
        float x_max = xcor[nx-1];
        float y_min = ycor[0];
        float y_max = ycor[ny-1];
        
        coord[0] = (xcor[x] - x_min) / (x_max - x_min);
        coord[1] = (ycor[y] - y_min) / (y_max - y_min);
    }
    
     /*! \fn void createVertices(int t)
    * \brief Populates the ncVertex array
    * 
    * \param t index of the timestep for which the array is created
    */
    void ncRead::createVertices(float t) {
        for(size_t j=0; j<ny; j++){
            for (size_t i=0; i<nx; i++){
                
                //ncVertex v = {
                //    .pos=       {xcor[i], ycor[j]},     //position
                //    .color=     setColor(i,j,t),        //ncVertex color
                //    .texCoord=  {6.f, 7.f}              //texture coordinate
                //};
                
                
                // what a horrible way to handle array initialization
        
                ncVertex v;
                setPos(v.pos, i, j, t);
                setColor(v.color, i, j, t);
                setTexCoord(v.texCoord, i, j);
                
                vertices.insert(vertices.end(), v);
                
            }
        }
        print("");
        print(vertices[nx*ny-1].pos[0]);
        print(vertices[nx*ny-1].pos[1]);
        print(vertices[nx*ny-1].color[0]*256);
        print(vertices[nx*ny-1].color[1]*256);
        print(vertices[nx*ny-1].color[2]*256);
        print(vertices[nx*ny-1].texCoord[0]);
        print(vertices[nx*ny-1].texCoord[1]);
        
        print(std::endl<<"vertices:");
        for(int i=0; i<=5; i++){
            std::cout<<vertices[i].pos[0]<<" "<<vertices[i].pos[1]<<"} {";
        }
    }
    
     /*! \fn void createVertices(int t)
    * \brief Populates the ncVertex array with height
    * 
    * \param t index of the timestep for which the array is created
    */
    void ncRead::createVertices3D(float t) {
        for(size_t j=0; j<ny; j++){
            for (size_t i=0; i<nx; i++){
        
                ncVertex3D v;
                setPos3D(v.pos, i, j, t);
                setColor(v.color, i, j, t);
                setTexCoord(v.texCoord, i, j);
                
                vertices3D.insert(vertices3D.end(), v);
                
            }
        }
    }
    
    
    
    // gives the index of ncVertex at index (x,y)
    uint16_t ncRead::vi(int x, int y){
        return x + nx*y;
    }
    
     /*! \fn void createIndices(int t)
    * \brief Populates the ncVertex index array
    */
    void ncRead::createIndices() {
        
        for(size_t j=0; j<ny-1; j++){
            for (size_t i=0; i<nx-1; i++){
                
                // todo: should we vary the square orientation?
                std::vector<uint16_t> square_indices =
                    {
                        vi(i, j),   vi(i+1, j),  vi(i+1, j+1),
                        vi(i, j),   vi(i, j+1),  vi(i+1, j+1),
                    };
                
                indices.insert(indices.end(), square_indices.begin(), square_indices.end());
            }
        }
        
        print(std::endl<<"indices:");
        for(int i=0; i<=20; i++){
            std::cout<<indices[i]<<" ";
        }
    }
    
     /*! \fn void createIndicesWaterLandSplit(int t)
    * \brief Populates the ncVertex index array, split into 2 according to wetness
    * 
    * Both indices_water and indices_land create objects with a mesh only in the water (bzw. land), 
    * and lots of unconnected vertices (which are not rendered)
    * \param t timestep index, should be irrelevant if no wetting/drying
    */
    void ncRead::createIndicesWaterLandSplit(int t) {
        
        for(size_t j=0; j<ny-1; j++){
            for (size_t i=0; i<nx-1; i++){
                
                // todo: should we vary the square orientation?
                std::vector<uint16_t> square_indices =
                    {
                        vi(i, j),   vi(i+1, j),  vi(i+1, j+1),
                        vi(i, j),   vi(i, j+1),  vi(i+1, j+1),
                    };
                    
                
                //only all-wet squares are added to indices_water, rest goes to indices_land
                if ( isWet(i,j,t) && isWet(i,j+1,t) && isWet(i+1,j,t) && isWet(i+1,j+1,t) ) {
                    indices_water.insert(indices_water.end(), square_indices.begin(), square_indices.end());
                } else {
                    indices_land.insert(indices_land.end(), square_indices.begin(), square_indices.end());
                    
                }
            }
        }
    }
    


