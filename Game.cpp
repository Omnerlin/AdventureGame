#include "Game.h"

void Game::init(sf::RenderWindow *window) {

		mapManager.loadMap("AG_1A.txt", groundTexture, 0, 0, enemyManager);
		mapManager.loadMap("AG_1B.txt", groundTexture, 1, 0, enemyManager);
		mapManager.loadMap("AG_1C.txt", groundTexture, 2, 0, enemyManager);
		mapManager.loadMap("AG_1D.txt", groundTexture, 3, 0, enemyManager);

		mapManager.loadMap("AG_2A.txt", groundTexture, 0, 1, enemyManager);
		mapManager.loadMap("AG_2B.txt", groundTexture, 1, 1, enemyManager);
		mapManager.loadMap("AG_2C.txt", groundTexture, 2, 1, enemyManager);
		mapManager.loadMap("AG_2D.txt", groundTexture, 3, 1, enemyManager);

		mapManager.loadMap("AG_3AD.txt",groundTexture, 0, 2, enemyManager);
		mapManager.loadMap("AG_3B.txt", groundTexture, 1, 2, enemyManager);
		mapManager.loadMap("AG_3C.txt", groundTexture, 2, 2, enemyManager);
		mapManager.loadMap("AG_3D.txt", groundTexture, 3, 2, enemyManager);

		mapManager.loadMap("AG_4A.txt", groundTexture, 0, 3, enemyManager);
		mapManager.loadMap("AG_4B.txt", groundTexture, 1, 3, enemyManager);
		mapManager.loadMap("AG_4C.txt", groundTexture, 2, 3, enemyManager);
		mapManager.loadMap("AG_4D.txt", groundTexture, 3, 3, enemyManager);
	
		std::cout << mapManager.mapArray.size() << std::endl;

	currentview.setCenter(mapManager.mapArray[0].view.getCenter());
	gameView.setSize(mapManager.mapArray[0].view.getSize());
	gameView.setCenter(mapManager.mapArray[0].view.getCenter());

	playerHUD.view.setCenter(gameView.getCenter());
	playerHUD.view.setSize(gameView.getSize().x, gameView.getSize().y);

	std::cout << mapManager.getWidth() << std::endl;
	std::cout << mapManager.getHeight() << std::endl;

	mapManager.setupTileMap();
	setupGrid();

	// Be sure to fix this (This is just for testing)
	DoorSwitch doorSwitch;
	doorSwitch.setPosition(600, 400);
	doorSwitch.updatePosition();
	doorSwitch.sprite.setTexture(switchTexture);
	doorSwitches.push_back(doorSwitch);
	// -----------------------------------------------
	
	window->setView(gameView);
}

void Game::enemyFindPath(Enemy & enemy, sf::Vector2f &target)
{

}

void Game::drawGridNodes(sf::RenderWindow *window)
{
	window->draw(pathGrid.gridNodes[player->gridPositionX][player->gridPositionY].circle);
}

void Game::setupGrid()
{
	pathGrid.gridNodes.resize(mapManager.tileMap.size());
	for (int i = 0; i < pathGrid.gridNodes.size(); i++) {
		pathGrid.gridNodes[i].resize(mapManager.tileMap[i].size());
	}


	for (int i = 0; i < pathGrid.gridNodes.size(); i++) {
		for (int j = 0; j < pathGrid.gridNodes[i].size(); j++) {
			if (mapManager.tileMap[i][j].collidable) {
				pathGrid.gridNodes[i][j].traversible = false;
				pathGrid.gridNodes[i][j].active = false;
			}
			pathGrid.gridNodes[i][j].setPosition(mapManager.tileMap[i][j].rect.getPosition());
			pathGrid.gridNodes[i][j].circle.setPosition(mapManager.tileMap[i][j].rect.getPosition());
		}
	}
}

void Game::checkPlayerHitButton()
{
	if (player->sword.hitBoxActive) {
		for (int i = 0; i < doorSwitches.size(); i++) {
			if (doorSwitches[i].getToggleable() && player->sword.hitBox.checkIntersect(doorSwitches[i].hitbox)) {
				doorSwitches[i].toggleState();
			}
		}
	}
}

void Game::handlePlayerProjectileCollision()
{
		for (int i = 0; i < enemyManager.enemyArray.size(); i++) {
			for (int k = 0; k < enemyManager.enemyArray[i].projectileManager.projectiles.size(); k++)
			{
				if (enemyManager.enemyArray[i].projectileManager.projectiles[k].getActive() == true 
					&& enemyManager.enemyArray[i].projectileManager.projectiles[k].rect.getGlobalBounds().intersects(player->hurtbox.rect.getGlobalBounds())) {
					if (player->hittable)
					{
						player->hittable = false;
						player->setHealth(player->getHealth() - enemyManager.enemyArray[i].projectileManager.projectiles[k].getDamage());
						player->recoveryClock.restart();
					}	
					enemyManager.enemyArray[i].projectileManager.projectiles[k].setActive(false);
				}
			}
		}
}

void Game::checkProjectileCollisionWithMaps()
{
	for (int i = 0; i < enemyManager.enemyArray.size(); i++) {
		for (int k = 0; k < enemyManager.enemyArray[i].projectileManager.projectiles.size(); k++)
		{
			if (enemyManager.enemyArray[i].projectileManager.projectiles[k].getActive() == true) {
				mapManager.testMapProjectileCollisions(enemyManager.enemyArray[i].projectileManager.projectiles[k]);
			}
		}
	}
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
						enemyManager.enemyArray[i].health -= 1;
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

	//Handle Logic
	enemyManager.updateEnemies(elapsed, player->rect.getPosition());
	checkProjectileCollisionWithMaps();
	handlePlayerProjectileCollision();
	checkPlayerHitButton();
	checkPlayerHitEnemy();

	// Draw Stuff plus some logic
	enemyManager.drawEnemies(window);
	player->update(window, elapsed);
	player->sword.update(window);
	//window->draw(player->rect);

	/*for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			int indexX = player->gridPositionX + i;
			int indexY = player->gridPositionY + j;
			window->draw(mapManager.tileMap[indexX][indexY].rect);
		}
	}*/

	window->draw(player->sprite);
	window->draw(player->hurtbox.rect);
	drawGridNodes(window);

	for (int i = 0; i < doorSwitches.size(); i++) {
		window->draw(doorSwitches[i].sprite);
	}
	//window->draw(mapManager.tileMap[player->gridPositionX][player->gridPositionY].rect);

	window->setView(playerHUD.view);
	playerHUD.update(player->getHealth());
	playerHUD.drawElements(window);
	window->setView(gameView);

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
	
	player->m_moveSpeed = (player->baseMoveSpeed * deltaTime);
	player->oldPositionX = player->rect.getPosition().x;
	player->oldPositionY = player->rect.getPosition().y;

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

	player->gridPositionX = (int)player->rect.getPosition().x / 32;
	player->gridPositionY = (int)player->rect.getPosition().y / 32;
	//std::cout << "X: " << player->gridPositionX << "Y: " << player->gridPositionY << std::endl;
	
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
	groundTexture->loadFromFile("media\\tileMap2.png");
	std::cout << "Constructor Called";
	switchTexture.loadFromFile("media\\daButton.png");
}


Game::~Game()
{
	std::cout << "Game Destructor Called" << std::endl;
	delete groundTexture; std::cout << "Texture Deleted" << std::endl;
	delete player; std::cout << "Player Deleted" << std::endl;
	
}
