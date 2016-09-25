#pragma once
#include "Entity.h"
#include "HitBox.h"
#include "ProjectileManager.h"

enum class ENEMYTYPES
{
	REGULAR_ENEMY,
	HONING_ENEMY
};

class Enemy : public Entity
{

private:
	


public:
	bool recovering = false;
	HitBox hitBox;
	ProjectileManager projectileManager;

	sf::Clock fireClock;
	float fireCooldown = 2; // in seconds

	sf::Clock recoveryClock;
	float hitRecoveryTime = 0.5; // in seconds
	bool active = true;
	int health = 3;

	void update(sf::Time elapsed, const sf::Vector2f &playerPosition);
	void attack();
	Enemy();
	~Enemy();
};

