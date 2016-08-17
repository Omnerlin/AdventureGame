#pragma once
#include "Entity.h"
#include "HitBox.h"
#include <math.h>

enum class SWORDDIRECTION
{
	LEFT,
	RIGHT
};

class Sword : public Entity, public sf::Transformable
{

private:

public:
	HitBox hitBox;
	int damage = 1;
	//sf::RectangleShape hitBox;
	bool hitBoxActive = false;
	SWORDDIRECTION direction = SWORDDIRECTION::LEFT;
	float offset = 45;
	bool drawAnim = false;
	sf::Texture texture;
	sf::Texture animTexture;
	sf::Sprite animSprite;
	void update(sf::RenderWindow *window);
	Sword();
	~Sword();
};

