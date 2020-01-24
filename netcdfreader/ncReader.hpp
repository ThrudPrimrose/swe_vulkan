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
#include <glm/glm.hpp>

#define error(e) {std::cout<<"error with number"<<e<<std::endl; exit(-1);}



//Reads from a netcdf array of input and output
//build a static image of the t=0;
class NcReader  {
  protected:
  glm::vec3 limegreen = {0.196, 0.804, 0.196};
  glm::vec3 cyan = {0.08,0.92,0.97};
  glm::vec3 white = {0.97,0.97,0.97};
  glm::vec3 red = {0.97,0.08,0.08};
    
    int nx; //!< Size of the x-coordinates array
    int ny; //!< Size of the y-coordinates array

    std::vector<float> h_vec; //!< Dynamic array for waterheights, maps 2D h array to 1D
    std::vector<float> b_vec; //!< Dynamic array for bathymetry values, maps 2D h array to 1D
    std::vector<float> times_vec; //!< Dynamic array for simulation times for timesteps
    
    bool init = false; //!< Boolean for initialization of the dynamic arrays 
    bool generatedValues = false;
    float timelimit; //!< Endtime for the simulation

    int l_bound; //!< Boundary type of the left edge
    int r_bound; //!< Boundary type of the right edge
    int t_bound; //!< Boundary type of the top edge
    int b_bound; //!< Boudnary type of the bottom edge

    int curtimestep = 0; //!< Timestep of the last checkpoint
    int maxGeneratedTime = 0;
    float curtime; //!< The simulation time of the last checkpoint
  
    
  public:
  std::vector<Vertex> vertexArray;
  std::vector<uint16_t> indexArray;

  std::string afterquake ; //!< Stores the name of the bathymetry file
  std::string beforequake ; //!< Stores the name of the displacement file
  
  void readAndInit(std::string b);
  float getBathymetry(int x, int y);
  float getWaterHeight(int x, int y);
  float getWaterHeight(int x, int y, int time);
 
  int getTimeStep();
  float getTime();
  int getLNX();
  int getLNY();
 
  float max(float a,float b);
  float min(float a,float b);
  float abs(float a,float b);

};

#endif