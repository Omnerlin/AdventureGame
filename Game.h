#pragma once
#include "State.h"
#include <iostream>
#include "MapManager.h"
#include "Player.h"
#include "Gamestates.h"

class Game : public State
{
private:
	bool drawRects = false;
	Player *player = new Player;
	MapManager mapManager;
	sf::Texture *groundTexture = new sf::Texture;
	sf::View currentview;
	sf::View gameView;
	sf::Clock debugClock;
	bool debug = false;
	GAMESTATE returnState = GAMESTATE::GAMELOOP;


public:
	void testDebugging();
	void updateViews(sf::RenderWindow *window);
	void init(sf::RenderWindow *window);
	GAMESTATE update(sf::RenderWindow *window, sf::Time elapsed);
	void updatePlayerMovement(Player *player, sf::Time elapsed);
	void updateActiveMaps();
	void cleanup();
	Game();
	~Game();
};

