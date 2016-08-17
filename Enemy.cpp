#include "Enemy.h"


void Enemy::attack()
{

}

void Enemy::update()
{
	hitRecoveryTime = recoveryClock.getElapsedTime();
	if (recovering && hitRecoveryTime.asSeconds() < 0.5)
	{
		rect.setFillColor(sf::Color(200, 0, 0, 255));
	}
	else
	{
		rect.setFillColor(sf::Color(255, 255, 255, 255));
		recovering = false;
	}

	hitBox.setPosition(rect.getPosition());
	hitBox.update();

	if (health <= 0)
	{
		health = 0;
		active = false;
	}
	
}

Enemy::Enemy()
{
	rect.setSize(sf::Vector2f(32, 32));
	hitBox.rect.setSize(rect.getSize());
}


Enemy::~Enemy()
{
}
