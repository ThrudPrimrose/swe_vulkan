
    #include "ncReader.hpp"
    void NcReader::readAndInit(std::string name){
        init = true;
        int ncid;
        int e;
        //std::cout<<name<<std::endl;
        e = nc_open(name.c_str(),NC_NOWRITE,&ncid); if(e!=0)error(e);
        int numofdim;
        int numofvar;
        int numofattr;
        int numofunl;
        e = nc_inq(ncid,&numofdim,&numofvar,&numofattr,&numofunl); if(e!=0)error(e);

        int xid;
        size_t xsize;
        char xname;
        int yid;
        size_t ysize;
        char yname;
        int timestepid;
        size_t timestepsize;
        char timename;        
        //std::cout<<name<<std::endl;
        e = nc_inq_dimid(ncid,"x",&xid); if(e!=0)error(e)
        e = nc_inq_dim(ncid,xid,&xname,&xsize); if(e!=0)error(e);
        e = nc_inq_dimid(ncid,"y",&yid); if(e!=0)error(e)
        e = nc_inq_dim(ncid,yid,&yname,&ysize); if(e!=0)error(e);
        e = nc_inq_dimid(ncid,"t",&timestepid); if(e!=0)error(e)
        e = nc_inq_dim(ncid,timestepid,&timename,&timestepsize); if(e!=0)error(e);



        nx = static_cast<int>(xsize);
        ny = static_cast<int>(ysize);
        curtimestep = static_cast<int>(timestepsize);

        float* h = new float[curtimestep*ny*nx];
        float* b = new float[ny*nx];
        float* t = new float[curtimestep];
        int timelimitid;
        //boundary id
        int bid;
    
        //std::cout<<name<<std::endl;
        e = nc_inq_varid(ncid,"t_max",&timelimitid); if(e!=0)error(e);
        e = nc_get_var_float(ncid,timelimitid,&timelimit); if(e!=0)error(e);
        
        e = nc_inq_varid(ncid,"l_boundary",&bid); if(e!=0)error(e);
        e = nc_get_var_int(ncid,bid,&l_bound); if(e!=0)error(e);

        e = nc_inq_varid(ncid,"r_boundary",&bid); if(e!=0)error(e);
        e = nc_get_var_int(ncid,bid,&r_bound); if(e!=0)error(e);

        e = nc_inq_varid(ncid,"t_boundary",&bid); if(e!=0)error(e);
        e = nc_get_var_int(ncid,bid,&t_bound); if(e!=0)error(e);

        e = nc_inq_varid(ncid,"b_boundary",&bid); if(e!=0)error(e);
        e = nc_get_var_int(ncid,bid,&b_bound); if(e!=0)error(e);

        e = nc_inq_varid(ncid,"h",&bid); if(e!=0)error(e);
        e = nc_get_var_float(ncid, bid, h); if(e!=0)error(e);

        e = nc_inq_varid(ncid,"b" ,&bid); if(e!=0)error(e);
        e = nc_get_var_float(ncid, bid, b); if(e!=0)error(e);

        e = nc_inq_varid(ncid,"t" ,&bid); if(e!=0)error(e);
        e = nc_get_var_float(ncid, bid, t); if(e!=0)error(e);

        times_vec.insert(times_vec.end(), t, t +curtimestep);
        curtime = times_vec.back();

        b_vec.insert(b_vec.end(),b,b + ny*nx);
        //we need all time steps
        //do it on startup for ease of coding
        h_vec.insert(h_vec.end(),h, h + curtimestep*ny*nx);
        //std::cout<<nx<<" "<<ny<<std::endl;
        //std::cout<<"start"<<std::endl;


        /*for(int i=0;i<nx*ny;i++){
            std::cout<<h_vec[i]<<std::endl;
        }*/
    }

    


float NcReader::getWaterHeight(int x, int y,int time){
        if (x>=nx || y>=ny || time>curtimestep){
          std::cout<<"out of bound, wheight"<<std::endl;
        }
        //std::cout<<xb<<" "<<yb<<std::endl;
        return h_vec[time*ny*nx+y*nx+x];
    }

float NcReader::getWaterHeight(int x, int y){
        if (x>=nx || y>=ny || maxGeneratedTime>curtimestep){
          std::cout<<"out of bound, wheight"<<std::endl;
        }
        //std::cout<<xb<<" "<<yb<<std::endl;
        return h_vec[maxGeneratedTime*ny*nx+y*nx+x];
    }

    /*! \fn float getBathymetry(float x, float y)
    * \brief Returns b[y'][x'] from the netcdf array
    * 
    * Coordinates are mapped to index'.
    * \param x x-coordinate
    * \param y y-coordinate
    * \return b[y'][x']
    */
float NcReader::getBathymetry(int x, int y){
        if (x>=nx || y>=ny){
          std::cout<<"out of bound, bathymetry"<<std::endl;
        }
        return b_vec[y*nx+x];
}

int NcReader::getTimeStep(){
  return curtimestep;
}

float NcReader::getTime(){
  return curtime;
}

int NcReader::getLNX(){
  return nx;
}

int NcReader::getLNY(){
  return ny;
}

float NcReader::max(float a,float b){
  float ret;
  a>=b ? ret= a : ret=b;
  return ret;
}

float NcReader::min(float a,float b){
  float ret;
  a<=b ? ret= a : ret=b;
  return ret;
}

float NcReader::abs(float a,float b){
  float ret;
  (a-b)>0 ? ret = a-b: ret -a+b;
  return ret;
}

