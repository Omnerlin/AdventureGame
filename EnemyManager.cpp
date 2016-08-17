#include "EnemyManager.h"


void EnemyManager::drawEnemies(sf::RenderWindow *window)
{
	for(int i = 0; i < enemyArray.size(); ++i)
	{
		if(enemyArray[i].active == true)
		window->draw(enemyArray[i].rect);
	}
	
}

void EnemyManager::updateEnemies()
{

	for (int i = 0; i < enemyArray.size(); ++i)
	{
		enemyArray[i].update();
	}
}

EnemyManager::EnemyManager()
{
	Enemy enemy;
	enemy.rect.setPosition(200, 400);
	enemyArray.push_back(enemy);
	enemy.rect.setPosition(400, 500);
	enemyArray.push_back(enemy);
}


EnemyManager::~EnemyManager()
{
}
