#include "Player.h"


void Player::animate()
{
	
}
void Player::updateAttack(sf::Time elapsed)
{
	sf::Time attackTime = attackClock.getElapsedTime();

	if (animCounter <= 2 && attackTime.asSeconds() >= 0.05)
	{
		animCounter++;
		if (animCounter == 1)
		{
			sword.hitBoxActive = true;
		}
		else {
			sword.hitBoxActive = false;
		}
		
		attackClock.restart();
	}
	else if (animCounter >= 3 && attackTime.asSeconds() >= 0.20)
	{
		//sword.hitBoxActive = false;
		animCounter++;
		attackClock.restart();
	}
	else if (animCounter >= 4)
	{
		isAttacking = false;
		sword.drawAnim = false;
		//sword.hitBoxActive = false;
	}
	sword.animSprite.setTextureRect(sf::IntRect(animCounter * 32, 0, 32, 128));
}

void Player::attack()
{
	animCounter = 0;
	attackClock.restart();
	isAttacking = true;
	sword.drawAnim = true;
}

int Player::getHealth()
{
	return health;
}

void Player::setHealth(int health)
{
	this->health = health;
}

void Player::update(sf::RenderWindow *window, sf::Time elapsed)
{
	sf::Time attackTimer = attackClock.getElapsedTime();
	//std::cout << attackClock.getElapsedTime().asSeconds() << std::endl;
	sf::Vector2f converted = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	float mouseCompareX = converted.x - (rect.getPosition().x + rect.getSize().x/2);
	float mouseCompareY = converted.y - (rect.getPosition().y + rect.getSize().y / 2);

	float radian = std::atan2f(mouseCompareX, mouseCompareY);
	float angle = radian * (180 / 3.14159265);

	sword.setRotation(angle * -1 + sword.offset);
	sword.animSprite.setPosition(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2);
	sword.hitBox.setPosition(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2);

	if (!hittable && recoveryClock.getElapsedTime().asSeconds() <= recoveryTime)
	{
		sprite.setColor(sf::Color(255, 100, 100, 150));
		hittable = false;
	}
	else
	{
		sprite.setColor(sf::Color(255, 255, 255, 255));
		hittable = true;
	}
	
	if (angle > 30 && angle < 150)
	{
		sword.direction = SWORDDIRECTION::RIGHT;
		sword.animSprite.setScale(1, -1);
	}
	else if (angle < -30 && angle > -150)
	{
		sword.direction = SWORDDIRECTION::LEFT;
		sword.animSprite.setScale(1, 1);
	}

	if (sword.direction == SWORDDIRECTION::RIGHT)
	{
		sword.setPosition(rect.getPosition().x + 32, rect.getPosition().y + 4);
	}
	else if(sword.direction == SWORDDIRECTION::LEFT)
	{
		sword.setPosition(rect.getPosition().x - 2, rect.getPosition().y + 4);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAttacking)
	{
		attack();
	}

	if (isAttacking)
	{
		updateAttack(attackTimer);
	}

	if (health <= 0) {
		health = 0;
	}

	sprite.setPosition(rect.getPosition().x - 4, rect.getPosition().y-6);
	hurtbox.setPosition(sprite.getPosition().x, sprite.getPosition().y - 32);
	hurtbox.update();


}



Player::Player()
{
	rect.setPosition(700, 440);
	rect.setFillColor(sf::Color::White);
	hurtbox.rect.setSize(sf::Vector2f(32, 64));
	hurtbox.rect.setFillColor(sf::Color(0,0,255,50));
	rect.setOutlineColor(sf::Color::Black);
	rect.setSize(sf::Vector2f(24,26));
	sprite.setOrigin(8, 16);
	sprite.setScale(2.0, 2.0);
	playerTexture.loadFromFile("media\\theSun.png");
	sprite.setTexture(playerTexture);
	
}


Player::~Player()
{
}
