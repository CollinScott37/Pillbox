#pragma once
#include "Types.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace Pillbox
{
	class GraphicsManager
	{
	public:
		friend class InputManager;
		void StartUp();
		void ShutDown();
		void Draw();
		GLFWwindow* GetWindow();

	private:
		GLFWwindow* window;
		//Engine& engine;
	};
}