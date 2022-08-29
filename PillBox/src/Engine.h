#pragma once

#include "Types.h"
/*	Stores all of the various managers
	Starts them up
	Runs the game loop
	Shuts the managers down
*/
namespace Pillbox
{
	class Engine
	{
	public:
		GraphicsManager graphics;
		//InputManager input;

		void StartUp(bool start)
		{
			graphics.StartUp();
		}

		void ShutDown(bool end)
		{
			graphics.ShutDown();
		}

		
	
	};
}
