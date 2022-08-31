#include "Engine.h"
#include <thread>
#include <chrono>


using namespace Pillbox;

/*
Engine::Engine()
{
	g = GraphicsManager();
}
*/
void Engine::StartUp()
{	
	graphics.StartUp();
}

void Engine::ShutDown()
{
	graphics.ShutDown();
}

void Engine::RunGameLoop()
{
	graphics.StartUp();

	const auto one_sixteith_of_a_second = std::chrono::duration<real>(1. / 60.);
	while (true)
	{
		auto t1 = std::chrono::steady_clock::now(); //start of tick
		graphics.Draw();

		auto t2 = std::chrono::steady_clock::now(); //end of tick
	
		auto time_took = t2 - t1;
		std::this_thread::sleep_for(one_sixteith_of_a_second - time_took);
	}

	ShutDown();
}

