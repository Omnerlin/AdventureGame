#pragma once
#include "Entity.h"

enum class PROJECTILE_TYPES
{
	NORMAL,
	HOMING
};

class Projectile : public Entity, public sf::Transformable
{
private:
	sf::Vector2f m_speed;
	bool active = false;
	float lifetime = 5.0;
	int damage = 20;

public:
	float baseMoveSpeed = 0.05;
	float timeStamp = 0.0;
	bool getActive();
	int getDamage();
	sf::Vector2f getSpeed();
	void setActive(bool boolio);
	void setSpeed(sf::Vector2f &speed);
	sf::Vector2f direction;
	Projectile();
	~Projectile();
};

