#include "creator.hpp"

 void Creator::createInstance() {
    if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
}

void Creator::run(){
    interface.initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void Creator::initVulkan(){
    createInstance();
    setupDebugMessenger(instance, debugMessenger);
    interface.createSurface(instance);
    gDevice.pickPhysicalDevice(instance, interface.surface);
    gDevice.createLogicalDevice(instance,enableValidationLayers,validationLayers,interface.surface);
    gDevice.HEIGHT = interface.HEIGHT;
    gDevice.WIDTH = interface.WIDTH;
    gDevice.createSwapchain(interface.surface);
    gDevice.createImageViews();
    gDevice.createRenderPass();
    gDevice.createGraphicsPipeline();
}

void Creator::mainLoop() {
        while (!interface.shouldClose()) {
           interface.poll();
        }
    }

void Creator::cleanup(){
    vkDestroyPipeline(gDevice.logicDevice, gDevice.graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(gDevice.logicDevice, gDevice.pipelineLayout, nullptr);
    vkDestroyRenderPass(gDevice.logicDevice, gDevice.renderPass, nullptr);
    vkDestroyPipelineLayout(gDevice.logicDevice, gDevice.pipelineLayout, nullptr);
    for (auto imageView : gDevice.swapChainImageViews) {
        vkDestroyImageView(gDevice.logicDevice, imageView, nullptr);
    }
    vkDestroySwapchainKHR(gDevice.logicDevice, gDevice.swapChain, nullptr);
    vkDestroyDevice(gDevice.logicDevice, nullptr);
    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }
    vkDestroySurfaceKHR(instance, interface.surface, nullptr);
    vkDestroyInstance(instance, nullptr);
    interface.killWindow();
    delete &interface;
    delete &gDevice;
}

Creator::Creator(){
    interface.HEIGHT = HEIGHT;
    interface.WIDTH = WIDTH;
}


int main() {
    Creator app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}