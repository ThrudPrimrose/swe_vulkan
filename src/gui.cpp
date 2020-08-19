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
    std::cout<<"initialized window"<<std::endl; 
}

bool Gui::shouldClose(){
    if (glfwWindowShouldClose(window)){
        return true;
    }else {
        return false;
    }
}

MoveInfo Gui::poll(){
    move_msg = NOPE;
    glfwPollEvents();
    //TODO: MOVEMENT ACTIONS
    return move_msg;
}

void Gui::key_callback_press(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action ==GLFW_PRESS){
        move_msg = UP;
        //std::cout<<"pressed up"<<std::endl;
    }else if (key == GLFW_KEY_DOWN && action ==GLFW_PRESS){
        move_msg = DOWN;    
    }else if (key == GLFW_KEY_LEFT && action ==GLFW_PRESS){
        move_msg = LEFT; 
    }else if (key == GLFW_KEY_RIGHT && action ==GLFW_PRESS){
        move_msg = RIGHT;
    }else if (key == GLFW_KEY_I && action ==GLFW_PRESS){
        move_msg = ZIN;
    }else if (key == GLFW_KEY_O && action ==GLFW_PRESS){
        move_msg = ZOUT;
    }else if (key == GLFW_KEY_KP_ADD && action ==GLFW_PRESS){
        move_msg = AP;
    }else if (key == GLFW_KEY_KP_SUBTRACT && action ==GLFW_PRESS){
        move_msg = AM;
    }else{
        move_msg = NOPE;
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

void Gui::killWindow(Device dev){
    //ImGui_ImplVulkan_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Gui::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    framebufferResized = true;
    //std::cout<<"uwu i' movin"<<std::endl;
}

void Gui::inqChange(int &height, int &width){
    glfwGetFramebufferSize(window, &width, &height);
}


void Gui::check_vk_result(VkResult x){
    if(x!=VK_SUCCESS){
        std::cout<<"yabai desu"<<std::endl;
        exit(-1);
    }
}
