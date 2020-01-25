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
  glm::vec3 limegreen = {0.196, 0.874, 0.196};
  glm::vec3 cyan = {0.08,0.92,0.97};
  glm::vec3 white = {0.97,0.97,0.97};
  glm::vec3 red = {0.97,0.08,0.08};
  glm::vec3 coral = {0.95,0.498039,0.0};
  glm::vec3 slateblue =  {0.08,0.4988,0.98};
  glm::vec3 skyblue = {0.196,0.6,0.8};
    
    int nx; //!< Size of the x-coordinates array
    int ny; //!< Size of the y-coordinates array

    
    float start = -1.f; //best to begin from -1
    float end = 1.f; //limit of the array , best to normalize to 1
    
    //this are for print 
    //have nothing to do with dx and dy from swe netcdfreader
    float dx = 0.1f; //distance between two cells in x
    float dy = 0.1f; //distance between two cells in y

    float maxHforWhite = 30.0;
    
    float sY = start; //begin loc for sY

    
    
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
  std::vector<uint32_t> indexArray;

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

  void generateValues();
  void updateMaxH();

};

#endif