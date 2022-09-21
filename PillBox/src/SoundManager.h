#pragma once
#include "Types.h"
#include "soloud.h"
#include "soloud_wav.h"
//#include "GLFW/glfw3.h"


namespace Pillbox
{
	class SoundManager
	{
	public:
		Engine& engine;
		SoundManager(Engine& anEng) : engine(anEng) {}
		void StartUp();
		void ShutDown();
		void PlaySound(string);
		bool LoadSound( const string& name, const string& path );
	private:
		
		SoLoud::Soloud soloud;
		std::unordered_map< string, SoLoud::Wav > sounds;

	};
}