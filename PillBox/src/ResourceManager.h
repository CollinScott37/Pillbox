#pragma once
#include <fstream>
#include <filesystem>
#include "Types.h"


namespace Pillbox
{
	class ResourceManager
	{
	public:
		Engine& engine;
		ResourceManager(Engine& e) : engine(e) {}
		void StartUp();
		void ShutDown();
		string getPath(string);

	private:
		const std::filesystem::path root{ "assets/" };
	};
}