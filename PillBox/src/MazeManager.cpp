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
	
	CreateMaze();
}

void MazeManager::CreateMaze()
{
	if (!alreadyCreatedMaze)
	{
		srand(50);
		std::vector<std::vector<int>> v(width, std::vector<int>(height, unvisited));
		maze = v;
	}


	srand(time(NULL));
	//rand();

	bool normalBlock = false;
	for (int j = 0; j < height; j += 1)
	{
		for (int i = 0; i < width; i += 1)
		{
			//other other row and column
			if (i % 2 == 1 || j % 2 == 1)
			{
				maze[i][j] = wall;
				normalBlock = true;
			}

			if (i == 0 || j == 0 || i == width - 1 || j == height - 1) //if the borders of maze
			{
				maze[i][j] = visited;
				normalBlock = true;
			}

			if (!normalBlock)
			{
				maze[i][j] = unvisited;
			}
			normalBlock = false;

		}
	}

	//std::cout << "\nBefore\n";
	//PrintMaze();
	int startx = 2;
	int starty = 2;
	vec2 startIndex = CreateRandomValidMazeIndex(true);
	//std::cout << "at: " << startIndex.x << ", " << startIndex.y << "\n";
	GenerateMazeFromPos(startIndex.x, startIndex.y);

	std::cout << "\nfinal version\n";
	PrintMaze();

	MazeToScreen();
}

vec3 MazeManager::MazeIndexToWorldPosVec3(vec3 pos)
{
	return MazeIndexToWorldPos(pos.x, pos.y);
}

vec3 MazeManager::MazeIndexToWorldPosVec2(vec2 pos)
{
	return MazeIndexToWorldPos(pos.x, pos.y);
}

vec3 MazeManager::MazeIndexToWorldPos(int i, int j)
{
	float x = (i - (width / (2))) * xyscale;
	float y = (j - (height / (2))) * xyscale;

	return vec3(x, -y, 0);
}

vec2 MazeManager::WorldPosToMazeIndex(vec3 pos)
{
	int i = (pos.x / xyscale) + (width/2);
	int j = (-pos.y / xyscale) + (height/2);
	
	return vec2(i,j);
}

vec3 MazeManager::CreateRandomValidMazeIndex(bool isStartIndex)
{
	int i = -1;
	int j = -1;

	while (true)
	{
		if (isStartIndex)
		{
			i = (rand() % (width - 4)) + 2;
			j = (rand() % (height - 4)) + 2;
			//std::cout << "AAA: " << i << ", " << j << "\n";
			if (i % 2 == 0 && j % 2 == 0)
			{
				return vec3(i, j, 0);
			}
		}
		else
		{
			i = (rand() % (width - 4)) + 2;
			j = (rand() % (height - 4)) + 2;
			//std::cout << "BBB: " << i << ", " << j << "\n";
			if (maze[i][j] == visited)
			{
				return vec3(i, j, 0);
			}
		}

	}


}

void MazeManager::GenerateMazeFromPos(int x, int y)
{
	
	maze[x][y] = visited;

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
				GenerateMazeFromPos(x, y - 2);
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
				GenerateMazeFromPos(x, y + 2);
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
				GenerateMazeFromPos(x - 2, y);
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
				GenerateMazeFromPos(x + 2, y);
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
	for (int j = 0; j < height; j += 1)
	{
		for (int i = 0; i < width; i += 1)
		{
			if (maze[i][j] == wall)
			{
				std::cout << "#";
			}
			else
			{
				std::cout << " ";
			}
			
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void MazeManager::MazeToScreen()
{
	//std::cout << "inside of MazeToScreen\n";
	for (int j = 0; j < height; j += 1)
	{
		for (int i = 0; i < width; i += 1)
		{
			EntityID id = 0; //placeHolder
			if (!alreadyCreatedMaze)
			{
				 id = engine.ecs.UnusedEntity();
			}
			else
			{
				id = (i * height) + j;
			}
			
			
			
			//float x =  (i - (width / (2))) * xyscale;
			//float y = (j - (height / (2))) * xyscale;
			
			engine.ecs.Get<Transform>(id).position = MazeIndexToWorldPos(i,j);//vec3((j - width/2) + height/2, -((i + height/2) + width/2),1);
			engine.ecs.Get<Transform>(id).rotation = vec3(0);
			engine.ecs.Get<Transform>(id).scale = vec3(1, 1, 1) * (xyscale/2);
			
			if (maze[i][j] == visited)
			{
				engine.ecs.Get<Sprite>(id).name = "visited.png";
				engine.ecs.Get<Sprite>(id).z = 0.9f;
			}
			else if (maze[i][j] == wall)
			{
				engine.ecs.Get<Sprite>(id).name = "wall.png";
				engine.ecs.Get<Sprite>(id).z = 0.9f;
			}

		}
	}

	alreadyCreatedMaze = true;

	//std::cout << "\nthere are " << engine.ecs.UnusedEntity() << "entities\n";
}