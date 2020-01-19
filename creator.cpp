#include "creator.hpp"



void Creator::cleanup(){
    dev.cleanupSwapChain();

    vkDestroySampler(dev.logicDevice, dev.textureSampler, nullptr);
    vkDestroyImageView(dev.logicDevice, dev.textureImageView, nullptr);
    
    vkDestroyImage(dev.logicDevice, dev.textureImage, nullptr);
    vkFreeMemory(dev.logicDevice, dev.textureImageMemory, nullptr);

    vkDestroyDescriptorSetLayout(dev.logicDevice, dev.descriptorSetLayout, nullptr);
    vkDestroyBuffer(dev.logicDevice, dev.indexBuffer, nullptr);
    vkFreeMemory(dev.logicDevice, dev.indexBufferMemory, nullptr);

    vkDestroyBuffer(dev.logicDevice, dev.vertexBuffer, nullptr);
    vkFreeMemory(dev.logicDevice, dev.vertexBufferMemory, nullptr);

    for (size_t i = 0; i < dev.MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(dev.logicDevice, dev.renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(dev.logicDevice, dev.imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(dev.logicDevice, dev.inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(dev.logicDevice, dev.commandPool, nullptr);

    vkDestroyDevice(dev.logicDevice, nullptr);

    if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }
    vkDestroySurfaceKHR(instance, gui.surface, nullptr);
    vkDestroyInstance(instance, nullptr);
    gui.killWindow();
}

void Creator::mainLoop(){
    while(!gui.shouldClose()){
        gui.poll();
        drawFrame();
    }
    vkDeviceWaitIdle(dev.logicDevice);
}

void Creator::createInstance(){
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

void Creator::initVulkan(){
    createInstance();
    setupDebugMessenger();
    gui.createSurface(instance);
    dev.pickPhysicalDevice(instance,gui.surface);
    dev.createLogicalDevice(enableValidationLayers, validationLayers,gui.surface);
    dev.createSwapChain(gui.surface);
    dev.createImageViews();
    dev.createRenderPass();
    dev.createDescriptorSetLayout();
    dev.createGraphicsPipeline();
    dev.createFramebuffers();
    dev.createCommandPool(gui.surface);
    dev.createTextureImage();
    dev.createTextureImageView();
    dev.createTextureSampler();
    dev.createVertexBuffer();
    dev.createIndexBuffer();
    dev.createUniformBuffers();
    dev.createDescriptorPool();
    dev.createDescriptorSets();
    dev.createCommandBuffers();
    dev.createSyncObjects();
}




void Creator::run(){
    gui.size.first=width;
    gui.size.second=height;
    gui.initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}


void Creator::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
    }

    void Creator::setupDebugMessenger() {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);

        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    std::vector<const char*> Creator::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    bool Creator::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

     VKAPI_ATTR VkBool32 VKAPI_CALL Creator::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

void Creator::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

VkResult Creator::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}



void Creator::drawFrame() {
        vkWaitForFences(dev.logicDevice, 1, &dev.inFlightFences[dev.currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(dev.logicDevice, dev.swapChain, UINT64_MAX, 
        dev.imageAvailableSemaphores[dev.currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            dev.recreateSwapChain(gui.window,gui.surface);
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        if (dev.imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(dev.logicDevice, 1, &dev.imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        }
        dev.imagesInFlight[imageIndex] = dev.inFlightFences[dev.currentFrame];

        updateUniformBuffer(imageIndex);
        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {dev.imageAvailableSemaphores[dev.currentFrame]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &dev.commandBuffers[imageIndex];

        VkSemaphore signalSemaphores[] = {dev.renderFinishedSemaphores[dev.currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(dev.logicDevice, 1, &dev.inFlightFences[dev.currentFrame]);

        if (vkQueueSubmit(dev.graphicsQueue, 1, &submitInfo, dev.inFlightFences[dev.currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {dev.swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(dev.presentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || gui.framebufferResized) {
            gui.framebufferResized = false;
            dev.recreateSwapChain(gui.window,gui.surface);
        } else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        dev.currentFrame = (dev.currentFrame + 1) % dev.MAX_FRAMES_IN_FLIGHT;
    }


void Creator::updateUniformBuffer(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBufferObject ubo = {};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), dev.swapChainExtent.width / (float) dev.swapChainExtent.height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;   

    void* data;
    vkMapMemory(dev.logicDevice, dev.uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(dev.logicDevice, dev.uniformBuffersMemory[currentImage]);
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
