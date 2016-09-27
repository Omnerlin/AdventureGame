#include "ProjectileManager.h"
#include <math.h>


void ProjectileManager::fire(const sf::Vector2f &position1, const sf::Vector2f &position2)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].getActive() == false) {
			projectiles[i].setPosition(position1);
			float positionCompareX = position2.x - position1.x;
			float positionCompareY = position2.y - position1.y;
			float radian = std::atan2f(positionCompareY, positionCompareX);
			projectiles[i].direction = sf::Vector2f(cosf(radian), sinf(radian));
			//std::cout << "Projectile Fired." << std::endl;
			//std::cout << projectiles[i].direction.x << " " << projectiles[i].direction.y << std::endl;
			projectiles[i].setActive(true);
			break;
		}
	}
}

void ProjectileManager::updateActiveProjectiles(sf::Time elapsed)
{
	for (int i = 0; i < projectiles.size(); i++) {
		float deltaTime = elapsed.asMilliseconds() - projectiles[i].timeStamp;
		if (projectiles[i].getActive() == true)
		{
			
			projectiles[i].setSpeed(sf::Vector2f(deltaTime * projectiles[i].baseMoveSpeed * projectiles[i].direction.x,
				deltaTime * projectiles[i].baseMoveSpeed * projectiles[i].direction.y));

			projectiles[i].move(projectiles[i].getSpeed().x, projectiles[i].getSpeed().y);

			projectiles[i].rect.setPosition(projectiles[i].getPosition());

			projectiles[i].gridPosition.x = projectiles[i].getPosition().x / 32;
			projectiles[i].gridPosition.y = projectiles[i].getPosition().y / 32;

		}
		projectiles[i].timeStamp = elapsed.asMilliseconds();
	}
}

ProjectileManager::ProjectileManager()
{

}


ProjectileManager::~ProjectileManager()
{
}
