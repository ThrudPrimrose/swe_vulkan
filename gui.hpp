#ifndef GUI
#define GUI

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility> 

#include <imgui.h>
#include <examples/imgui_impl_vulkan.h>
#include <examples/imgui_impl_glfw.h>

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
    ImGui_ImplVulkanH_Window guiObjWindow;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    VkDescriptorPool guiDescriptorPool;
    uint32_t minImageCount =2;
    std::vector<VkCommandPool> guiCommandPools;
    std::vector<VkCommandBuffer> guiCommandBuffers;

    void initWindow();
    bool shouldClose();
    MoveInfo poll();
    void killWindow(Device dev);
    void createSurface(VkInstance instance);
    void querysizes(int *width, int *height);
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    void inqChange(int &height, int &width);

    void setupImguiContext(Device dev, VkInstance instance, VkQueue guiQueue);
    void createGuiDPool(Device dev, VkQueue guiQueue);
    void createGuiRenderPass(Device dev);
    void rebuild(Device dev,VkInstance instance);
    void drawObjects(Device dev);
    static void check_vk_result(VkResult x);
    void FrameRender(ImGui_ImplVulkanH_Window* guiObjWindow, Device dev);
    void createGuiCommandPool(Device dev,VkCommandPool* commandPool, VkCommandPoolCreateFlags flags);
    void createGuiCommandBuffers(Device dev,VkCommandBuffer* commandBuffer, uint32_t commandBufferCount, VkCommandPool &commandPool);

};


#endif