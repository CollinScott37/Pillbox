#pragma once
#include "Types.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"


namespace Pillbox
{

	class InputManager
	{
		
	public:
		
		Engine& engine;
		InputManager(Engine& anEng) : engine(anEng) {}
		void StartUp();
		void Update();
		void ShutDown();
		void SetWindow(GLFWwindow*);
		bool KeyIsPressed(int keyName);	
	private:
		GLFWwindow* window;
		
	};
}