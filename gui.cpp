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

void Gui::setupImguiContext(Device dev, VkInstance instance, VkQueue guiQueue){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForVulkan(window, true);
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = instance;
    init_info.PhysicalDevice = dev.physicalDevice;
    init_info.Device = dev.logicDevice;
    init_info.QueueFamily = dev.qFamilyInd;
    init_info.Queue = dev.graphicsQueue;
    init_info.PipelineCache = VK_NULL_HANDLE;
    createGuiDPool(dev,guiQueue);
    init_info.DescriptorPool = guiDescriptorPool;
    init_info.Allocator = nullptr;
    init_info.MinImageCount = minImageCount;
    init_info.ImageCount = dev.swapChainImages.size();
    init_info.CheckVkResultFn = check_vk_result;
    ImGui_ImplVulkan_Init(&init_info, dev.renderPass);
    
}

void Gui::createGuiDPool(Device dev, VkQueue guiQueue){
 VkDescriptorPoolSize pool_sizes[] =
        {
            { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
        };
        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
        pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
        pool_info.pPoolSizes = pool_sizes;
        std::cout<<"ishere"<<std::endl;
        VkResult err = vkCreateDescriptorPool(dev.logicDevice, &pool_info, VK_NULL_HANDLE, &guiDescriptorPool);
        check_vk_result(err);
}

void Gui::createGuiRenderPass(Device dev){
    VkAttachmentDescription attachment = {};
    attachment.format = dev.swapChainImageFormat;
    attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    attachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
    attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachment.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;    
    VkAttachmentReference color_attachment = {};
    color_attachment.attachment = 0;
    color_attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_attachment;
    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;  // or VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    VkRenderPassCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    info.attachmentCount = 1;
    info.pAttachments = &attachment;
    info.subpassCount = 1;
    info.pSubpasses = &subpass;
    info.dependencyCount = 1;
    info.pDependencies = &dependency;
    if (vkCreateRenderPass(dev.logicDevice, &info, nullptr, &dev.guiRenderPass) != VK_SUCCESS) {
        throw std::runtime_error("Could not create Dear ImGui's render pass");
    }

    //upload text to gpu - w one time command buffer
    VkCommandBuffer commandBuffer = dev.beginSingleTimeCommands();
    ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
    dev.endSingleTimeCommands(commandBuffer);   

 
}

void Gui::check_vk_result(VkResult x){
    if(x!=VK_SUCCESS){
        std::cout<<"yabai desu"<<std::endl;
        exit(-1);
    }
}

void Gui::drawObjects(Device dev){
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    ImGui::Render();

    memcpy(&guiObjWindow.ClearValue.color.float32[0], &clear_color, 4 * sizeof(float));
    //too hard do it later   
    FrameRender(&guiObjWindow,dev);
    //FramePresent(guiObjWindow);
}


void Gui::FrameRender(ImGui_ImplVulkanH_Window* wd, Device dev){
    //this parts results in segmentation fault
    /*VkSemaphore image_acquired_semaphore  = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
    VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
    VkResult err = vkAcquireNextImageKHR(dev.logicDevice, wd->Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &wd->FrameIndex);
    check_vk_result(err);*/
    
    /*ImGui_ImplVulkanH_Frame* fd = &(wd.Frames[wd.FrameIndex]);
    {
        err = vkWaitForFences(dev.logicDevice, 1, &fd->Fence, VK_TRUE, UINT64_MAX);    // wait indefinitely instead of periodically checking
        check_vk_result(err);

        err = vkResetFences(dev.logicDevice, 1, &fd->Fence);
        check_vk_result(err);
    }*/

}


//rebuilds the gui object for the window
void Gui::rebuild(Device dev,VkInstance instance){
    int height,width;
    glfwGetFramebufferSize(window,&height,&width);

    ImGui_ImplVulkan_SetMinImageCount(minImageCount);
    ImGui_ImplVulkanH_CreateWindow(instance, dev.physicalDevice,
    dev.logicDevice, &guiObjWindow, 
    dev.qFamilyInd , VK_NULL_HANDLE, width, height, 1);
    guiObjWindow.FrameIndex = 0;

}

void Gui::createGuiCommandPool(Device dev,VkCommandPool* commandPool, VkCommandPoolCreateFlags flags) {
    VkCommandPoolCreateInfo commandPoolCreateInfo = {};
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.queueFamilyIndex = dev.qFamilyInd;
    commandPoolCreateInfo.flags = flags;

    if (vkCreateCommandPool(dev.logicDevice, &commandPoolCreateInfo, nullptr, commandPool) != VK_SUCCESS) {
        throw std::runtime_error("Could not create graphics command pool");
    }
}

void Gui::createGuiCommandBuffers(Device dev, VkCommandBuffer* commandBuffer, uint32_t commandBufferCount, VkCommandPool &commandPool) {
    VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocateInfo.commandPool = commandPool;
    commandBufferAllocateInfo.commandBufferCount = commandBufferCount;
    vkAllocateCommandBuffers(dev.logicDevice, &commandBufferAllocateInfo, commandBuffer);
}
