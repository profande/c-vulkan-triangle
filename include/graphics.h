#pragma once

#include "common.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

GLFWwindow *InitGraphics(uint32 w, uint32 h, const char *name);
void GraphicsCleanup();