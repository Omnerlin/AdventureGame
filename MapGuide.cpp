#include "MapGuide.h"


void MapGuide::setup(sf::Texture *texture, int tileWidth, int tileHeight)
{
	int row = -1;
	for (int i = 0, j = 0; i < (texture->getSize().x / tileWidth) * (texture->getSize().y / tileHeight); i++, j++)
	{
		Tile tile;
		
		tile.index = i;
		if (i % (texture->getSize().x / tileWidth) == 0)
		{
			row++;
			j = 0;
		}
		tile.rect.setPosition(tile.getWidth() * j, tile.getHeight()*row);
		tiles.push_back(tile);
	}

}

MapGuide::MapGuide()
{
}


MapGuide::~MapGuide()
{
}
