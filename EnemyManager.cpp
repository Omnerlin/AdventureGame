#include "EnemyManager.h"


void EnemyManager::drawEnemies(sf::RenderWindow *window)
{
	for(int i = 0; i < enemyArray.size(); ++i)
	{
		if(enemyArray[i].active == true)
		window->draw(enemyArray[i].rect);

		for (int j = 0; j < enemyArray[i].projectileManager.projectiles.size(); ++j) {
			if (enemyArray[i].projectileManager.projectiles[j].getActive() == true) {
				window->draw(enemyArray[i].projectileManager.projectiles[j].rect);
			}
		}
	}
}

void EnemyManager::updateEnemies(sf::Time elapsed, const sf::Vector2f &playerPosition)
{

	for (int i = 0; i < enemyArray.size(); ++i)
	{
		enemyArray[i].update(elapsed, playerPosition);
		enemyArray[i].projectileManager.updateActiveProjectiles(elapsed);
	}
}

EnemyManager::EnemyManager()
{
	
}


EnemyManager::~EnemyManager()
{

}
