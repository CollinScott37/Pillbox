#pragma once
#include "Types.h"
#include "GraphicsManager.h"
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
		//Engine(); constructor?
		
		void StartUp();
		void ShutDown();
		void RunGameLoop();

	private:
		GraphicsManager graphics;
	};


}
