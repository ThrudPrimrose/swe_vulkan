#ifndef GUI
#define GUI

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>


const int WIDTH = 800;
const int HEIGHT = 600;

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

    gui();
    void initWindow();
    bool shouldClose();
    MoveInfo poll();
    void killWindow();
    void createSurface(VkInstance instance);
    
};

//MoveInfo gui::move_msg;

#endif