#pragma once
#include <memory>
#include "GLFW/glfw3.h"
#include "Types.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"

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
		InputManager input;
		GraphicsManager graphics;
		ResourceManager resources;
		SoundManager sounds;

		//order in the way they are declared
		Engine() : input(*this) , graphics(*this), resources(*this), sounds(*this){} //, graphics(*this) {}
		//~Engine();
		void StartUp();
		void ShutDown();
		//void RunGameLoop(const UpdateCallback& callback(char));
		//void RunGameLoop(void (*callback)(char));
		void RunGameLoop(const UpdateCallback& callback);
		//void RunGameLoop();
		void Test();

	};


}
