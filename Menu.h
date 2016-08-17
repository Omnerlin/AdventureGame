#pragma once
#include "State.h"
#include "ClickableButton.h"

class Menu : public State
{

private:
	float titleTextTimeStamp;

	ClickableButton startButton;
	ClickableButton quitButton;
	sf::Font font;
	sf::Text titleText;
	double originalTitleYPos;
	sf::Time elapsed;
	sf::RectangleShape background;

public:

	void updateTitleText(sf::Time elapsed);
	GAMESTATE returnState = GAMESTATE::MENU;
	void init(sf::RenderWindow *window);
	GAMESTATE update(sf::RenderWindow *window, sf::Time elapsed);
	void updateBackgroundColor(sf::Time elapsed);
	void cleanup();
	Menu();
	~Menu();
};

