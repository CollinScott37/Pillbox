#include "ResourceManager.h"
#include <filesystem>
#include "Engine.h"

//#include "soloud.h"
using namespace Pillbox;

void ResourceManager::StartUp()
{
	
}

void ResourceManager::ShutDown()
{

}

string ResourceManager::getPath(string path)
{
	string test = root.string() + path;
	std::cout << test << ": " << std::filesystem::is_regular_file(test) << "\n";

	return test;
}
