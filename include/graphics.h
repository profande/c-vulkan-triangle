#pragma once

#include "common.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// Initializes Vulkan and returns a GLFWwindow *
GLFWwindow *InitGraphics(uint32 w, uint32 h, const char *name);

// Deinitializes Vulkan and terminates GLFW
void GraphicsCleanup();