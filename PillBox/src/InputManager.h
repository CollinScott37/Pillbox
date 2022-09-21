#pragma once
#include "Types.h"
#define GLFW_INCLUDE_NONE
//#include "GLFW/glfw3.h"


namespace Pillbox
{

	class InputManager
	{
		
	public:
		int keys[26][2]; //keyid is index [0] is prev input [1] is current input
		Engine& engine;
		InputManager(Engine& anEng) : engine(anEng) {}
		void StartUp();
		void Update();
		void ShutDown();
		void SetWindow(GLFWwindow*);
		void MoveCurrKeyToPrev();
		void UpdateCurrKey();
		bool GetKeyCodeUp(int keyName);
		bool GetKeyCodeDown(int keyName);

	private:
		GLFWwindow* window;
		
	};
}