#include "creator.hpp"

    void Creator::run() {
        mainLoop();
        cleanup();
    }

    void Creator::mainLoop() {
        while (!interface.shouldClose()){ //wrapper around glfwshouldclose
            interface.poll(); //wrapper around glfw poll eventes
        }
    }

    void Creator::cleanup() {
        delete &gDevice;
        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }
        vkDestroySurfaceKHR(instance, interface.surface, nullptr);
        vkDestroyInstance(instance, nullptr);
        interface.killWindow();
        delete &interface; //destroy our class
    }

    Creator::Creator(){
        createInstance();
        setupDebugMessenger(instance, debugMessenger);
        interface.createSurface(instance);
        //combine gDevice functions to one thing
        gDevice.setSurface(interface.surface); //a hack becasue functions need the surface parameter
        gDevice.pickPhysDevice(instance);
        gDevice.createLogicalDevice(val_layer);
        gDevice.createSwapChain();
        interface.surface = gDevice.surface;
        gDevice.createImageViews();
        gDevice.createGraphicsPipeline();
        //so right now gui and device has surface, any update to surface
        //should be assigned to both just in case

    }

    void Creator::createInstance() {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "SWE";
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
            val_layer= true;
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            val_layer=false;
            createInfo.enabledLayerCount = 0;
            
            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
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