#pragma once
#include "Map.h"
#include "Player.h"
class MapManager
{
private:
	

public:
	void testMapPlayerCollisions(Player *player, int index);
	std::vector<Map> mapArray;
	void loadMap(std::string fileName, sf::Texture *texture, float x, float y);
	void addMap(Map map);
	void drawMapsLayerOne(sf::RenderWindow *window, bool debug);
	void drawMapsLayerTwo(sf::RenderWindow *window, bool debug);//Draws the maps if they are active.
	MapManager();
	~MapManager();
};

