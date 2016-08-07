#pragma once
#include "MapGuide.h"
#include <vector>
#include "Tile.h"
#include <string>

class Map : public sf::Transformable
{
private:
	
	
	int width = 32;
	int height = 18;
	int depth;

	void placeTiles();
	

public:

	MapGuide mapGuide;
	std::vector<Tile> tileArray;
	std::vector<Tile> tileArray2;
	sf::View view;
	void load(std::string fileName, sf::Texture *texture);
	void setOrigin(float x, float y);
	sf::RectangleShape rect;
	sf::RectangleShape drawAndCollisionRect;
	bool active = false;
	int getWidth();
	int getHeight();
	
	Map();
	~Map();
};

