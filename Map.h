#pragma once
#include "MapGuide.h"
#include <vector>
#include "Tile.h"
#include <string>
#include "EnemyManager.h"

class Map : public sf::Transformable, public sf::Drawable
{
private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &mapTexture;
		target.draw(tileSetLayerOne, states);
		target.draw(tileSetLayerTwo, states);

	}
	
	int width = 32;
	int height = 18;
	int depth;

	void placeTiles();
	

public:

	sf::Vector2i origin;
	MapGuide mapGuide;
	std::vector<Tile> tileArray;
	std::vector<Tile> tileArray2;
	sf::View view;
	void load(std::string fileName, sf::Texture *texture, EnemyManager &enemyManager);
	void setOrigin(float x, float y);
	sf::RectangleShape rect;
	sf::RectangleShape drawAndCollisionRect;

	sf::VertexArray tileSetLayerOne;
	sf::VertexArray tileSetLayerTwo;

	sf::Texture mapTexture;

	bool active = false;
	int getWidth();
	int getHeight();
	
	Map();
	~Map();
};

