#include "ClickableButton.h"

void ClickableButton::update(sf::RenderWindow *window) {
	
	
	if (active)
	{
		//std::cout << "X: " << sf::Mouse::getPosition(*window).x << " Y: " << sf::Mouse::getPosition(*window).y << std::endl;
		sf::Vector2f converted = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		/*if (sf::Mouse::getPosition(*window).x > rect.getPosition().x && sf::Mouse::getPosition(*window).x < rect.getPosition().x + rect.getSize().x
			&& sf::Mouse::getPosition(*window).y > rect.getPosition().y && sf::Mouse::getPosition(*window).y < rect.getPosition().y + rect.getSize().y) { 
			mousedOver = true;
		}
		*/
		if (converted.x > rect.getPosition().x && converted.x < rect.getPosition().x + rect.getSize().x
			&& converted.y > rect.getPosition().y && converted.y < rect.getPosition().y + rect.getSize().y) {
			mousedOver = true;
		}
		else { mousedOver = false; rect.setFillColor(sf::Color(200, 200, 200, 255)); }

		if (mousedOver && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			std::cout << "Button Pressed" << std::endl;
			pressed = true;
			rect.setFillColor(sf::Color(200, 0, 0, 255));
		}
		
		if (pressed)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				released = true;
				std::cout << "Button Released" << std::endl;

				mousedOver = false;
				pressed = false;
				released = false;
			}
			//else {
			//	released = false;
			//}
		}

		

		
	}
}

void ClickableButton::updateColor()
{
	if (released)
	{
		rect.setFillColor(sf::Color(0, 200, 0, 255));
	}
	else if (pressed) {
		rect.setFillColor(sf::Color(0, 0, 200, 255));
	}
	else if (mousedOver) {
		rect.setFillColor(sf::Color::Yellow);
	}
	
	else
	{
		rect.setFillColor(sf::Color(200, 200, 200, 255));
	}

}

ClickableButton::ClickableButton()
{
	rect.setSize(sf::Vector2f(100, 50));
	rect.setFillColor(sf::Color::Blue);
}


ClickableButton::~ClickableButton()
{
}
