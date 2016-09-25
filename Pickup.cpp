#include "Pickup.h"



void Pickup::update()
{
	hitbox.setPosition(getPosition());
	hitbox.update();
}

Pickup::Pickup()
{
}


Pickup::~Pickup()
{
}
