#pragma once
#include "Entity.h"
#include "HitBox.h"

enum class BUTTON_STATE
{
	PRESSED,
	UNPRESSED
};

class DoorSwitch : public Entity, public sf::Transformable
{
private:
	sf::Clock toggleClock;
	bool toggleable = true;
	float toggleCooldown = 0.5; // In Seconds

public:
	sf::Texture texture;
	BUTTON_STATE state = BUTTON_STATE::UNPRESSED;
	bool interactable;
	HitBox hitbox;
	void toggleState();
	void updatePosition();
	bool getToggleable();

	DoorSwitch();
	~DoorSwitch();
};

