#pragma once
#include <memory>
#include "Types.h"
#include "GraphicsManager.h"
#include "InputManager.h"

/*	
	Stores all of the various managers
	Starts them up
	Runs the game loop
	Shuts the managers down
*/
namespace Pillbox
{

	
	class Engine
	{
	public:
		Engine(); //constructor ?
		~Engine();
		void StartUp();
		void ShutDown();
		//void RunGameLoop(const UpdateCallback& callback(char));
		//void RunGameLoop(void (*callback)(char));
		void RunGameLoop(void (*callback)(char));
		void Test();
	private:
		GraphicsManager graphics;
		InputManager input;
	};


}
