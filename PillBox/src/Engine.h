#pragma once
#include "Types.h"

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

	private:
		GraphicsManager graphics;
	};


}
