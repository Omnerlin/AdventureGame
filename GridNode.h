#pragma once
#include "SFML\Graphics.hpp"

class GridNode : public sf::Transformable
{
private:
	bool active;
	bool traversible;

public:
	int gCost = 0;
	int hCost = 0;

	int getFCost();
	GridNode();
	GridNode(sf::Vector2f &position);
	sf::CircleShape circle;
	~GridNode();
};

