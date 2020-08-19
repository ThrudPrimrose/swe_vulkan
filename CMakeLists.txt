cmake_minimum_required(VERSION 3.10)

project(swe_vulkan)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

option(THRID "Build for 3D rendering" OFF)
option(TWOD "Build for 2D rendering" ON)
option(LIVE "Build for Live integration to SWE_E" OFF)

if(THRID)
	add_definitions(-DTHRID)
endif()

if(TWOD)
	add_definitions(-DTWOD)
endif()

if(LIVE)
	add_definitions(-DLIVE)
endif()

file(GLOB_RECURSE sources "src/*.cpp")

add_executable(renderer ${sources})

find_package(NetCDF REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

target_include_directories(renderer PRIVATE $ENV{HOME}/libraries/stb)
target_include_directories(renderer PRIVATE ${Vulkan_INCLUDE_DIRS})
target_include_directories(renderer PRIVATE $ENV{HOME}/libraries/tinyobjloader)
target_include_directories(renderer PRIVATE $ENV{HOME}/libraries/stb)
target_include_directories(renderer PRIVATE ${NETCDF_INCLUDE_DIRS})
target_link_libraries(renderer PRIVATE ${NETCDF_LIBRARIES})
target_link_libraries(renderer PRIVATE ${Vulkan_LIBRARIES})
target_link_libraries(renderer PRIVATE glfw)

target_compile_options(renderer PRIVATE -O3)
