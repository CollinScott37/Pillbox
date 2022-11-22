#pragma once
#include "Types.h"
//#include "Pair.h"

namespace Pillbox {

	//typedef std::pair<int, vec2> Pair;

	class PathFind {
		public:
			bool findPath(vec2 start);
			void setGoal(vec2 newGoal);
			PathFind(Engine& anEng) : engine(anEng) {}
			std::stack<vec2> getPath();
			void StartUp();

		private:
			Engine& engine;
			vec2 goal;
			std::vector<std::vector<bool>> visitedNodes;
			std::vector<std::vector<vec2>> parentList;
			std::vector<std::vector<int>> costList;
			std::vector<std::vector<int>> hList;
			std::vector<std::vector<int>> fList;
			std::stack<vec2> stack;

			/*struct compare {
				bool operator()(const Pair& a, const Pair& b) {
					if (a.first < b.first) {
						return true;
					}
					return false;
				}
			};*/
			
			int calculateManhattan(vec2 node);
			bool isValid(vec2 node);
			bool isGoal(vec2 node);
	}; 
}