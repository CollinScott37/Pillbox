#include "SoundManager.h"
#include "Engine.h"

using namespace Pillbox;

void SoundManager::StartUp()
{
	soloud.init();

	quack.load( engine.resources.getPath("sounds/quack.wav").c_str());
	nuke.load(engine.resources.getPath("sounds/nuke.wav").c_str());
	ph.load(engine.resources.getPath("sounds/ph.wav").c_str());
	death.load(engine.resources.getPath("sounds/death.wav").c_str());
}

void SoundManager::PlaySoundKeyboard(int keycode)
{
	if (keycode == GLFW_KEY_Q)
	{
		soloud.play(quack);
	}
	else if (keycode == GLFW_KEY_N)
	{
		soloud.play(nuke);
	}
	else if (keycode == GLFW_KEY_P)
	{
		soloud.play(ph);
	}
	else if (keycode == GLFW_KEY_R)
	{
		soloud.play(death);
	}
	
}

void SoundManager::ShutDown()
{
	soloud.deinit();
}