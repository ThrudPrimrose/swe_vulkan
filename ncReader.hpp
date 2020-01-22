/*! \file ncRead.hpp 
*   \brief The Scenario that reads from an input from a netcdf file
*
*  The Scenario implements a reader. When compiled the option for readnetcdf,
* then the scenario reads from two files. One from a bathymetry file and another
* from a displacement file, which has the net difference of bathymetry in a subdomain.
*/

#ifndef NCREAD
#define NCREAD

#include <string>
#include <cmath>
#include <iostream>
#include "netcdf.h"
//#include <netcdf.h>
#include <vector> 
#include "struct.hpp"
#include <glm/glm.hpp>


#define error(e) {std::cout<<"error with number"<<e<<std::endl; exit(-1);}
#define print(x) {std::cout<<x<<std::endl;}

struct ncVertex {
    float pos[2];
    float color[3];
    float texCoord[2];
};


struct ncVertex3D {
    float pos[3];
    float color[3];
    float texCoord[2];
};



/*! \class ncRead
* \brief Create Vulkan-usable ncVertex buffers
*/
class ncRead {
  private:
    const char* name; //!< Stores the file name of the checkpoint file  
    float i;
    
    int nx; //!< Size of the x-coordinates array
    int ny; //!< Size of the y-coordinates array
    int nt; //!< Size of the timestep array

//     std::vector<float> xloc_vec; //!< Dynamic array for x-coordinates 
//     std::vector<float> yloc_vec; //!< Dynamic array for y-coordinates
//     std::vector<float> h_vec; //!< Dynamic array for waterheights, maps 2D h array to 1D
//     
//     std::vector<float> b_vec; //!< Dynamic array for bathymetry values, maps 2D h array to 1D
//     std::vector<float> t_vec; //!< Dynamic array for simulation times for timesteps
    float* hs; 
    float* bs; 
    float* ts;
    float* xcor;
    float* ycor;
    
    
    std::vector<ncVertex> vertices;
    std::vector<uint16_t> indices;
    
    
    std::vector<ncVertex3D> vertices3D;
    
    std::vector<uint16_t> indices_water;
    std::vector<uint16_t> indices_land;
    
    
  public:
    ncRead();
    
    
     /*! \fn void initArrays(const char* name)
    * \brief Initializes the dynamic arrays and reads from netcdf file
    * 
    * Is only called from the constructor
    */
    void initArrays();
    
    

    /*! \fn float getH(int x, int y, int t)
    * \brief Returns hs[y][x][t] from the netcdf array
    * 
    * \param x x-coordinate index
    * \param y y-coordinate index
    * \param t timestep index
    * \return hs[y][x][t]
    */
    float getH(int x, int y, int t);

     /*! \fn float getB(int x, int y, int t)
    * \brief Returns bs[y][x][t] from the netcdf array
    * 
    * \param x x-coordinate index
    * \param y y-coordinate index
    * \param t timestep index
    * \return bs[y][x][t]
    */
    float getB(int x, int y, int t);
    
     /*! \fn float isWet(int x, int y, int t)
    * \brief Checks if ncVertex is wet
    * 
    * \param x x-coordinate index
    * \param y y-coordinate index
    * \param t timestep index
    * \return h > 0
    */
    bool isWet(int x, int y, int t);
    
    void setPos(float* pos, int x, int y, int t);
    
    // not used yet
    void setPos3D(float* pos, int x, int y, int t);
    
    // colors the ncVertex according to height
    void setColor(float* color, int x, int y, int t);
    
    // linearly maps lowest x (or y) coordinate to 0, and highest to 1
    void setTexCoord(float* coord, int x, int y);

     /*! \fn void createVertices(int t)
    * \brief Populates the ncVertex array
    * 
    * \param t index of the timestep for which the array is created
    */
    void createVertices(float t);
    
     /*! \fn void createVertices(int t)
    * \brief Populates the ncVertex array with height
    * 
    * \param t index of the timestep for which the array is created
    */
    void createVertices3D(float t);
    
    
    
    // gives the index of ncVertex at index (x,y)
    uint16_t vi(int x, int y);
     /*! \fn void createIndices(int t)
    * \brief Populates the ncVertex index array
    */
    void createIndices();
    
     /*! \fn void createIndicesWaterLandSplit(int t)
    * \brief Populates the ncVertex index array, split into 2 according to wetness
    * 
    * Both indices_water and indices_land create objects with a mesh only in the water (bzw. land), 
    * and lots of unconnected vertices (which are not rendered)
    * \param t timestep index, should be irrelevant if no wetting/drying
    */
    void createIndicesWaterLandSplit(int t);
    
};


#endif