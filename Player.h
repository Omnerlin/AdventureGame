#pragma once
#include "Sword.h"

enum class DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UPRIGHT,
	UPLEFT,
	DOWNRIGHT,
	DOWNLEFT
};

class Player : public Entity
{
private:
	
	
	int health = 100;

public:

	sf::Time hitRecoveryTime;
	bool isAttacking = false;
	float attackTimeStamp;
	int animCounter = 0;
	int counter = 0;
	float swingSwordTime = 0;
	sf::Clock attackClock;


	Sword sword;


	float timeStamp;
	float baseMoveSpeed = 0.2;
	float acceleration = 0.5;
	float m_maxMoveSpeed = 5;
	float m_moveSpeed = 0;
	DIRECTION direction;

	unsigned int animFrames = 4;
	unsigned int currentAnimFrame = 4;
	int oldPositionX;
	int oldPositionY;
	int newPositionX;
	int newPositionY;

	void update(sf::RenderWindow *window, sf::Time elapsed);
	void animate();

	void attack();
	void updateAttack(sf::Time elapsed);

	Player();
	~Player();
};

