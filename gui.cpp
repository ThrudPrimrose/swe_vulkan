#include "gui.hpp"

MoveInfo gui::move_msg = NOPE; //why here?

gui::gui(){
    initWindow();
}

void gui::initWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
    glfwSetKeyCallback(window,key_callback_press); //set callback for press actions
}

bool gui::shouldClose(){
    if (glfwWindowShouldClose(window)){
        return true;
    }else {
        return false;
    }
}

MoveInfo gui::poll(){
    glfwPollEvents();
    //TODO: MOVEMENT ACTIONS
    return NOPE;
}

void gui::key_callback_press(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action ==GLFW_PRESS){
        move_msg = UP;
           std::cout<<"pressed up"<<std::endl;
    }
}


void gui::createSurface(VkInstance instance){
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void gui::killWindow(){
    glfwDestroyWindow(window);
    glfwTerminate();
}
