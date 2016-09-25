#include "DoorSwitch.h"

void DoorSwitch::toggleState()
{
	if (state == BUTTON_STATE::UNPRESSED) {
		state = BUTTON_STATE::PRESSED;
		
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	}
	else {
		state = BUTTON_STATE::UNPRESSED;
		sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
	}
	toggleable = false;
	toggleClock.restart();
}

void DoorSwitch::updatePosition()
{
	hitbox.setPosition(getPosition());
	hitbox.update();
	rect.setPosition(getPosition());
	sprite.setPosition(getPosition());
}

bool DoorSwitch::getToggleable()
{
	if (toggleable || (!toggleable && toggleClock.getElapsedTime().asSeconds() >= toggleCooldown)){
		toggleable = true;
		return true;
	}
	else {
		return false;
	}
}

DoorSwitch::DoorSwitch()
{
	rect.setSize(sf::Vector2f(texture.getSize()));
	sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
	hitbox.rect.setSize(sf::Vector2f(32, 32));
}


DoorSwitch::~DoorSwitch()
{

}
