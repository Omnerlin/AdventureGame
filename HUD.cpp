#include "HUD.h"



void HUD::update(int health)
{
	backGroundRect.setSize(sf::Vector2f(view.getSize().x, view.getSize().y/8));
	playerHealth.setPosition(0, 5);
	playerHealth.setString("Health: " + std::to_string(health));
}

void HUD::drawElements(sf::RenderWindow *window)
{
	window->draw(backGroundRect);
	window->draw(playerHealth);
	window->draw(enemiesKilled);
}

HUD::HUD()
{
	backGroundRect.setFillColor(sf::Color(0, 0, 0, 75));
	hudFont.loadFromFile("fonts\\computerFont.ttf");
	playerHealth.setFont(hudFont);
	playerHealth.setCharacterSize(50);
}


HUD::~HUD()
{
}
