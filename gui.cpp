#include "gui.hpp"

MoveInfo Gui::move_msg = NOPE; //why here?
bool Gui::framebufferResized = false;

void Gui::initWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(size.first,size.second, "Vulkan", nullptr, nullptr);
    glfwSetKeyCallback(window,key_callback_press); //set callback for press actions
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    
}

bool Gui::shouldClose(){
    if (glfwWindowShouldClose(window)){
        return true;
    }else {
        return false;
    }
}

MoveInfo Gui::poll(){
    glfwPollEvents();
    //TODO: MOVEMENT ACTIONS
    return NOPE;
}

void Gui::key_callback_press(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action ==GLFW_PRESS){
        move_msg = UP;
           std::cout<<"pressed up"<<std::endl;
    }
}


void Gui::createSurface(VkInstance instance){
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void Gui::querysizes(int* width, int* height){
    glfwGetFramebufferSize(window, width, height);
}

void Gui::killWindow(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Gui::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    framebufferResized = true;
}

void Gui::inqChange(int &height, int &width){
    glfwGetFramebufferSize(window, &width, &height);
}

