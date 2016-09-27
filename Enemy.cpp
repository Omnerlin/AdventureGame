#include "Enemy.h"

void Enemy::attack()
{

}

void Enemy::update(sf::Time elapsed, const sf::Vector2f &playerPosition)
{
	if (recovering && recoveryClock.getElapsedTime().asSeconds() < hitRecoveryTime)
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

	gridPositionX = rect.getPosition().x / 32;
	gridPositionY = rect.getPosition().y / 32;

	if (active && !recovering && fireClock.getElapsedTime().asSeconds() > fireCooldown) {
		projectileManager.fire(sf::Vector2f(hitBox.getPosition().x + rect.getSize().x/2, hitBox.getPosition().y), playerPosition);
		fireClock.restart();
	}

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

	Projectile bullet;
	for (int i = 0; i < 5; i++)
	{
		projectileManager.projectiles.push_back(bullet);
	}
}


Enemy::~Enemy()
{
}
