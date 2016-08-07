#pragma once
#include "Entity.h"

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
	float timeStamp;
	float baseMoveSpeed = 0.6;
	float acceleration = 0.5;
	float m_maxMoveSpeed = 5;
	int m_moveSpeed = 0;
	DIRECTION direction;


	int oldPositionX;
	int oldPositionY;
	int newPositionX;
	int newPositionY;

	//void update(sf::Time elapsed);
	void animate();
	Player();
	~Player();
};

