#pragma once
#include "Types.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace Pillbox
{

	//class Engine;
	class InputManager
	{
	public:
		
		void StartUp();
		void Update();
		void ShutDown();
		void SetWindow(GLFWwindow*);
		int KeyIsPressed(int keyName);
	private:
		GLFWwindow* window;
	};
}