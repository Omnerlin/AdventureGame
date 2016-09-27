#include "GridNode.h"

int GridNode::getFCost()
{
	return gCost + hCost;
}

GridNode::GridNode()
{
	setPosition(0, 0);
	circle.setRadius(5);
	circle.setPosition(0, 0);
}

GridNode::GridNode(sf::Vector2f &position)
{
	setPosition(position);
	circle.setPosition(position);
}


GridNode::~GridNode()
{

}
