#include "MapManager.h"


void MapManager::loadMap(std::string fileName, sf::Texture *texture, float x, float y) {
	Map map;
	map.load(fileName, texture);
	map.setOrigin(x, y);
	map.rect.setPosition(map.getPosition().x + map.tileArray[0].getWidth()/2, map.getPosition().y + map.tileArray[0].getHeight()/2);
	map.rect.setSize(sf::Vector2f((map.tileArray[0].getWidth()*map.getWidth()) - map.tileArray[0].getWidth(), map.tileArray[0].getHeight()*map.getHeight() - map.tileArray[0].getWidth()));
	map.view.setCenter(sf::Vector2f((map.getWidth() * map.tileArray[0].getWidth()) / 2 + map.getPosition().x, (map.getHeight() * map.tileArray[0].getHeight() / 2 + map.getPosition().y)));
	map.view.setSize(1024, 576);
	map.drawAndCollisionRect.setPosition(map.getPosition().x - map.tileArray[0].getWidth()*4, map.getPosition().y - map.tileArray[0].getHeight()*4);
	map.drawAndCollisionRect.setSize(sf::Vector2f(map.view.getSize().x + map.tileArray[0].getWidth()*8, map.view.getSize().y + map.tileArray[0].getHeight()*8));
	mapArray.push_back(map);
}

void MapManager::addMap(Map map) {
	mapArray.push_back(map);
}

void MapManager::drawMapsLayerOne(sf::RenderWindow *window, bool debug) { 
	if (mapArray.size() < 1) { return; }
	for (int i = 0; i < mapArray.size(); i++) {
		if (mapArray[i].active)
		{
			for (int j = 0; j < mapArray[i].tileArray.size(); j++)
			{
				if (!debug)
				{
					window->draw(mapArray[i].tileArray[j].sprite);
				}
				else
				{
					window->draw(mapArray[i].tileArray[j].rect);
				}
			}
		}
	}
} 

void MapManager::drawMapsLayerTwo(sf::RenderWindow *window, bool debug) {
	if (mapArray.size() < 1) { return; }
	for (int i = 0; i < mapArray.size(); i++) {
		if (mapArray[i].active)
		{
			for (int j = 0; j < mapArray[i].tileArray2.size(); j++)
			{
				if (!debug)
				{
					if (mapArray[i].tileArray2[j].index != -1)
					{
						window->draw(mapArray[i].tileArray2[j].sprite);
					}
				}
				else
				{
					window->draw(mapArray[i].tileArray2[j].rect);
				}
			}
		}
	}
}

void MapManager::testMapPlayerCollisions(Player *player, int index) {
	
	for (int i = 0; i < mapArray.size(); i++) {
		if (mapArray[i].active){
			for (int j = 0; j < mapArray[i].tileArray.size(); j++) {
				if (mapArray[i].tileArray[j].collidable) {
					if (player->rect.getGlobalBounds().intersects(mapArray[i].tileArray[j].rect.getGlobalBounds())) {
						while (player->rect.getGlobalBounds().intersects(mapArray[i].tileArray[j].rect.getGlobalBounds())) {
							if (index == 1) {
								if (player->oldPositionX < player->rect.getPosition().x) {
									player->rect.setPosition(mapArray[i].tileArray[j].rect.getPosition().x - player->rect.getSize().x, player->rect.getPosition().y);
								}
								else if (player->oldPositionX > player->rect.getPosition().x) {
									player->rect.setPosition(mapArray[i].tileArray[j].rect.getPosition().x + player->rect.getSize().x, player->rect.getPosition().y);
								}
							}
							else if (index == 2)
							{
								if (player->oldPositionY < player->rect.getPosition().y) {
									player->rect.setPosition(player->rect.getPosition().x, mapArray[i].tileArray[j].rect.getPosition().y - player->rect.getSize().y);
								}
								else if (player->oldPositionY > player->rect.getPosition().y) {
									player->rect.setPosition(player->rect.getPosition().x, mapArray[i].tileArray[j].rect.getPosition().y + player->rect.getSize().y);
								}
							}

						}

					}
				}
			}
	}
	}
}

MapManager::MapManager()
{

}

MapManager::~MapManager()
{

}
