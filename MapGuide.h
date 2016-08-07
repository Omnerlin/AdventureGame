#pragma once
//#include <SFML\Graphics.hpp>
#include "Tile.h"
#include <vector>
class MapGuide
{
private:

public:
	std::vector<Tile> tiles;
	int length;
	int width;
	void setup(sf::Texture *texture, int tileWidth, int tileHeight);
	MapGuide();
	~MapGuide();
};

