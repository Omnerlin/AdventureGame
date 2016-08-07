#include "Game.h"

void Game::init(sf::RenderWindow *window) {

	mapManager.loadMap("geebo.txt", groundTexture, 0, 0);
	mapManager.loadMap("map2col.txt", groundTexture, 0, 576);
	mapManager.loadMap("3rdmap.txt", groundTexture, -1024, 576);
	
	gameView.setSize(mapManager.mapArray[0].view.getSize());
	gameView.setCenter(mapManager.mapArray[0].view.getCenter());
	
	window->setView(gameView);
}

GAMESTATE Game::update(sf::RenderWindow *window, sf::Time elapsed) {

			testDebugging();
			updateViews(window);
			updatePlayerMovement(player, elapsed);
			updateActiveMaps();
			mapManager.drawMapsLayerOne(window, debug);
			mapManager.drawMapsLayerTwo(window, debug);
			window->draw(player->rect);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			{
				return GAMESTATE::MENU;
			}
			return this->returnState;
}

void Game::updatePlayerMovement(Player *player, sf::Time elapsed)
{
	float timeElapsed = elapsed.asMilliseconds();
	float deltaTime = timeElapsed - player->timeStamp;
	player->m_moveSpeed = (player->baseMoveSpeed * deltaTime)/3;
	
	player->oldPositionX = player->rect.getPosition().x;
	player->oldPositionY = player->rect.getPosition().y;


	//std::cout << m_moveSpeed << std::endl;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player->direction = DIRECTION::UPLEFT;
		player->rect.move(-player->m_moveSpeed, 0);
		// Check Collision
		mapManager.testMapPlayerCollisions(player, 1);
		player->rect.move(0, -player->m_moveSpeed);
		mapManager.testMapPlayerCollisions(player, 2);
		// Check Collision
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player->direction = DIRECTION::UPRIGHT;
		player->rect.move(player->m_moveSpeed, 0);
		mapManager.testMapPlayerCollisions(player, 1);
		player->rect.move(0, -player->m_moveSpeed);
		mapManager.testMapPlayerCollisions(player, 2);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player->direction = DIRECTION::DOWNLEFT;
		player->rect.move(-player->m_moveSpeed, 0);
		mapManager.testMapPlayerCollisions(player, 1);
		player->rect.move(0, player->m_moveSpeed);
		mapManager.testMapPlayerCollisions(player, 2);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player->direction = DIRECTION::DOWNRIGHT;
		player->rect.move(player->m_moveSpeed, 0);
		mapManager.testMapPlayerCollisions(player, 1);
		player->rect.move(0, player->m_moveSpeed);
		mapManager.testMapPlayerCollisions(player, 2);
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player->direction = DIRECTION::LEFT;
			player->rect.move(-player->m_moveSpeed, 0);
			mapManager.testMapPlayerCollisions(player, 1);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player->direction = DIRECTION::RIGHT;
			player->rect.move(player->m_moveSpeed, 0);
			mapManager.testMapPlayerCollisions(player, 1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player->direction = DIRECTION::DOWN;
			player->rect.move(0, player->m_moveSpeed);
			mapManager.testMapPlayerCollisions(player, 2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player->direction = DIRECTION::UP;
			player->rect.move(0, -player->m_moveSpeed);
			mapManager.testMapPlayerCollisions(player, 2);
		}
	}

	player->newPositionX = player->rect.getPosition().x;
	player->newPositionY = player->rect.getPosition().y;
	player->timeStamp = elapsed.asMilliseconds();
}

void Game::cleanup()
{
	delete groundTexture; std::cout << "Texture Deleted" << std::endl;
	delete player; 
}

void Game::updateActiveMaps()
{
	for (int i = 0; i < mapManager.mapArray.size(); i++) {
		if (player->rect.getGlobalBounds().intersects(mapManager.mapArray[i].drawAndCollisionRect.getGlobalBounds())) {
			mapManager.mapArray[i].active = true;
		}
		else {
			mapManager.mapArray[i].active = false;
		}
	}
}

void Game::testDebugging()
{
	sf::Time debugTimer = debugClock.getElapsedTime();
	if (debugTimer.asSeconds() >= 0.5 && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		if (!debug) {
			debug = true;
			debugClock.restart();
		}
		else if (debug) {
			debug = false;
			debugClock.restart();
		}
	}
}

void Game::updateViews(sf::RenderWindow *window) {
	gameView.move((currentview.getCenter().x - gameView.getCenter().x) * 0.3, (currentview.getCenter().y - gameView.getCenter().y) * 0.3);
	window->setView(gameView);
	
	//std::cout << "X: " << gameView.getCenter().x << " Y: " << gameView.getCenter().y << std::endl;
	for (int i = 0; i < mapManager.mapArray.size(); i++) {
		if (player->rect.getGlobalBounds().intersects(mapManager.mapArray[i].rect.getGlobalBounds())) {
			currentview = mapManager.mapArray[i].view;
		}
	}
	
}

Game::Game()
{
	//groundTexture->loadFromFile("media\\grassTiles.png");
	groundTexture->loadFromFile("media\\tileMap.png");
	std::cout << "Constructor Called";
}


Game::~Game()
{
	std::cout << "Game Destructor Called" << std::endl;
	delete groundTexture; std::cout << "Texture Deleted" << std::endl;
	delete player; std::cout << "Player Deleted" << std::endl;
}
