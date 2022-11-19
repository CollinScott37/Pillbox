#pragma once
#include "Types.h"

namespace Pillbox
{
	class MazeManager
	{
	public:
		Engine& engine;
		std::vector<std::vector<int>> maze;

		//size of maze
		int width = 70;
		int height = 40;

		MazeManager(Engine& anEng) : engine(anEng) {}
		void StartUp();
		void CreateMaze();
		
		void ShutDown() { }
		
		vec3 MazeIndexToWorldPos(int x, int y);
		vec3 MazeIndexToWorldPos(vec3 pos);

		vec3 CreateRandomValidMazeIndex(bool isStartIndex);

	private:
		void GenerateMazeFromPos(int x, int y);
		void PrintMaze();
		void MazeToScreen();

		int seed = 50;
		
		float xyscale = 5;

		const int wall = 0;
		const int unvisited = 1;
		const int visited = 2;

		bool alreadyCreatedMaze = false;

	};
}