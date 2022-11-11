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
		void CreateMaze();
		
		void ShutDown() { }
		
		vec3 MazeIndexToWorldPos(int x, int y);
		vec3 MazeIndexToWorldPos(vec3 pos);

		vec3 CreateRandomValidMazeIndex(bool isStartIndex);
	private:
		std::vector<std::vector<int>> maze;
		
		void GenerateMazeFromPos(int x, int y);
		void PrintMaze();
		void MazeToScreen();
 		
		//size of maze
		int seed = 50;
		int width = 70;
		int height = 40;
		
		float xyscale = 5;

		const int wall = 0;
		const int unvisited = 1;
		const int visited = 2;

		bool alreadyCreatedMaze = false;

	};
}