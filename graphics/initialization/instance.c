#include "..\graphics_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NDEBUG

internal const char *validation_layers[] = {
    "VK_LAYER_KHRONOS_validation"
};

internal bool8 CheckValidationLayerSupport() {
    uint32 layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, NULL);

    VkLayerProperties *available_layers = malloc(layer_count * sizeof(VkLayerProperties));
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers);

    for (uint64 i = 0; i < array_length(validation_layers); i += 1) {
        bool8 layer_found = false;

        for (uint64 j = 0; j < layer_count; j += 1) {
            if (strcmp(validation_layers[i], available_layers[j].layerName) == 0) {
                layer_found = true;
                break;
            }
        }

        if (!layer_found) {
            return false;
        }
    }

    return true;
}

internal bool32 VKAPI_CALL 
DebugMessageCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
                     VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
                     const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                     void*                                       pUserData) 
{
    fprintf(stderr, "%s\n", pCallbackData->pMessage);

    return VK_FALSE;
}
#endif // NDEBUG

void CreateInstance(VkInstance *instance) {
#ifndef NDEBUG
    if (!CheckValidationLayerSupport()) {
        fprintf(stderr, "Validation layers requested, but not available!\n");
        exit(EXIT_FAILURE);
    }
#endif // NDEBUG

    VkApplicationInfo app_info = { 0 };
    app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName   = "Vulkan Triangle";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName        = "No engine";
    app_info.engineVersion      = VK_MAKE_VERSION(0, 0, 0);
    app_info.applicationVersion = VK_API_VERSION_1_2;

    VkInstanceCreateInfo create_info = { 0 };
    create_info.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    uint32 extension_count = 0;
    const char **glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&extension_count);

    const char **extensions = malloc(extension_count * sizeof(const char *));
    memcpy(extensions, glfw_extensions, extension_count * sizeof(const char *));

#ifndef NDEBUG
    extensions = realloc(extensions, ++extension_count * sizeof(const char *));
    extensions[extension_count - 1] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
#endif

    create_info.enabledExtensionCount   = extension_count;
    create_info.ppEnabledExtensionNames = extensions;

#ifndef NDEBUG
    create_info.enabledLayerCount   = array_length(validation_layers);
    create_info.ppEnabledLayerNames = validation_layers;

    VkDebugUtilsMessengerCreateInfoEXT debug_create_info = { 0 };
    debug_create_info.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debug_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT   ;
    debug_create_info.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT     |
                                        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
                                        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT  ;
    debug_create_info.pfnUserCallback = DebugMessageCallback;
    
    create_info.pNext = &debug_create_info;
#elif
    create_info.enabledLayerCount = 0;
    create_info.pNext             = NULL;
#endif // NDEBUG

    if (vkCreateInstance(&create_info, NULL, instance) != VK_SUCCESS) {
        fprintf(stderr, "Vulkan Instance Creation failed\n");
        exit(EXIT_FAILURE);
    }

    free(extensions);
}