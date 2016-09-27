#pragma once
#include "Entity.h"

class Tile : public Entity
{
private:
	unsigned int width = 32;
	unsigned int height = 32;

public:
	int index;
	unsigned int getWidth();
	unsigned int getHeight();
	void setIndex(int number);
	bool collidable;
	Tile();
	~Tile();
};

