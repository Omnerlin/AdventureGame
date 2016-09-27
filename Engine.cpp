#include "Engine.h"

void Engine::init()
{
	window->create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "AdventureGame");
	//window->setFramerateLimit(30);
	//window->setVerticalSyncEnabled(true);
	state->init(window);
}

void Engine::switchStates(GAMESTATE state)
{
	//this->state->cleanup();
	delete this->state;

	if (state == GAMESTATE::GAMELOOP) {
		this->state = new Game;
		this->state->returnState = GAMESTATE::GAMELOOP;
		currentGamestate = GAMESTATE::GAMELOOP;
		this->state->init(window);
	}

	else if (state == GAMESTATE::MENU) {
		this->state = new Menu;
		this->state->returnState = GAMESTATE::MENU;
		currentGamestate = GAMESTATE::MENU;
		this->state->init(window);
	}
}


void Engine::update()
{
	sf::Clock gameClock;
	sf::Clock fpsClock;
	while (window->isOpen())
	{
		fps++;
		sf::Time elapsed = gameClock.getElapsedTime();
		sf::Time fpsElapsed = fpsClock.getElapsedTime();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left) {

				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
		}
		window->clear();
		currentGamestate = state->update(window, elapsed);
if (currentGamestate != state->returnState)
		{
			gameClock.restart();
			switchStates(currentGamestate);
		}
		window->display();
		if (fpsElapsed.asMilliseconds() >= 1000)
		{
			std::cout << fps << std::endl;
			fps = 0;
			fpsClock.restart();
		}
	}
}


Engine::Engine()
{
}


Engine::~Engine()
{
	delete state;
	delete window;
}
