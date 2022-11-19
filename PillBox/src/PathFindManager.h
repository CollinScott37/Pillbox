#pragma once
#include "Types.h"

namespace Pillbox {
	class PathFind {
		public:
			vec2 * getPath();
			void findPath(vec2 start);
			void setGoal(vec2 newGoal);

		private:
			Engine& engine;
			vec2 goal;
			std::vector<std::vector<bool>> visitedNodes;
			std::vector<std::vector<vec2>> parentList;
			std::stack<vec2> stack;

			void StartUp();
			int calculateManhattan(vec2 node);
	};
}