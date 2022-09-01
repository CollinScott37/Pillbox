#pragma once
#include "Types.h"

namespace Pillbox
{
	class GraphicsManager
	{
	public:
		//GraphicsManager() = default; //constructor?
		void StartUp();
		void ShutDown();
		void Draw();
	};
}