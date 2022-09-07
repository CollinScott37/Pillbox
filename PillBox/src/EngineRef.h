#pragma once
#include <memory>
#include "Types.h"
#include "Engine.h"

namespace Pillbox
{
	class EngineRef
	{
	public:
		EngineRef();
		~EngineRef();
		std::unique_ptr <Engine> engine;
	};
}
