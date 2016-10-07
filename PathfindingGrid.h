#pragma once
#include <vector>
#include "GridNode.h"
class PathfindingGrid
{
private:
	

public:
	std::vector<std::vector<GridNode>> gridNodes; // Vector array of nodes for the grid

	std::vector<GridNode> findPath(sf::Vector2i &startPosition, sf::Vector2i &endPosition);
	std::vector<GridNode> getNeighbors(GridNode &node);
	int getDistance(const GridNode &nodeA, const GridNode &nodeB);
	std::vector<GridNode> retracePath(GridNode &startNode, GridNode &endNode);

	PathfindingGrid();
	~PathfindingGrid();
};

