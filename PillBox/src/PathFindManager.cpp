#include "PathFindManager.h"
#include "Engine.h"
//#include <bits/stdc++.h>
using namespace Pillbox;

//resets important variables
void PathFind::StartUp()
{
	visitedNodes = std::vector<std::vector<bool>>(engine.maze.width, std::vector<bool>(engine.maze.height, false));
	parentList = std::vector<std::vector<vec2>>(engine.maze.width, std::vector<vec2>(engine.maze.height, vec2(-1, -1)));
	costList = std::vector<std::vector<int>>(engine.maze.width, std::vector<int>(engine.maze.height, INT_MAX));
	hList = std::vector<std::vector<int>>(engine.maze.width, std::vector<int>(engine.maze.height, INT_MAX));
	fList = std::vector<std::vector<int>>(engine.maze.width, std::vector<int>(engine.maze.height, INT_MAX));
	stack = std::stack<vec2>();

	//calculate all heuristics because it won't change ever
	for (int x = 0; x < hList.size(); x++) {
		for (int y = 0; y < hList[x].size(); y++) {
			hList[x][y] = calculateManhattan(vec2(x, y));
		}
	}
}

//used in findPath to calculate the heuristic
//only calculates for movement in 4 directions
int PathFind::calculateManhattan(vec2 node)
{
	int dx = abs(node.x - goal.x);
	int dy = abs(node.y - goal.y);
	return dx + dy; //<-- D * (dx + dy) where D is 1
}

//checks if a given node is outside of the maze, a wall, or valid
bool PathFind::isValid(vec2 node)
{
	//out of bounds node
	if (node.x < 0 || node.y < 0 || node.x >= engine.maze.width || node.y >= engine.maze.height) {
		return false;
	}

	//node is a wall
	if (engine.maze.maze[node.x][node.y] == 0) {
		return false;
	}

	return true;
}

//checks if the current node is the goal
bool Pillbox::PathFind::isGoal(vec2 node)
{
	if (node.x == goal.x && node.y == goal.y) {
		return true;
	}

	return false;
}

//set new goal for goose to find (available in lua)
void PathFind::setGoal(vec2 newGoal)
{
	goal = newGoal;
}

//use this to walk path from start to goal (returns array of indices to follow in order from start to goal) 
//do not use if findPath returns false (available in lua)
/*vec2**/std::stack<vec2> PathFind::getPath()
{
	stack = std::stack<vec2>();
	vec2 currNodeParent = parentList[goal.x][goal.y];

	stack.push(goal);

	while (currNodeParent.x >= 0 || currNodeParent.y >= 0) {
		stack.push(currNodeParent);
		currNodeParent = parentList[currNodeParent.x][currNodeParent.y];
	}

	/*vec2 path[costList[goal.x][goal.y]]; //vec2 path[stack.size()] = {};
	
	int i = 0;

	while (!stack.empty()) {
		path[i] = stack.top();
		stack.pop();
		i++;
	}

	return path;*/

	return stack;
}

//give the start point where goose will be (available in lua)
bool Pillbox::PathFind::findPath(vec2 start)
{
	StartUp();

	visitedNodes[start.x][start.y] = true;
	parentList[start.x][start.y] = vec2(-1, -1);
	
	//out of bounds start
	if (!isValid(start)) {
		return false;
	}

	//goal out of range
	if (!isValid(goal)) {
		return false;
	}

	//already at goal
	if (isGoal(start)) {
		return true;
	}

	costList[start.x][start.y] = 0;

	fList[start.x][start.y] = 0;

	std::map<int, vec2> openList;

	openList[0] = start;

	while (!openList.empty()) {
		auto poppedNode = *openList.begin();
		openList.erase(openList.begin());

		visitedNodes[poppedNode.x][poppedNode.y] = true;

		vec2 northNode = vec2(poppedNode.x - 1, poppedNode.y);

		//check north
		if (isValid(northNode)) {

			//north is goal
			if (isGoal(northNode)) {
				parentList[northNode.x][northNode.y] = vec2(poppedNode);
				costList[goal.x][goal.y] = costList[poppedNode.x][poppedNode.y] + 1;
				return true;
			}

			//node has not been visited yet
			else if (!visitedNodes[northNode.x][northNode.y]) {
				int newCost = costList[poppedNode.x][poppedNode.y] + 1;
				int newf = newCost + hList[northNode.x][northNode.y];

				//northNode's f (f = h + g) is larger than the new f;
				if (fList[northNode.x][northNode.y] == INT_MAX || fList[northNode.x][northNode.y] > newf) {
					fList[northNode.x][northNode.y] = newf;
					costList[northNode.x][northNode.y] = newCost;
					parentList[northNode.x][northNode.y] = vec2(poppedNode);

					openList[newf] = northNode;
				}
			}
		}

		vec2 southNode = vec2(poppedNode.x + 1, poppedNode.y);

		//check south
		if (isValid(southNode)) {

			//south is goal
			if (isGoal(southNode)) {
				parentList[southNode.x][southNode.y] = vec2(poppedNode);
				costList[goal.x][goal.y] = costList[poppedNode.x][poppedNode.y] + 1;
				return true;
			}

			//node has not been visited yet
			else if (!visitedNodes[southNode.x][southNode.y]) {
				int newCost = costList[poppedNode.x][poppedNode.y] + 1;
				int newf = newCost + hList[southNode.x][southNode.y];

				//southNode's f (f = h + g) is larger than the new f;
				if (fList[southNode.x][southNode.y] == INT_MAX || fList[southNode.x][southNode.y] > newf) {
					fList[southNode.x][southNode.y] = newf;
					costList[southNode.x][southNode.y] = newCost;
					parentList[southNode.x][southNode.y] = vec2(poppedNode);

					openList[newf] = southNode;
				}
			}
		}

		vec2 eastNode = vec2(poppedNode.x, poppedNode.y + 1);

		//check east
		if (isValid(eastNode)) {

			//east is goal
			if (isGoal(eastNode)) {
				parentList[eastNode.x][eastNode.y] = vec2(poppedNode);
				costList[goal.x][goal.y] = costList[poppedNode.x][poppedNode.y] + 1;
				return true;
			}

			//node has not been visited yet
			else if (!visitedNodes[eastNode.x][eastNode.y]) {
				int newCost = costList[poppedNode.x][poppedNode.y] + 1;
				int newf = newCost + hList[eastNode.x][eastNode.y];

				//eastNode's f (f = h + g) is larger than the new f;
				if (fList[eastNode.x][eastNode.y] == INT_MAX || fList[eastNode.x][eastNode.y] > newf) {
					fList[eastNode.x][eastNode.y] = newf;
					costList[eastNode.x][eastNode.y] = newCost;
					parentList[eastNode.x][eastNode.y] = vec2(poppedNode);

					openList[newf] = eastNode;
				}
			}
		}

		vec2 westNode = vec2(poppedNode.x, poppedNode.y - 1);

		//check west
		if (isValid(westNode)) {

			//west is goal
			if (isGoal(westNode)) {
				parentList[westNode.x][westNode.y] = vec2(poppedNode);
				costList[goal.x][goal.y] = costList[poppedNode.x][poppedNode.y] + 1;
				return true;
			}

			//node has not been visited yet
			else if (!visitedNodes[westNode.x][westNode.y]) {
				int newCost = costList[poppedNode.x][poppedNode.y] + 1;
				int newf = newCost + hList[westNode.x][westNode.y];

				//westNode's f (f = h + g) is larger than the new f;
				if (fList[westNode.x][westNode.y] == INT_MAX || fList[westNode.x][westNode.y] > newf) {
					fList[westNode.x][westNode.y] = newf;
					costList[westNode.x][westNode.y] = newCost;
					parentList[westNode.x][westNode.y] = vec2(poppedNode);

					openList[newf] = westNode;
				}
			}
		}
	}

	//if this line is reached, a path was not found
	return false;
}
