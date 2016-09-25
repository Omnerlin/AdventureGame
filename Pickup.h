#pragma once
#include "Entity.h"
#include "HitBox.h"

enum class PICKUP_TYPES
{
	HEALTH,
	RESOURCE
};

class Pickup : public Entity, public sf::Transformable
{
private:

public:
	HitBox hitbox;
	PICKUP_TYPES pickupType;
	bool active = true;
	void update();

	Pickup();
	~Pickup();
};

