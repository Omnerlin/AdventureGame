#include "Map.h"

Map::Map()
{
	setPosition(sf::Vector2f(0, 0));
	Tile tile;
	for (int i = 0; i < width*height; i++) {
		
		tileArray.push_back(tile);
	}
	for (int i = 0; i < width*height; i++) {

		tileArray2.push_back(tile);
	}
	placeTiles();
	
}

void Map::load(std::string fileName, sf::Texture *texture)
{
	std::ifstream mapFile("levelMaps\\" + fileName);
	mapGuide.setup(texture, tileArray[0].getWidth(), tileArray[0].getHeight());

	mapFile >> width;
	mapFile >> height;
	mapFile >> depth;

	for (int i = 0; i < width*height; i++) {
		int index = 0;
		mapFile >> index;
		mapFile >> tileArray[i].collidable;
		tileArray[i].index = index;
		tileArray[i].sprite.setTexture(*texture);
		if (mapGuide.tiles[i].index != -1)
		{
			tileArray[i].sprite.setTextureRect(sf::IntRect(mapGuide.tiles[tileArray[i].index].rect.getPosition().x, mapGuide.tiles[tileArray[i].index].rect.getPosition().y, tileArray[i].getWidth(), tileArray[i].getHeight()));
		}
		else
		{
			tileArray[i].sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
		}
	}

	mapFile >> width;
	mapFile >> height;
	mapFile >> depth;

	for (int i = 0; i < width*height; i++) {
		int index = 0;
		mapFile >> index;
		tileArray2[i].index = index;
		tileArray2[i].sprite.setTexture(*texture);
		if (tileArray2[i].index != -1)
		{
			tileArray2[i].sprite.setTextureRect(sf::IntRect(mapGuide.tiles[tileArray2[i].index].rect.getPosition().x, mapGuide.tiles[tileArray2[i].index].rect.getPosition().y,tileArray2[i].getWidth(), tileArray2[i].getHeight()));
		}
		else
		{
			tileArray2[i].sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
		}
	}

	mapFile.close();
	placeTiles();
}

void Map::placeTiles()
{
	
	int row = 0;
	for (int i = 0, j = 0; i < tileArray.size(); i++, j++) {
		if (i % width == 0 && i > 0) {
			row++;
			j = 0;
		}
		tileArray[i].rect.setPosition((tileArray[i].getWidth() * j) + getPosition().x, (tileArray[i].getHeight() * row) + getPosition().y);
		tileArray[i].sprite.setPosition(tileArray[i].rect.getPosition());
		tileArray2[i].rect.setPosition((tileArray[i].getWidth() * j) + getPosition().x, (tileArray[i].getHeight() * row) + getPosition().y);
		tileArray2[i].sprite.setPosition(tileArray[i].rect.getPosition());
		//std::cout << "X: " << tileArray[i].rect.getPosition().x << "Y: " << tileArray[i].rect.getPosition().y << std::endl;
	}
}

int Map::getWidth() {
	return width;
}
int Map::getHeight() {
	return height;
}
void Map::setOrigin(float x, float y)
{
	setPosition(x, y);
	placeTiles();
}

Map::~Map()
{
	
}
