#pragma once
#include "Entity.h"

enum class TILETYPE
{
	GRASSFLOOR,
	PATCHFLOOR,
	DIRTFLOOR
};


class Tile : public Entity
{
private:
	
	unsigned int width = 32;
	unsigned int height = 32;
	TILETYPE type;
public:
	int index;
	unsigned int getWidth();
	unsigned int getHeight();
	void setIndex(int number);
	bool collidable;
	Tile();
	~Tile();
};

