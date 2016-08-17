#include "Game.h"

void Game::init(sf::RenderWindow *window) {

	mapManager.loadMap("geebo.txt", groundTexture, 0, 0);
	mapManager.loadMap("map2col.txt", groundTexture, 0, 576);
	mapManager.loadMap("3rdmap.txt", groundTexture, -1024, 576);
	mapManager.loadMap("map4.txt", groundTexture, 1024, 576);
	
	currentview.setCenter(mapManager.mapArray[0].view.getCenter());
	gameView.setSize(mapManager.mapArray[0].view.getSize());
	gameView.setCenter(mapManager.mapArray[0].view.getCenter());
	

	window->setView(gameView);
	playerHUD.view.setCenter(gameView.getCenter());
	playerHUD.view.setSize(gameView.getSize());
	playerHUD.view.setViewport(sf::FloatRect(0, 0, 1, 0.1));

}

void Game::checkPlayerHitEnemy()
{
	if (player->sword.hitBoxActive == true) {
		for (int i = 0; i < enemyManager.enemyArray.size(); ++i)
		{
			if (enemyManager.enemyArray[i].active && !enemyManager.enemyArray[i].recovering && std::abs(enemyManager.enemyArray[i].rect.getPosition().x - player->rect.getPosition().x <= 300 )
				&& std::abs(enemyManager.enemyArray[i].rect.getPosition().y - player->rect.getPosition().y <= 300))
			{
				if (player->sword.hitBox.rect.getGlobalBounds().intersects(enemyManager.enemyArray[i].rect.getGlobalBounds()))
				{
					if (player->sword.hitBox.checkIntersect(enemyManager.enemyArray[i].hitBox))
					{
						//enemyManager.enemyArray[i].health -= 1;
						enemyManager.enemyArray[i].recovering = true;
						enemyManager.enemyArray[i].recoveryClock.restart();
						std::cout << "Enemy Hit " << std::endl;
					}
				}
			}
		}
	}
}

GAMESTATE Game::update(sf::RenderWindow *window, sf::Time elapsed) {

	
	testDebugging();
	updateViews(window, elapsed);
	updatePlayerMovement(player, elapsed);
	updateActiveMaps();
	mapManager.drawMapsLayerOne(window, debug);
	mapManager.drawMapsLayerTwo(window, debug);
	enemyManager.drawEnemies(window);
	enemyManager.updateEnemies();
	player->update(window, elapsed);
	player->sword.update(window);
	checkPlayerHitEnemy();
	window->draw(player->rect);

	//window->setView(playerHUD.view);
	//playerHUD.update();
	//playerHUD.drawElements(window);

	//window->setView(gameView);

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
	//std::cout << timeElapsed << std::endl;
	
	player->m_moveSpeed = (player->baseMoveSpeed * deltaTime);
	//std::cout << player->m_moveSpeed << std::endl;
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

void Game::updateViews(sf::RenderWindow *window, sf::Time elapsed) {
	float timeElapsed = elapsed.asMilliseconds();
	float deltaTime = timeElapsed - viewTimeStamp;
	gameView.move(((currentview.getCenter().x - gameView.getCenter().x) * 0.01) * deltaTime, ((currentview.getCenter().y - gameView.getCenter().y) * 0.01) * deltaTime);
	//sf::Vector2f converted = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	//gameView.setCenter((player->rect.getPosition().x + converted.x) / 2 , (player->rect.getPosition().y + converted.y) / 2 );

	window->setView(gameView);
	for (int i = 0; i < mapManager.mapArray.size(); i++) {
		if (player->rect.getGlobalBounds().intersects(mapManager.mapArray[i].rect.getGlobalBounds())) {
			currentview = mapManager.mapArray[i].view;
		}
	}
	
	viewTimeStamp = elapsed.asMilliseconds();
}

Game::Game()
{
	groundTexture->loadFromFile("media\\tileMap.png");
	std::cout << "Constructor Called";
}


Game::~Game()
{
	std::cout << "Game Destructor Called" << std::endl;
	delete groundTexture; std::cout << "Texture Deleted" << std::endl;
	delete player; std::cout << "Player Deleted" << std::endl;
}
