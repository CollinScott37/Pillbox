#include "EngineRef.h"

using namespace Pillbox;

EngineRef::EngineRef()
{
	engine = std::make_unique<Engine>();
}

EngineRef::~EngineRef()
{
	
}