#pragma once
#include "SFML\Graphics.hpp"

class GridNode : public sf::Transformable
{
private:
	

public:
	int gCost = 0;
	int hCost = 0;

	bool active = true;
	bool traversible = true;
	int getFCost();
	
	sf::Vector2i gridPosition;
	sf::CircleShape circle;

	bool operator ==(const GridNode &other) const;
	bool operator !=(const GridNode &other) const;

	GridNode(sf::Vector2f &position);
	GridNode();
	~GridNode();
	GridNode *parent;
};

