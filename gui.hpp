#ifndef GUI
#define GUI

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility> 
enum MoveInfo{
    UP,DOWN,LEFT,RIGHT,ZIN,ZOUT,NOPE
};

class Gui {
    private:
    static void key_callback_press(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:
    VkSurfaceKHR surface;
    static MoveInfo move_msg;
    std::pair <int,int> size;
    GLFWwindow* window;
    static bool framebufferResized;


    void initWindow();
    bool shouldClose();
    MoveInfo poll();
    void killWindow();
    void createSurface(VkInstance instance);
    void querysizes(int *width, int *height);
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    void inqChange(int &height, int &width);
    
};


#endif