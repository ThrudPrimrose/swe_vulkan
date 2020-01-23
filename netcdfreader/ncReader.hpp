/*! \file SWE_ReadNetCDF.hpp 
*   \brief The Scenario that reads from an input from a netcdf file
*
*  The Scenario implements a reader. When compiled the option for readnetcdf,
* then the scenario reads from two files. One from a bathymetry file and another
* from a displacement file, which has the net difference of bathymetry in a subdomain.
*/

#ifndef READNETCDF
#define READNETCDF

#include <string>
#include <cmath>
#include <iostream>
#include <netcdf.h>
#include "netcdfHelpers.hpp" 
#include <vector> 
#include "../struct.hpp"

#define error(e) {std::cout<<"error with number"<<e<<std::endl; exit(-1);}

/*! \class SWE_ReadNetCDF
* \brief Scenari that reads from the two input files
*
* Reads the information from two netcdf files and provides the implementations of funtions introduced in SWE_Scenario
*/

class NcReader {
  private:
    
    int timelimit; //!< timelimit of the scenario
    int nxb; //!< Maximal x range of the displacement file
    int nyb; //!< Maximal y range of the displacement file
    int nya; //!< Maximal y range of the bathymetry file
    int nxa; //!< Maximal x range of the bathymetry file
     
    std::vector<double> xvalafter;  //!< Dynamic array for the x values of the displacement file
    std::vector<double> yvalafter;  //!< Dynamic array for the y values of the displacement file
    std::vector<double> zvalafter;  //!< Dynamic array for the z values (= b(x,y)) of the displacement file, maps 2D array to 1D

    std::vector<double> xvalbefore;  //!< Dynamic array for the x values of the bathymetry file
    std::vector<double> yvalbefore; //!< Dynamic array for the y values of the bathymetry file
    std::vector<double> zvalbefore; //!< Dynamic array for the z values (= b(x,y)) of the bathymetry file,maps 2D array to 1D
  
   
    /*
    double* xvalafter;
    double* yvalafter;
    double* zvalafter;

    double* xvalbefore;
    double*yvalbefore;
    double* zvalbefore;
    */

    bool init=false; //!< Boolean that checks wether the dynamic arrays were initiliazed
    
  
  public:
  std::vector<Vertex> vertexArray;
  std::vector<uint16_t> indexArray;

  std::string afterquake ; //!< Stores the name of the bathymetry file
  std::string beforequake ; //!< Stores the name of the displacement file
  
  int readAndInit(std::string b,std::string a);
  void createArrays();
  float getBathymetry(float x, float y);
  float getWaterHeight(float x, float y);


};

#endif