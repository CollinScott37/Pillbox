#pragma once
#include "Types.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace Pillbox
{
	class GraphicsManager
	{
	public:
		Engine& engine;
		GraphicsManager(Engine& e) : engine(e) {}
		friend class InputManager;
		void StartUp();
		void ShutDown();
		void Draw();
		
		GLFWwindow* GetWindow();
		
		int ShouldQuit();
		void SetShouldQuit(bool);

	private:
		GLFWwindow* window;
		//Engine& engine;
	};
}