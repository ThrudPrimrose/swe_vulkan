
    #include "ncReader.hpp"
    int NcReader::readAndInit(std::string b,std::string a){
            if(init==true){
                std::cout << "initializing twices shuld now happen and may idnicate a bug!"<<std::endl;
            }
            init = true;
            int ncid;
            int *varid;
            //open file
            //std::cout<<"init1"<<std::endl;
            int e = nc_open(b.c_str(),NC_NOWRITE,&ncid);
            //std::cout<<e<<std::endl;
            char xname;
            char yname;
            int xid;
            int yid;
            size_t xsize;
            size_t ysize;

            //notall of them are used need for nc_inq call
            int numofdim;
            int numofvar;
            int numofattr;
            int numofunl;
            int ex= nc_inq(ncid,&numofdim,&numofvar,&numofattr,&numofunl);

            //std::cout<<e<<std::endl;
            e = nc_inq_dimid(ncid,"x",&xid); if(e!=0)error(e);
            //std::cout<<"x"<<std::endl;
            e = nc_inq_dim(ncid,xid,&xname,&xsize); if(e!=0)error(e);
            e = nc_inq_dimid(ncid,"y",&yid); if(e!=0)error(e);
            //std::cout<<"y"<<std::endl;
            e = nc_inq_dim(ncid,yid,&yname,&ysize); if(e!=0)error(e);
             // std::cout<<e<<std::endl;

            int nx = static_cast<int>(xsize);
            nxb=nx;
            int ny = static_cast<int>(ysize);
            nyb=ny;
           //std::cout<<nxb<<" "<<nyb<<std::endl;
            //std::cout<<e<<std::endl;

            //std::cout<<1<<std::endl;
            int zid;
            //std::cout<<ny<<" "<<nx<<std::endl;
            
            //std::cout<<2<<std::endl;
            double *xcor = new double[nx];
            //std::cout<<3<<std::endl;
            double *ycor = new double[ny];
            //std::cout<<e<<std::endl;
            double *data = new double[nyb*nxb];
            //std::cout<<"100"<<std::endl;

            e = nc_inq_varid(ncid,"z",&zid); if(e!=0)error(e);
            //std::cout<<"z"<<std::endl;
            e = nc_get_var_double(ncid,zid,data); if(e!=0)error(e);
            //std::cout<<e<<std::endl;
            e = nc_inq_varid(ncid,"x",&xid); if(e!=0)error(e);
            e = nc_inq_varid(ncid,"y",&yid); if(e!=0)error(e);
            e = nc_get_var_double(ncid, xid, xcor); if(e!=0)error(e);
            e = nc_get_var_double(ncid, yid, ycor); if(e!=0)error(e);

            xvalbefore.insert(xvalbefore.end(), xcor, xcor+ nx);
            yvalbefore.insert(yvalbefore.end(), ycor, ycor+ ny); 
            zvalbefore.insert(zvalbefore.end(), data, data+ (ny*nx));
            //*xvalbefore = *xcor;
            //*yvalbefore = *ycor;
            //*zvalbefore = *data;
            e = nc_close(ncid);

            int ncid2;
            int *varid2;
            //open file
            //std::cout<<"init2"<<std::endl;
            e = nc_open(a.c_str(),NC_NOWRITE,&ncid2);
            //std::cout<<e<<std::endl;
            char xname2;
            char yname2;
            int xid2;
            int yid2;
            size_t xsize2;
            size_t ysize2;

            //notall of them are used need for nc_inq call
            int numofdim2;
            int numofvar2;
            int numofattr2;
            int numofunl2;
            int ex2= nc_inq(ncid2,&numofdim2,&numofvar2,&numofattr2,&numofunl2);

            e = nc_inq_dimid(ncid2,"x",&xid2); if(e!=0)error(e);
            e = nc_inq_dim(ncid2,xid,&xname2,&xsize2); if(e!=0)error(e);
            e = nc_inq_dimid(ncid2,"y",&yid2); if(e!=0)error(e);
            e = nc_inq_dim(ncid2,yid2,&yname2,&ysize2); if(e!=0)error(e);

            int nx2 = static_cast<int>(xsize2);
            nxa=nx2;
            int ny2 = static_cast<int>(ysize2);
            nya=ny2;

            int zid2;
            double* data2 = new double[ny2*nx2];
            double* xcor2 = new double[nx2];
            double* ycor2 = new double[ny2];

            e = nc_inq_varid(ncid2,"z",&zid2); if(e!=0)error(e);
            e = nc_get_var_double(ncid2,zid2,data2); if(e!=0)error(e);

          


            e = nc_inq_varid(ncid2,"x",&xid2); if(e!=0)error(e);
            e = nc_inq_varid(ncid2,"y",&yid2); if(e!=0)error(e);
            e = nc_get_var_double(ncid2, xid2, xcor2); if(e!=0)error(e);
            e = nc_get_var_double(ncid2, yid2, ycor2); if(e!=0)error(e);

            xvalafter.insert(xvalafter.end(), xcor2, xcor2 +nx2);
            yvalafter.insert(yvalafter.end(), ycor2, ycor2 +ny2); 
            zvalafter.insert(zvalafter.end(), data2, data2 +ny2*nx2);
            //*xvalafter = *xcor2;
            //*yvalafter = *ycor2;
            //*zvalafter = *data2;
    
            /*for(int i=0;i<nxa;i++){
               
               std::cout<< xvalafter[i]<<std::endl;
            }
            for(int j=0;j<nya;j++){
                 
               std::cout<< yvalafter[j]<<std::endl;
            }*/
            
            /*for(int l=0;l<ny2;l++){
                for(int k=0;k<nx2;k++){
                     std::cout<< zvalafter[l*nx2+k]<<std::endl;
                }
               //std::cout<< zvalbefore[l]<<std::endl;
            }
            */

            createArrays();
            return 0;
            
    }
    /*! \fn float getBathymetry(float x, float y) 
    * \brief Returns the z value for the given location.
    * 
    * Indexes are calculated with binary search over the x and y coordinations arrays if the displacement is 
    * not equal to zero the displacement is added.  Which is the sum of the bathymetry before and after the
    * displacement
    * 
    * \param x x-coordinate
    * \param y y-coordinate
    * \return bathymetry value for the location (x,y) after the earthquake (or. other cause of displacement) 
    */
    float NcReader::getBathymetry(float x, float y) {
        //get indexes for z value
        int xa= getClose(xvalbefore,0,nxb,x);
        int ya= getClose(yvalbefore,0,nyb,y);
        double bef = zvalbefore[ya*nxb+xa];
        double disz = 0.f;
        //std::cout<<"iteration "<<iter<<std::endl;
        //check if there is displacement
        //if the indexes are in the boundary of the displacments calculate to displacement 
        if(xvalbefore[xa]>=xvalafter[0] && xvalbefore[xa]<=xvalafter[nxa-1] 
        && yvalbefore[ya]<=yvalafter[nya-1] && yvalbefore[ya]>=yvalafter[0]){
            //then displacement is not 0
            //because the values for our indexes are also in displacement array
            int locinnew_x = getClose(xvalafter,0,nxa,x);
            int locinnew_y = getClose(yvalafter,0,nya,y);
            disz = zvalafter[locinnew_y*nxa+locinnew_x];
            //std::cout<<"indsly"<<std::endl;
        }else{
                disz = 0.f;
        
        }

        //values of [-20,0) are mapped to -20 and
        //(0,20] are mapped to 20. 
        if (bef+disz>-20 && bef+disz<0){
          return -20;
        }else if (bef+disz<20 && bef+disz>=0){
          return 20;
        }else{
          return (float)bef +disz;
        }
        
        return (float)(bef + disz);
    }
    
     /*! \fn float getWaterHeight(float x, float y)
    * \brief Gets the waterheight at the given location (x,y)
    * 
    * \param x x-coordinate
    * \return y y-coordinate
    * 
    * Calculates the water height at location (x,y) is a value in (0,inf), is equal to
    * negative of the bathymetry before the displacement
    * \return water height at the location (x,y)
   */


    float NcReader::getWaterHeight(float x, float y) { 
        int xb= getClose(xvalbefore,0,nxb,x);
        int yb= getClose(yvalbefore,0,nyb,y);
        double tmp = zvalbefore[(yb*nxb)+xb];
        //std::cout<<tmp<<std::endl;
        
        if(tmp>=0 && tmp<20){
          tmp = 0.0;
        }else if(tmp<0 && tmp>-20){
          tmp = -20.0;
        }
        double height = -std::min(tmp,0.0);
        

        return (float)height;

    }

    void NcReader::createArrays(){

        
    }