#include "Player.h"


void Player::animate()
{

}

/*
void Player::update(sf::Time elapsed)
{
	float timeElapsed = elapsed.asMilliseconds();
	float deltaTime = timeElapsed - timeStamp;
	m_moveSpeed = (baseMoveSpeed * deltaTime);

	oldPositionX = rect.getPosition().x;
	oldPositionY = rect.getPosition().y;

	
	//std::cout << m_moveSpeed << std::endl;
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
			direction = DIRECTION::UPLEFT;
			rect.move(-m_moveSpeed, 0);
			// Check Collision
			
			rect.move(0, -m_moveSpeed);
			// Check Collision
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
			direction = DIRECTION::UPRIGHT;
			rect.move(m_moveSpeed, -m_moveSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
			direction = DIRECTION::DOWNLEFT;
			rect.move(-m_moveSpeed, m_moveSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
			direction = DIRECTION::DOWNRIGHT;
			rect.move(m_moveSpeed, m_moveSpeed);
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
				direction = DIRECTION::LEFT;
				rect.move(-m_moveSpeed, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
				direction = DIRECTION::RIGHT;
				rect.move(m_moveSpeed, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
				direction = DIRECTION::DOWN;
				rect.move(0, m_moveSpeed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{		
				direction = DIRECTION::UP;
				rect.move(0, -m_moveSpeed);		
		}
	}
	newPositionX = rect.getPosition().x;
	newPositionY = rect.getPosition().y;
	timeStamp = elapsed.asMilliseconds();
}
*/

Player::Player()
{
	rect.setPosition(75, 300);
	rect.setFillColor(sf::Color::Magenta);
	rect.setSize(sf::Vector2f(32,32));
}


Player::~Player()
{
}
