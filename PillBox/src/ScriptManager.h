#pragma once
#include "Types.h"
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>


namespace Pillbox
{

	class ScriptManager
	{
	public:
		Engine& engine;
		ScriptManager(Engine& anEng) : engine(anEng) {}
		void StartUp();
		bool LoadScript(const string& name, const string& path);
		void Update();
	private:
		sol::state lua;
		std::unordered_map< string, sol::load_result > scripts;
	};
}
