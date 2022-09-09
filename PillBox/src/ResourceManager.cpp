#include "ResourceManager.h"
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
	return test;
}
