#include "InputManager.h"
#include "Engine.h";

using namespace Pillbox;

void InputManager::StartUp()
{
	window = engine.graphics.window;
}

void InputManager::Update()
{
	
	glfwPollEvents();
	//std::cout << "press c: " << glfwGetKey(window, GLFW_KEY_C) << "\n";
}



void InputManager::ShutDown()
{

}

bool InputManager::KeyIsPressed(int keyName)
{
	return glfwGetKey(window, keyName) == GLFW_PRESS;
}

void InputManager::SetWindow(GLFWwindow* w)
{
	window = w;
}