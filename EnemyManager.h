#pragma once
#include "Enemy.h"
#include <vector>

class EnemyManager
{
private:

public:
	std::vector<Enemy> enemyArray;
	void drawEnemies(sf::RenderWindow *window);
	void updateEnemies(sf::Time elapsed, const sf::Vector2f &playerPosition);
	EnemyManager();
	~EnemyManager();
};

