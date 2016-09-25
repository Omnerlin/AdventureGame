#pragma once
#include "Projectile.h"

class ProjectileManager
{
private:
	
public:
	std::vector<Projectile> projectiles;
	void fire(const sf::Vector2f &position1, const sf::Vector2f &position2);
	void updateActiveProjectiles(sf::Time elapsed);

	ProjectileManager();
	~ProjectileManager();
};

