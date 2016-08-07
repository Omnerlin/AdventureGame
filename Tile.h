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
	
	int width = 32;
	int height = 32;
	TILETYPE type;
public:
	int index;
	int getWidth();
	int getHeight();
	void setIndex(int number);
	bool collidable;
	Tile();
	~Tile();
};

