#include "SoundManager.h"
#include "Engine.h"

using namespace Pillbox;

void SoundManager::StartUp()
{
	soloud.init();

	//quack.load(engine.resources.getPath("sounds/quack.wav").c_str());
	//nuke.load(engine.resources.getPath("sounds/nuke.wav").c_str());
	//ph.load(engine.resources.getPath("sounds/ph.wav").c_str());
	//death.load(engine.resources.getPath("sounds/death.wav").c_str());
}

void SoundManager::PlaySound(string name, float vol)
{
	if (sounds.count(name) != 0)
	{
		auto handle = soloud.play(sounds[name]);
		soloud.setVolume(handle, vol);
	}
	
	
}

bool SoundManager::LoadSound( const string& name, const string& path )
{
	string p = path + "/" + name;

	if (sounds.count(name) == 0)
	{
		sounds[name].load(engine.resources.getPath(p).c_str());
		return true;
	}
	else
	{
		return false;
	}
	
}

void SoundManager::ShutDown()
{
	soloud.deinit();
}