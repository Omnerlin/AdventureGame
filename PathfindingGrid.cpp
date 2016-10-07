#include "PathfindingGrid.h"
#include <iostream>
#include <algorithm>


std::vector<GridNode> PathfindingGrid::findPath( sf::Vector2i & startPosition,  sf::Vector2i & endPosition)
{
	GridNode startNode = gridNodes[startPosition.x][startPosition.y];
	GridNode targetNode = gridNodes[endPosition.x][endPosition.y];

	std::vector<GridNode> openSet;
	std::vector<GridNode> closedSet;
	std::vector<GridNode> path;
	openSet.push_back(startNode);
	//std::vector<GridNode>::const_iterator iter;
	
	while (openSet.size() > 0) {
		GridNode currentNode = openSet[0];
		int counter = 0;
		for (counter = 0; counter < openSet.size(); ++counter) {
			if (openSet[counter].getFCost() < currentNode.getFCost() || openSet[counter].getFCost() == currentNode.getFCost() && openSet[counter].hCost < currentNode.hCost) {
				currentNode = openSet[counter];
			}
		}

		closedSet.push_back(currentNode);
		std::cout << openSet.size() << std::endl;
		openSet.erase(openSet.begin() + 0);

		if (currentNode == targetNode) {
			return retracePath(startNode, targetNode);
		}

		std::vector<GridNode> neighbors = getNeighbors(currentNode);
		for (int i = 0; i < neighbors.size(); i++) {
			if (!neighbors[i].traversible || (std::find(neighbors.begin(), neighbors.end(), currentNode) != neighbors.end())) {
				continue;
			}
			int newMovementCostToNeighbor = currentNode.gCost + getDistance(currentNode, neighbors[i]);
			if (newMovementCostToNeighbor < neighbors[i].gCost || (std::find(openSet.begin(), openSet.end(), neighbors[i]) != openSet.end())) {
				neighbors[i].gCost = newMovementCostToNeighbor;
				neighbors[i].hCost = getDistance(neighbors[i], targetNode);
				*neighbors[i].parent = currentNode;

				if (std::find(openSet.begin(), openSet.end(), neighbors[i]) != openSet.end()) {}
				else {
					openSet.push_back(neighbors[i]);
				}
			}
		}

		
	}
}

std::vector<GridNode> PathfindingGrid::getNeighbors(GridNode & node)
{
	std::vector<GridNode> neighbors;
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0)
				continue;
			
			int checkX = node.gridPosition.x;
			int checkY = node.gridPosition.y;

			if (checkX >= 0 && checkX < gridNodes.size() && checkY >= 0 && checkY < gridNodes[0].size()) {
				neighbors.push_back(gridNodes[checkX][checkY]);
			}
		}
	}


	return neighbors;
}

int PathfindingGrid::getDistance(const GridNode & nodeA, const GridNode & nodeB)
{
	int distanceX = abs(nodeA.gridPosition.x - nodeB.gridPosition.x);
	int distanceY = abs(nodeA.gridPosition.y - nodeB.gridPosition.y);

	if (distanceX > distanceY) {
		return 14 * distanceY + 10 * (distanceX - distanceY);
	}
	return 14 * distanceY + 10 * (distanceY - distanceX);
}

std::vector<GridNode> PathfindingGrid::retracePath(GridNode & startNode, GridNode & endNode)
{
	std::vector<GridNode> path;
	GridNode currentNode = endNode;

	while (currentNode != startNode) {
		path.push_back(currentNode);
		currentNode = *currentNode.parent;
	}

	std::reverse(path.begin(), path.end());
	return path;
}

PathfindingGrid::PathfindingGrid()
{
}


PathfindingGrid::~PathfindingGrid()
{
}
