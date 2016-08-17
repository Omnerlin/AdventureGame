#pragma once
#include "Entity.h"
#include "HitBox.h"


class Enemy : public Entity
{

private:
	


public:
	bool recovering = false;
	HitBox hitBox;
	sf::Clock recoveryClock;
	sf::Time hitRecoveryTime;
	bool active = true;
	int health = 1;
	void update();
	void attack();
	Enemy();
	~Enemy();
};

