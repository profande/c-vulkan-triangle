#include "graphics_internal.h"

#include <stdio.h>
#include <stdlib.h>

internal GLFWwindow *window;

internal VkInstance instance;

internal VkSurfaceKHR surface;

internal GLFWwindow *InitWindow(uint32 w, uint32 h, const char *name) {
     if (glfwInit() == GLFW_FALSE) {
        const char *err = NULL;
        glfwGetError(&err);
        fprintf(stderr, "glfwInit failed! glfwGetError: %s\n", err);

        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(w, h, name, NULL, NULL);
    if (window == NULL) {
        const char *err = NULL;
        glfwGetError(&err);
        fprintf(stderr, "glfwCreateWindow failed! glfwGetError: %s\n", err);

        exit(EXIT_FAILURE);
    }

    return window;
}

GLFWwindow *InitGraphics(uint32 w, uint32 h, const char *name) {
    window = InitWindow(w, h, name);
    
    CreateInstance(&instance);

    if (glfwCreateWindowSurface(instance, window, NULL, &surface) != VK_SUCCESS) {
        const char *err = NULL;
        glfwGetError(&err);
        fprintf(stderr, "glfwCreateWindowSurface failed! glfwGetError: %s\n", err);

        exit(EXIT_FAILURE);
    }

    return window;
}

void GraphicsCleanup() {
    vkDestroyInstance(instance, NULL);

    glfwTerminate();
}