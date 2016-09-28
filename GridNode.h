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
	GridNode();
	GridNode(sf::Vector2f &position);
	sf::CircleShape circle;
	~GridNode();
};

