#include "ECS.h"

using namespace Pillbox;

EntityID ECS::UnusedEntity()
{
	EntityID newId = nextAvailableID;
	nextAvailableID += 1;
	return newId;
}









