#pragma once
#include "State.h"
#include <iostream>
#include "MapManager.h"
#include "Player.h"
#include "Gamestates.h"
#include "EnemyManager.h"
#include "HUD.h"
class Game : public State
{
private:

	float viewTimeStamp;
	bool drawRects = false;
	Player *player = new Player;
	EnemyManager enemyManager;
	MapManager mapManager;
	sf::Texture *groundTexture = new sf::Texture;
	sf::View currentview;
	sf::View gameView;
	sf::Clock debugClock;
	bool debug = false;
	HUD playerHUD;
	GAMESTATE returnState = GAMESTATE::GAMELOOP;
	

public:
	void checkPlayerHitEnemy();
	void testDebugging();
	void updateViews(sf::RenderWindow *window, sf::Time elapsed);
	void init(sf::RenderWindow *window);
	GAMESTATE update(sf::RenderWindow *window, sf::Time elapsed);
	void updatePlayerMovement(Player *player, sf::Time elapsed);
	void updateActiveMaps();
	void cleanup();
	Game();
	~Game();
};

