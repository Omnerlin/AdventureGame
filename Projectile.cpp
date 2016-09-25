#include "Projectile.h"



bool Projectile::getActive()
{
	if (active) {
		return true;
	}
	else {
		return false;
	}
}

int Projectile::getDamage()
{
	return damage;
}

sf::Vector2f Projectile::getSpeed()
{
	return m_speed;
}

void Projectile::setActive(bool boolio)
{
	active = boolio;
}

void Projectile::setSpeed(sf::Vector2f &speed)
{
	m_speed = speed;
}

Projectile::Projectile()
{
	rect.setSize(sf::Vector2f(15, 15));
	rect.setFillColor(sf::Color::Yellow);
}


Projectile::~Projectile()
{
}
