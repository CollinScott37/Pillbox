#include "GraphicsManager.h"
#include "Engine.h"
using namespace Pillbox;


int window_width = 1280;
int window_height = 720;
const char* window_name = "Pillbox";
bool window_fullscreen = 0; 

void GraphicsManager::StartUp()
{
    //EngineRef.engine->Test();
    glfwInit();
    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(window_width, window_height, window_name, window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
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

void GraphicsManager::Draw()
{

}

GLFWwindow* GraphicsManager::GetWindow()
{
    return window;
}

int GraphicsManager::ShouldQuit()
{
    //std::cout << "HERE1\n";
    return glfwWindowShouldClose(window);
}

void GraphicsManager::SetShouldQuit(bool quit)
{
    std::cout << "HERE2\n";
    glfwSetWindowShouldClose(window, quit);
}
