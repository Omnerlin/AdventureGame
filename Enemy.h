#pragma once
#include "Entity.h"
#include "HitBox.h"
#include "ProjectileManager.h"
#include "GridNode.h"

enum class ENEMYTYPES
{
	REGULAR_ENEMY,
	HONING_ENEMY
};

class Enemy : public Entity
{

private:
	


public:

	GridNode startNode;
	GridNode targetNode;
	std::vector<GridNode> currentPath;

	bool recovering = false;
	HitBox hitBox;
	ProjectileManager projectileManager;
	sf::Vector2i gridPosition;

	sf::Clock fireClock;
	float fireCooldown = 1; // in seconds

	sf::Clock recoveryClock;
	float hitRecoveryTime = 0.5; // in seconds
	bool active = true;
	int health = 3;
	float baseMoveSpeed = 0.05;

	void update(sf::Time elapsed, const sf::Vector2f &playerPosition);
	void attack();
	Enemy();
	~Enemy();
};

