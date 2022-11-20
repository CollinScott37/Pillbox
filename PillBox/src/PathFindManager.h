#pragma once
#include "Types.h"

namespace Pillbox {

	typedef std::pair<int, vec2> Pair;

	class PathFind {
		public:
			vec2 * getPath();
			bool findPath(vec2 start);
			void setGoal(vec2 newGoal);

		private:
			Engine& engine;
			vec2 goal;
			std::vector<std::vector<bool>> visitedNodes;
			std::vector<std::vector<vec2>> parentList;
			std::vector<std::vector<int>> costList;
			std::vector<std::vector<int>> hList;
			std::vector<std::vector<int>> fList;
			std::stack<vec2> stack;

			void StartUp();
			int calculateManhattan(vec2 node);
			bool isValid(vec2 node);
			bool isGoal(vec2 node);
	};
}