#ifndef GUI
#define GUI

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility> 

#ifdef TWOD
#include "device2D.hpp"
#else
#include "deviceTexture.hpp"
#endif 

#include "device.hpp"

class Gui {
    private:
    static void key_callback_press(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:
    VkSurfaceKHR surface;
    static MoveInfo move_msg;
    std::pair <int,int> size;
    GLFWwindow* window;
    static bool framebufferResized;
    uint32_t minImageCount =2;
   
    void initWindow();
    bool shouldClose();
    MoveInfo poll();
    void killWindow(Device dev);
    void createSurface(VkInstance instance);
    void querysizes(int *width, int *height);
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    void inqChange(int &height, int &width);
    void check_vk_result(VkResult x);

};


#endif