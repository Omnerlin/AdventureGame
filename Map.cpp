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

void Map::load(std::string fileName, sf::Texture *texture, EnemyManager &enemyManager)
{
	std::ifstream mapFile("levelMaps\\" + fileName);
	mapGuide.setup(texture, tileArray[0].getWidth(), tileArray[0].getHeight());
	mapTexture = *texture;

	mapFile >> width;
	mapFile >> height;
	mapFile >> depth;

	for (int i = 0; i < width*height; i++) {
		int index = 0;
		mapFile >> index;
		mapFile >> tileArray[i].collidable;
		tileArray[i].index = index;
		tileArray[i].sprite.setTexture(*texture);
		if (tileArray[i].index != -1)
		{
			tileArray[i].sprite.setTextureRect(sf::IntRect(mapGuide.tiles[tileArray[i].index].rect.getPosition().x, mapGuide.tiles[tileArray[i].index].rect.getPosition().y, tileArray[i].getWidth(), tileArray[i].getHeight()));
		}
		else
		{
			tileArray[i].sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
		}
	}

	tileSetLayerOne.setPrimitiveType(sf::Quads);
	tileSetLayerOne.resize(width*height * 4);
	//tileSetLayerTwo.setPrimitiveType(sf::Quads);
	//tileSetLayerTwo.resize(width*height * 4);

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

	Enemy enemy;
	int enemyCount = 0;
	mapFile >> enemyCount;
	if (enemyCount > 0) {
		for (int i = 0; i < enemyCount; i++) {
			sf::Vector2f position;
			mapFile >> position.x;
			mapFile >> position.y;
			enemy.rect.setPosition(position.x + getPosition().x, position.y + getPosition().y);
			enemyManager.enemyArray.push_back(enemy);
		}
	}
	mapFile.close();

	// Create Vertex Arrays (layer 1)
	for (int i = 0; i < width; i++) {
		for (int k = 0; k < height; k++)
		{

			int tileIndex = tileArray[i + k * width].index;

			sf::Vertex* quad = &tileSetLayerOne[(i + k * width) * 4];

			quad[0].position = sf::Vector2f(i * tileArray[i].getWidth(), k * tileArray[i].getHeight());
			quad[1].position = sf::Vector2f((i + 1) * tileArray[i].getWidth(), k * tileArray[i].getHeight());
			quad[2].position = sf::Vector2f((i + 1) * tileArray[i].getWidth(), (k + 1) * tileArray[i].getHeight());
			quad[3].position = sf::Vector2f(i * tileArray[i].getWidth(), (k + 1) * tileArray[i].getHeight());

			if (tileIndex != -1) {
				quad[0].texCoords = mapGuide.tiles[tileIndex].rect.getPosition();
				quad[1].texCoords = sf::Vector2f(mapGuide.tiles[tileIndex].rect.getPosition().x + mapGuide.tiles[tileIndex].rect.getSize().x, mapGuide.tiles[tileIndex].rect.getPosition().y);
				quad[2].texCoords = sf::Vector2f(mapGuide.tiles[tileIndex].rect.getPosition().x + mapGuide.tiles[tileIndex].rect.getSize().x, mapGuide.tiles[tileIndex].rect.getPosition().y + mapGuide.tiles[tileIndex].rect.getSize().y);
				quad[3].texCoords = sf::Vector2f(mapGuide.tiles[tileIndex].rect.getPosition().x, mapGuide.tiles[tileIndex].rect.getPosition().y + mapGuide.tiles[tileIndex].getHeight());
			}
			else
			{
				quad[0].texCoords = sf::Vector2f(0, 0);
				quad[1].texCoords = sf::Vector2f(0, 0);
				quad[2].texCoords = sf::Vector2f(0, 0);
				quad[3].texCoords = sf::Vector2f(0, 0);
			}
		}
	}

	// Layer 2

	/*for (int i = 0; i < width; i++) {
		for (int k = 0; k < height; k++)
		{

			int tileIndex = tileArray2[i + k * width].index;

			sf::Vertex* quad = &tileSetLayerTwo[(i + k * width) * 4];
			
			if (tileIndex != -1) {
			quad[0].position = sf::Vector2f(i * tileArray2[i].getWidth(), k * tileArray2[i].getHeight());
			quad[1].position = sf::Vector2f((i + 1) * tileArray2[i].getWidth(), k * tileArray2[i].getHeight());
			quad[2].position = sf::Vector2f((i + 1) * tileArray2[i].getWidth(), (k + 1) * tileArray2[i].getHeight());
			quad[3].position = sf::Vector2f(i * tileArray2[i].getWidth(), (k + 1) * tileArray2[i].getHeight());

			
			quad[0].texCoords = mapGuide.tiles[tileIndex].rect.getPosition();
			quad[1].texCoords = sf::Vector2f(mapGuide.tiles[tileIndex].rect.getPosition().x + mapGuide.tiles[tileIndex].rect.getSize().x, mapGuide.tiles[tileIndex].rect.getPosition().y);
			quad[2].texCoords = sf::Vector2f(mapGuide.tiles[tileIndex].rect.getPosition().x + mapGuide.tiles[tileIndex].rect.getSize().x, mapGuide.tiles[tileIndex].rect.getPosition().y + mapGuide.tiles[tileIndex].rect.getSize().y);
			quad[3].texCoords = sf::Vector2f(mapGuide.tiles[tileIndex].rect.getPosition().x, mapGuide.tiles[tileIndex].rect.getPosition().y + mapGuide.tiles[tileIndex].getHeight());
			}
			else
			{
				quad[0].position = sf::Vector2f(0,0);
				quad[1].position = sf::Vector2f(0, 0);
				quad[2].position = sf::Vector2f(0, 0);
				quad[3].position = sf::Vector2f(0, 0);

				quad[0].texCoords = sf::Vector2f(-1, 0);
				quad[1].texCoords = sf::Vector2f(-1, 0);
				quad[2].texCoords = sf::Vector2f(-1, 0);
				quad[3].texCoords = sf::Vector2f(-1, 0);
			}
		}
	}*/

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
