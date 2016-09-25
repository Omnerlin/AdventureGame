#include "Menu.h"
#include <math.h>


Menu::Menu()
{


}

void Menu::init(sf::RenderWindow *window) {
	startButton.rect.setPosition(window->getDefaultView().getSize().x / 2 - startButton.rect.getSize().x/2, window->getDefaultView().getSize().y / 1.5);
	quitButton.rect.setPosition(200, 500);
	font.loadFromFile("fonts\\computerFont.ttf");
	titleText.setFont(font);
	titleText.setString("AdventureGame!");
	titleText.setCharacterSize(70);
	//titleText.setPosition(window->getSize().x / 3.5, window->getSize().y / 5);
	titleText.setPosition(window->getDefaultView().getSize().x / 3.5, window->getDefaultView().getSize().y / 5);
	originalTitleYPos = titleText.getPosition().y;
	background.setPosition(0, 0);
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	window->setView(window->getDefaultView());
}

void Menu::updateTitleText(sf::Time elapsed)
{
	float timeElapsed = elapsed.asMilliseconds();
	float deltaTime = timeElapsed - titleTextTimeStamp;
	//titleText.move(0, (0.05 * (sinf(elapsed.asMilliseconds() * 0.002)) * deltaTime));
	titleText.setPosition(titleText.getPosition().x, originalTitleYPos + (20.f * (sinf(elapsed.asMilliseconds() * 0.002))));
	//std::cout << titleText.getPosition().y << std::endl;
	titleTextTimeStamp = elapsed.asMilliseconds();
}

void Menu::updateBackgroundColor(sf::Time elapsed)
{
	unsigned char red = (unsigned char)((1 + sin(elapsed.asMilliseconds() * 0.0002)) * 100);
	unsigned char green = (unsigned char)((1 + sin(elapsed.asMilliseconds() * 0.0003)) * 100);
	unsigned char blue = (unsigned char)((1 + sin(elapsed.asMilliseconds() * 0.0007)) * 100);
	background.setFillColor(sf::Color(red, green, blue, 255));
	
}

GAMESTATE Menu::update(sf::RenderWindow *window, sf::Time elapsed) {

	startButton.update(window);
	startButton.updateColor();
	updateTitleText(elapsed);
	updateBackgroundColor(elapsed);
	window->draw(background);
	window->draw(startButton.rect);
	window->draw(titleText);

	if (startButton.pressed)
	{
		return GAMESTATE::GAMELOOP;
	}
	return this->returnState;

}

void Menu::cleanup()
{

}

Menu::~Menu()
{
	std::cout << " Menu Destructor Called" << std::endl;
}
