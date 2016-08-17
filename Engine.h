#pragma once
#include "Game.h"
#include "Menu.h"
#include "Gamestates.h"


class Engine
{

private:
	int fps = 0;
	sf::RenderWindow *window = new sf::RenderWindow;
	//Game *game = new Game;
	State *state = new Menu;
	int SCREENWIDTH = 1024;
	int SCREENHEIGHT = 576;
	sf::Clock gameClock;
	GAMESTATE currentGamestate = GAMESTATE::MENU;


public:

	void switchStates(GAMESTATE state);
	void init();
	void update();
	void switchStates();
	Engine();
	~Engine();
};

