#include "InputManager.h"


using namespace Pillbox;

void InputManager::StartUp()
{
	
}

void InputManager::Update()
{
	glfwPollEvents();
	//std::cout << "press c: " << glfwGetKey(window, GLFW_KEY_C) << "\n";


}



void InputManager::ShutDown()
{

}
int InputManager::KeyIsPressed(int keyName)
{
	return glfwGetKey(window, keyName);
}

void InputManager::SetWindow(GLFWwindow* w)
{
	window = w;
}