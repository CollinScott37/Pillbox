#include "Engine.h"
#include <thread>
#include <chrono>


using namespace Pillbox;

Engine::Engine()
{
	
}

Engine::~Engine()
{

}

void Engine::StartUp()
{	
	graphics.StartUp();
	input.SetWindow(graphics.GetWindow());
	input.StartUp();
}

void Engine::ShutDown()
{
	graphics.ShutDown();
	input.ShutDown();
}

//void Engine::RunGameLoop(const UpdateCallback& callback(char))
//void Engine::RunGameLoop(void (*callback)(char))
void Engine::RunGameLoop()
{
	StartUp();

	const auto one_sixteith_of_a_second = std::chrono::duration<real>(1. / 60.);
	
	bool isdone = graphics.ShouldQuit();
	//std::cout << isdone << "\n";

	while (!isdone)
	{
		auto t1 = std::chrono::steady_clock::now(); //start of tick
		
		input.Update();

		//callback('a');
		
		graphics.Draw();
		
		isdone = graphics.ShouldQuit() || input.KeyIsPressed(GLFW_KEY_Q);

		auto t2 = std::chrono::steady_clock::now(); //end of tick
		auto time_took = t2 - t1;

		std::this_thread::sleep_for(one_sixteith_of_a_second - time_took);
	}
	
	std::cout << "HERE3\n";
	std::cout << isdone << "\n";
	ShutDown();
}

void Engine::Test()
{
	std::cout << "TEST\n";
}

