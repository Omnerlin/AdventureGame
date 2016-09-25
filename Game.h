#pragma once
#include "State.h"
#include <iostream>
#include "MapManager.h"
#include "Player.h"
#include "Gamestates.h"
#include "EnemyManager.h"
#include "HUD.h"
#include "DoorSwitch.h"
#include "PathfindingGrid.h"

class Game : public State
{
private:

	PathfindingGrid pathGrid;
	sf::Texture switchTexture;
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
	std::vector<DoorSwitch> doorSwitches;

	

public:

	void checkPlayerHitButton();
	void handlePlayerProjectileCollision();
	void checkProjectileCollisionWithMaps();
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

