#include "MazeManager.h"
#include "Engine.h"



using namespace Pillbox;



void MazeManager::StartUp()
{
	engine.graphics.LoadImageFile("visited.png", "images");
	engine.graphics.LoadImageFile("wall.png", "images");
	
	if (width % 2 == 0)
	{
		width += 1;
	}
	if (height % 2 == 0)
	{
		height += 1;
	}

	std::vector<std::vector<int>> v(width, std::vector<int>(height, unvisited));
	maze = v;
	
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{
			//other other row and column
			if (i % 2 == 1 || j % 2 == 1)
			{
				maze[i][j] = wall;
			}
			
			//if the bordeers of maze
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
			{
				maze[i][j] = visited;
			}
		}
	}
	
	std::cout << "\nBefore\n";
	PrintMaze();
	GenerateMaze(2, 2);

	std::cout << "\nfinal version\n";
	PrintMaze();
	MazeToScreen();
}


void MazeManager::GenerateMaze(int x, int y)
{
	
	maze[x][y] = visited;
	if (x == 1 && y == 1 && maze[x][y] == unvisited)
	{
		//stuff
	}
	

	int count = 0;
	//0 = up
	//1 = down
	//2 = left
	//3 = right
	int direction = rand() % 4;
	while (true)
	{
		//PrintMaze();
		if (direction == 0 && count < 4) //going up
		{
			if (maze[x][y - 2] == unvisited)
			{
				maze[x][y - 1] = visited;
				GenerateMaze(x, y - 2);
			}
			else
			{
				count += 1;
				direction += 1;
			}
		}

		if (direction == 1 && count < 4) //going down
		{
			if (maze[x][y + 2] == unvisited)
			{
				maze[x][y + 1] = visited;
				GenerateMaze(x, y + 2);
			}
			else
			{
				count += 1;
				direction += 1;
			}
		}

		if (direction == 2 && count < 4) //going left
		{
			if (maze[x - 2][y] == unvisited)
			{
				maze[x-1][y] = visited;
				GenerateMaze(x - 2, y);
			}
			else
			{
				count += 1;
				direction += 1;
			}
		}

		if (direction == 3 && count < 4) //going right
		{
			if (maze[x + 2][y] == unvisited)
			{
				maze[x + 1][y] = visited;
				GenerateMaze(x + 2, y);
			}
			else
			{
				count += 1;
				direction = 0;
			}
		}

		if (count >= 4)
		{
			return;
		}
	} //end of while
	
	




}

void MazeManager::PrintMaze()
{
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{
			std::cout << maze[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void MazeManager::MazeToScreen()
{
	std::cout << "inside of MazeToScreen\n";
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{
			EntityID id = engine.ecs.UnusedEntity();

			engine.ecs.Get<Transform>(id).position = vec3( i * 4,  j * 4,1);
			engine.ecs.Get<Transform>(id).rotation = vec3(0);
			engine.ecs.Get<Transform>(id).scale = vec3(10, 10, 10);
			std::cout << maze[i][j];
			if (maze[i][j] == visited)
			{
				engine.ecs.Get<Sprite>(id).name = "visited.png";
				engine.ecs.Get<Sprite>(id).z = 0.5f;
			}
			else if (maze[i][j] == wall)
			{
				engine.ecs.Get<Sprite>(id).name = "wall.png";
				engine.ecs.Get<Sprite>(id).z = 0.5f;
			}

		}
		std::cout << "\n";
	}

	std::cout << "\nthere are " << engine.ecs.UnusedEntity() << "entities\n";
}