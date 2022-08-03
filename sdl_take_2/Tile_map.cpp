#include "Includes.h"




Tile_map::Tile_map()
{
	
}

Tile_map::~Tile_map()
{
	
}

void Tile_map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);


	int srcX, srcY;


	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			srcY = atoi(&tile) * TILE_SIZE;
			mapFile.get(tile);
			srcX = atoi(&tile) * TILE_SIZE;
			Game::AddTile(srcX, srcY, x * TILE_SIZE, y * TILE_SIZE);
			mapFile.ignore();
		}
		//mapFile.ignore();
	}

	mapFile.close();
}

