#include "HitBox.h"

void HitBox::update()
{
	rect.setPosition(getPosition());
	rect.setRotation(getRotation());
}

void HitBox::updatePoints()
{
	topLeft = rect.getTransform().transformPoint(sf::Vector2f(0, 0));
	topRight = rect.getTransform().transformPoint(sf::Vector2f(rect.getSize().x, 0));
	bottomLeft = rect.getTransform().transformPoint(sf::Vector2f(0, rect.getSize().y));
	bottomRight = rect.getTransform().transformPoint(sf::Vector2f(rect.getSize().x, rect.getSize().y));
}

bool HitBox::checkIntersect(HitBox &hitbox2) {

	updatePoints();
	hitbox2.updatePoints();
	Axis1 = sf::Vector2f(topRight.x - topLeft.x, topRight.y - topLeft.y);
	Axis2 = sf::Vector2f(topRight.x - bottomRight.x, topRight.y - bottomRight.y);
	Axis3 = sf::Vector2f(hitbox2.topLeft.x - hitbox2.bottomLeft.x, hitbox2.topLeft.y - hitbox2.bottomLeft.y);
	Axis4 = sf::Vector2f(hitbox2.topLeft.x - hitbox2.topRight.x, hitbox2.topLeft.y - hitbox2.topRight.y);

	float minA;
	float minB;
	float maxA;
	float maxB;

	// Test One
	normalize(Axis1);
	
	project(Axis1, minA, maxA);
	hitbox2.project(Axis1, minB, maxB);
	//std::cout << minA << " " << maxA << std::endl;
	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;

	// Test Two
	normalize(Axis2);

	project(Axis2, minA, maxA);
	hitbox2.project(Axis2, minB, maxB);
	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;

	// Test Three
	normalize(Axis3);

	project(Axis3, minA, maxA);
	hitbox2.project(Axis3, minB, maxB);
	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;

	// Test Four
	normalize(Axis4);

	project(Axis4, minA, maxA);
	hitbox2.project(Axis4, minB, maxB);
	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;

	return true;
}

void  HitBox::project(sf::Vector2f& axis, float &min, float &max)
{
	float _dot = dot(axis,topLeft);

	min = _dot;
	max = _dot;


	_dot = dot(topRight, axis);
	if (_dot<min)
		min = _dot;
	else if (_dot>max)
		max = _dot;

	_dot = dot(bottomRight, axis);
	if (_dot<min)
		min = _dot;
	else if (_dot>max)
		max = _dot;

	_dot = dot(bottomLeft, axis);
	if (_dot<min)
		min = _dot;
	else if (_dot>max)
		max = _dot;

	/*
	for (short i = 1; i<4; i++)
	{
		_dot = dot(this->vertex[i], axis);

		if (_dot<min)
			min = _dot;
		else if (_dot>max)
			max = _dot;
	}
	*/
}

float HitBox::distance(float minA, float maxA, float minB, float maxB) // Positive return = no hit
{
	if (minB > maxA) return minB - maxA;
	else return minA - maxB;
}

float HitBox::dot(sf::Vector2f& vector1, sf::Vector2f& vector2)
{
	return vector1.x*vector2.x + vector1.y*vector2.y;
}

void HitBox::normalize(sf::Vector2f &vector)
{
	const float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	if (length == 0)
	{
		return;
	}
	vector.x = vector.x / length;
	vector.y = vector.y / length;
}

HitBox::HitBox()
{
	rect.setSize(sf::Vector2f(45, 128));
}


HitBox::~HitBox()
{
}
