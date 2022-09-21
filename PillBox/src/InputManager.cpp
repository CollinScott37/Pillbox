#include "InputManager.h"
#include "Engine.h";

using namespace Pillbox;

void InputManager::StartUp()
{
	window = engine.graphics.window;
	for (int i = 0; i < 26; i += 1)
	{
		keys[i][0] = 0; //prev key //set all keys to 0;
		keys[i][1] = 0; //curr key //set all keys to 0;
	}
}

void InputManager::Update()
{
	MoveCurrKeyToPrev();
	glfwPollEvents();
	UpdateCurrKey();
	//std::cout << "press c: " << glfwGetKey(window, GLFW_KEY_C) << "\n";
}

void InputManager::MoveCurrKeyToPrev()
{
	for (int i = 0; i < 26; i += 1)
	{
		keys[i][0] = keys[i][1]; //move curr to prev
	}
}

void InputManager::UpdateCurrKey()
{
	for (int i = 0; i < 26; i += 1)
	{
		keys[i][1] = glfwGetKey(window, i + 65);
	}
	keys[25][1] = glfwGetKey(window, GLFW_KEY_ESCAPE);
}

void InputManager::ShutDown()
{

}

//checks if key was realesed
bool InputManager::GetKeyCodeUp(int keyName) 
{
	if(keyName == GLFW_KEY_ESCAPE)
	{
		keyName -= 231;
	}
	else
	{
		keyName -= 65; 
	}
	
	if (keyName > 25 || keyName < 0)
	{
		return false; //fix
	}
	
	if ((keys[keyName][0] == GLFW_PRESS) && (keys[keyName][1] == GLFW_RELEASE))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if key is being help down
bool InputManager::GetKeyCodeDown(int keyName)
{
	if(keyName == GLFW_KEY_ESCAPE)
	{
		keyName -= 231;
	}
	else
	{
		keyName -= 65; 
	}

	if (keyName > 25 || keyName < 0)
	{
		return false; //fix
	}
	
	if (keys[keyName][1] == GLFW_PRESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}
