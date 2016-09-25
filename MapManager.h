#pragma once
#include "Map.h"
#include "Player.h"
#include "Projectile.h"
class MapManager
{
private:
	unsigned int width = 0;
	unsigned int height = 0;

public:
	unsigned int getWidth();
	unsigned int getHeight();

	void testMapPlayerCollisions(Player *player, int index);
	void testMapProjectileCollisions(Projectile &projectile);

	std::vector<Map> mapArray;
	void loadMap(std::string fileName, sf::Texture *texture, float x, float y, EnemyManager &enemyManager);
	void addMap(Map map);
	void drawMapsLayerOne(sf::RenderWindow *window, bool debug);
	void drawMapsLayerTwo(sf::RenderWindow *window, bool debug);//Draws the maps if they are active.
	MapManager();
	~MapManager();
};

