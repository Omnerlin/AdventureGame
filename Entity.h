#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

class Entity
{
private:
	
public:
	sf::Sprite sprite;
	
	sf::RectangleShape rect;
	sf::Text text;

	Entity();
	~Entity();
};

