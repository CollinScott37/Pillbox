#include "PathFindManager.h"
#include "Engine.h"

using namespace Pillbox;

//resets important variables
void Pillbox::PathFind::StartUp()
{
	visitedNodes = std::vector<std::vector<bool>>(engine.maze.width, std::vector<bool>(engine.maze.height, false));
	parentList = std::vector<std::vector<vec2>>(engine.maze.width, std::vector<vec2>(engine.maze.height, 0));
	stack = std::stack<vec2>();
}

//used in findPath to calculate the heuristic
int Pillbox::PathFind::calculateManhattan(vec2 node)
{
	int dx = abs(node.x - goal.x);
	int dy = abs(node.y - goal.y);
	return dx + dy; //D is 1
}

//set new goal for goose to find (available in lua)
void Pillbox::PathFind::setGoal(vec2 newGoal)
{
	goal = newGoal;
}

//use this to walk path from start to goal (returns array of indices to follow in order) (available in lua)
vec2 * Pillbox::PathFind::getPath()
{
	stack = std::stack<vec2>();
	vec2 currNodeParent = parentList[goal.x][goal.y];

	while (currNodeParent.x >= 0 || currNodeParent.y >= 0) {
		stack.push(currNodeParent);
		currNodeParent = parentList[currNodeParent.x][currNodeParent.y];
	}

	vec2 path[stack.size()] = {};
	int i = 0;

	while (!stack.empty()) {
		path[i] = stack.pop();
		i++;
	}

	return path;
}

//give the start point where goose will be (available in lua)
void Pillbox::PathFind::findPath(vec2 start)
{
	StartUp();

	visitedNodes[start.x][start.y] = true;
	parentList[start.x][start.y] = vec2(-1, -1);
	//TODO finish a* path finding
}
