#ifndef GUI
#define GUI

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>


enum MoveInfo{
    UP,DOWN,LEFT,RIGHT,ZIN,ZOUT,NOPE
};

class gui {
    private:
    GLFWwindow* window;
    
    static void key_callback_press(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:
    VkSurfaceKHR surface;
    static MoveInfo move_msg;
    int HEIGHT = 600;
    int WIDTH = 800;


    void initWindow();
    bool shouldClose();
    MoveInfo poll();
    void killWindow();
    void createSurface(VkInstance instance);
    
};

//MoveInfo gui::move_msg;

#endif