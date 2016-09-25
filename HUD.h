#pragma once
#include "SFML\Graphics.hpp"
class HUD
{
private:
	sf::Font hudFont;
	sf::Text playerHealth;
	sf::Text enemiesKilled;
	sf::RectangleShape backGroundRect;
	sf::Texture backGroundTexture;

public:
	sf::View view;
	void update(int playerHealth);
	void drawElements(sf::RenderWindow * window);
	HUD();
	~HUD();
};

