# Vulkan SWE Renderer

Standalone Vulkan based SWE Renderer for [COARDS](https://ferret.pmel.noaa.gov/Ferret/documentation/coards-netcdf-conventions) netCDF conventions with integration for [SWE\_E](https://gitlab.lrz.de/ge69vuw/swe_e) based on [SWE](https://github.com/TUM-I5/SWE)


![3D Mode over Japan and Pacific](https://i.imgur.com/ECjmLJk.png)

## Dependencies

  - [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/) 1.1 or newer 
  - [STB](https://github.com/nothings/stb) for loading images
  - [TinyObjLoader](https://github.com/syoyo/tinyobjloader) for loadeing models
  - [NetCDF](https://www.unidata.ucar.edu/software/netcdf/) to read from netCDF files

## Installing

Makefile requires the dependencies installed under ~/libraries 
To install you can run the [install.sh](install.sh) script, it will clone the dependencies.

## Building

SWE Renderer supports a **2D** **3D** and **Texture** mode. The precompile flags **TWOD** and **THRID** will result respectively in **2D** and **3D** output, no output will compile the **Texture Mode**, but in essence [2D>3D](https://www.reddit.com/r/Animemes/comments/8n7cn4/2d_3d/)

### Nvidia and Linux
Nvidia GPUs creates issues, you might need to run the following:
```bash
export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/10_nvidia.json
```
You could also run the **run_nvidia.sh** after changing the Vulkan SDK path, it compile if the first argument is **c** and the second input is the mode **TWOD** or **THRID**:
```bash
./run_nvidia.sh c thrid
```
Will result in the image on the top, or just pass the argument to make file:
```bash
make twod
```

## Camera Movements

Momentarily the look angle increases with **+** on **15.00** and with **-** on **-15.00**, Movement buttons **left** and **right** moves the model on x (faces towards the user) axis, **up** and **down** on z (top) axis, **I** and **O** moves the camera to center / away from center  

### Task List
- [x] Basic 2D Support
- [x] Basic 3D Support
- [ ] Loading Texture into 3D Mode
- [x]  MSAA Support
- [x] Transparent Water in 3D
- [ ] Good Camera Support
- [ ] Imgui to create GUI Objects
- [ ] Support for changing Modes on runtime
- [ ] Command Line Argument Parsing 
- [ ] SWE_E Integration

