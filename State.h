#pragma once
#include "SFML\Graphics.hpp"
#include "Gamestates.h"
#include <iostream>
class State
{
private:


public:
	GAMESTATE returnState = GAMESTATE::MENU;
	virtual void init(sf::RenderWindow *window) = 0;
	virtual GAMESTATE update(sf::RenderWindow *window, sf::Time elapsed) = 0;
	virtual void cleanup() = 0;
	State();
	virtual ~State() = 0;
};

