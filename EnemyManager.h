#pragma once
#include "Enemy.h"
#include <vector>

class EnemyManager
{
private:

public:
	std::vector<Enemy> enemyArray;
	void drawEnemies(sf::RenderWindow *window);
	void updateEnemies();
	EnemyManager();
	~EnemyManager();
};

