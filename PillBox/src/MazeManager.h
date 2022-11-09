#pragma once
#include "Types.h"

namespace Pillbox
{
	class MazeManager
	{
	public:
		Engine& engine;
		MazeManager(Engine& anEng) : engine(anEng) {}
		void StartUp();
		void ShutDown() { }
	private:
		std::vector<std::vector<int>> maze;
		void GenerateMaze(int x, int y);
		void PrintMaze();
		void MazeToScreen();
 		//size of maze
		int seed = 50;
		int width = 20;
		int height = 20;

		const int wall = 0;
		const int unvisited = 1;
		const int visited = 2;

	};
}