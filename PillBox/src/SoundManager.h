#pragma once
#include "Types.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "GLFW/glfw3.h"


namespace Pillbox
{
	class SoundManager
	{
	public:
		Engine& engine;
		SoundManager(Engine& anEng) : engine(anEng) {}
		void StartUp();
		void ShutDown();
		void PlaySoundKeyboard(int);
	private:
		SoLoud::Soloud soloud;
		SoLoud::Wav quack;
		SoLoud::Wav nuke;
		SoLoud::Wav ph;
		SoLoud::Wav death;
	};
}