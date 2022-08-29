#include "GraphicsManager.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"


using namespace Pillbox;


int window_width = 1280;
int window_height = 720;
string window_name = "Pillbox";
bool window_fullscreen = 0; 

void GraphicsManager::StartUp()
{
    glfwInit();
    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_name, window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
    glfwSetWindowAspectRatio(window, window_width, window_height);
    if (!window)
    {
        std::cerr << "Failed to create a window." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void GraphicsManager::ShutDown()
{
    glfwTerminate();
}
