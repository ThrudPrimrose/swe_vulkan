#ifndef GUI
#define GUI

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility> 

#include <imgui.h>
#include <examples/imgui_impl_vulkan.h>
#include <examples/imgui_impl_glfw.h>

#include "deviceTexture.hpp"
#include "device.hpp"

enum MoveInfo{
    UP,DOWN,LEFT,RIGHT,ZIN,ZOUT,NOPE,REBUILD
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
    ImGui_ImplVulkanH_Window guiObjWindow;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    VkDescriptorPool guiDescriptorPool;
    uint32_t minImageCount =2;
    std::vector<VkCommandPool> guiCommandPools;
    std::vector<VkCommandBuffer> guiCommandBuffers;

    void initWindow();
    bool shouldClose();
    MoveInfo poll();
    void killWindow(DeviceTexture dev);
    void createSurface(VkInstance instance);
    void querysizes(int *width, int *height);
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    void inqChange(int &height, int &width);

    void setupImguiContext(DeviceTexture dev, VkInstance instance, VkQueue guiQueue);
    void createGuiDPool(DeviceTexture dev, VkQueue guiQueue);
    void createGuiRenderPass(DeviceTexture dev);
    void rebuild(DeviceTexture dev,VkInstance instance);
    void drawObjects(DeviceTexture dev);
    static void check_vk_result(VkResult x);
    void FrameRender(ImGui_ImplVulkanH_Window* guiObjWindow, DeviceTexture dev);
    void createGuiCommandPool(DeviceTexture dev,VkCommandPool* commandPool, VkCommandPoolCreateFlags flags);
    void createGuiCommandBuffers(DeviceTexture dev,VkCommandBuffer* commandBuffer, uint32_t commandBufferCount, VkCommandPool &commandPool);

};


#endif