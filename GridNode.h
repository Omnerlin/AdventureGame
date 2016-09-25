#pragma once
#include "SFML\Graphics.hpp"

class GridNode : public sf::Transformable
{
private:
	bool active;

public:
	GridNode(sf::Vector2f &position);
	~GridNode();
};

