#include "HUD.h"



void HUD::update()
{
	backGroundRect.setSize(view.getSize());
}

void HUD::drawElements(sf::RenderWindow *window)
{
	window->draw(backGroundRect);
	window->draw(playerHealth);
	window->draw(enemiesKilled);

}

HUD::HUD()
{
	backGroundRect.setFillColor(sf::Color(0, 0, 0, 150));
	
}


HUD::~HUD()
{
}
