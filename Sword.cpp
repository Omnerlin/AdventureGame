#include "Sword.h"


void Sword::update(sf::RenderWindow *window)
{

	rect.setPosition(getPosition());
	rect.setRotation(getRotation());
	sprite.setPosition(getPosition());
	sprite.setRotation(getRotation());
	//animSprite.setPosition(getPosition());

	animSprite.setRotation(getRotation() - 135);
	hitBox.setRotation(getRotation() + 45);
	hitBox.update();
	
	if (drawAnim)
	{
		window->draw(animSprite);
	}
	else
	{
		window->draw(sprite);
	}

	if (hitBoxActive == true)
	{
		window->draw(hitBox.rect);
	}
	

}

Sword::Sword()
{
	texture.loadFromFile("media\\swordSprite.png");
	animTexture.loadFromFile("media\\swordAnim.png");

	animSprite.setTexture(animTexture);
	animSprite.setTextureRect(sf::IntRect(0, 0, 32, 128));
	animSprite.setOrigin(48, 64);

	sprite.setTexture(texture);
	sprite.setOrigin(28, 28);
	sprite.setScale(-1, -1);

	
	hitBox.rect.setSize(sf::Vector2f(45, 128));
	hitBox.setOrigin(-16, 64);
	hitBox.rect.setOrigin(hitBox.getOrigin());
	hitBox.rect.setFillColor(sf::Color(255, 0, 0, 50));
	setPosition(0, 0);
}


Sword::~Sword()
{
}
