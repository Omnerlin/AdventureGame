#include "GridNode.h"

int GridNode::getFCost()
{
	return gCost + hCost;
}

bool GridNode::operator==(const GridNode & other) const
{
	return (this->getPosition() == other.getPosition());
}

bool GridNode::operator!=(const GridNode & other) const
{
	return !(*this == other);
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
	delete parent;
	circle.setPosition(position);
}


GridNode::~GridNode()
{

}
