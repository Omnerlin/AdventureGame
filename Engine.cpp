#include "Engine.h"

void Engine::init()
{
	window->create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "AdventureGame");
	//window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
	state->init(window);
}

void Engine::switchStates()
{

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
	while (window->isOpen())
	{
		sf::Time elapsed = gameClock.getElapsedTime();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
		}
		window->clear();
		currentGamestate = state->update(window, elapsed);
		if (currentGamestate != state->returnState)
		{
			switchStates(currentGamestate);
		}
		window->display();
	}
}


Engine::Engine()
{
}


Engine::~Engine()
{
	//state->cleanup();
	delete state;
	delete window;
}
