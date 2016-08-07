#pragma once
#include "Entity.h"
class ClickableButton : public Entity
{
private:


public:
	sf::Texture texture;
	bool pressed = false;
	bool mousedOver = false;
	bool released = false;
	bool active = true;
	void updateColor();
	void update(sf::RenderWindow *window);
	ClickableButton();
	~ClickableButton();
};

