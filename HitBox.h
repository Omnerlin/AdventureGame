#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"

class HitBox : public sf::Transformable
{
private:
	sf::Vector2f Axis1;
	sf::Vector2f Axis2;
	sf::Vector2f Axis3;
	sf::Vector2f Axis4;


	sf::Vector2f topLeft; // = rect.getTransform().transformPoint(sf::Vector2f(0, 0));
	sf::Vector2f topRight;// = rect.getTransform().transformPoint(sf::Vector2f(rect.getSize().x, 0));
	sf::Vector2f bottomLeft;// = rect.getTransform().transformPoint(sf::Vector2f(0, rect.getSize().y));
	sf::Vector2f bottomRight;// = rect.getTransform().transformPoint(sf::Vector2f(rect.getSize().x, rect.getSize().y));


	void normalize(sf::Vector2f &vector);
	float dot(sf::Vector2f& vector1, sf::Vector2f& vector2);
	float distance(float minA, float maxA, float minB, float maxB);
	void project(sf::Vector2f & axis, float & min, float & max);
	void updatePoints();

public:
	
	void update();
	bool checkIntersect(HitBox &hitbox2);
	sf::RectangleShape rect;



	HitBox();
	~HitBox();
};

