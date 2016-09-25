#pragma once
#include <vector>
#include "GridNode.h"
class PathfindingGrid
{
private:
	

public:
	std::vector<std::vector<GridNode>> gridNodes; // Vector array of nodes for the grid
	PathfindingGrid();
	~PathfindingGrid();
};

