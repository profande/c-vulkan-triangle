#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

int32 main(void) {
    GLFWwindow *window = InitGraphics(SCREEN_WIDTH, SCREEN_HEIGHT, "Vulkan");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    GraphicsCleanup();
    return 0;
}