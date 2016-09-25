#pragma once
#include "Sword.h"
#include "ProjectileManager.h"

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
	sf::Texture playerTexture;
	
	float recoveryTime = 1.5; // in seconds

public:
	int gridPositionX;
	int gridPositionY;

	HitBox hurtbox;
	int getHealth();
	void setHealth(int health);
	bool hittable = true;
	sf::Clock recoveryClock;
	//sf::Time hitRecoveryTime;
	bool isAttacking = false;
	float attackTimeStamp;
	int animCounter = 0;
	int counter = 0;

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
	float oldPositionX;
	float oldPositionY;
	float newPositionX;
	float newPositionY;

	void update(sf::RenderWindow *window, sf::Time elapsed);
	void animate();

	void attack();
	void updateAttack(sf::Time elapsed);

	Player();
	~Player();
};

