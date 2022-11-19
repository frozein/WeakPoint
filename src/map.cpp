#include "map.hpp"
#include "IO/graphics.hpp"
#include <memory>
#include <math.h>
#include <random>

Map::Map(int _w, int _h, TileType* _tiles, PropType* _props, int screenW, int screenH)
{
	w = _w;
	h = _h;

	tiles = (TileType*)malloc(sizeof(TileType) * w * h);
	props = (PropType*)malloc(sizeof(PropType) * w * h);
	rands =      (int*)malloc(sizeof(int)      * w * h);
	memcpy(tiles, _tiles, sizeof(TileType) * w * h);
	memcpy(props, _props, sizeof(PropType) * w * h);

	for(int i = 0; i < w * h; i++)
		rands[i] = rand();

	float tileW = (float)screenW / w;
	float tileH = (float)screenH / h;
	if(tileW > tileH)
	{
		tileSize = (int)tileH;
		mapL = (int)((tileW - tileH) * w / 2.0f);
		mapT = 0;
	}
	else
	{
		tileSize = (int)tileH;
		mapT = (int)((tileH - tileW) * h / 2.0f);
		mapL = 0;
	}

	printf("%i, %i, %i", tileSize, mapL, mapT);
}

Map::~Map()
{
	free(tiles);
	free(props);
}

void Map::render()
{
	for(int y = 0; y < h; y++)
	for(int x = 0; x < w; x++)
	{
		SDL_Rect srcRect;
		srcRect.w = MAP_SRC_SIZE;
		srcRect.h = MAP_SRC_SIZE;

		SDL_Rect destRect;
		destRect.x = x * tileSize + mapL;
		destRect.y = y * tileSize + mapT;
		destRect.w = destRect.h = tileSize;

		float angle = 90.0f * (rands[x + y * w] / 4 % 4);

		switch(tiles[x + y * w]) //TODO: add rest of tile types
		{
		case TileType::GRASS:
		{
			srcRect.x = rands[x + y * w] % 4 * MAP_SRC_SIZE;
			srcRect.y = 0;
			break;
		}
		case TileType::DIRT:
		{
			srcRect.x = rands[x + y * w] % 4 * MAP_SRC_SIZE;
			srcRect.y = MAP_SRC_SIZE;
			break;
		}	
		}

		TextureAttributes attrib = TextureAttributes(TEXTURE_TILESET, srcRect, destRect,
													 angle, NULL, SDL_FLIP_NONE, 
													 {255, 255, 255, 255}, false, 1.0f);
		graphics::render_texture(attrib);

		if(props[x + y * w] == PropType::NONE)
			continue;

		switch(props[x + y * w])
		{
		case PropType::TREE:
		{
			srcRect.x = 4 * MAP_SRC_SIZE;
			srcRect.y = MAP_SRC_SIZE;
			break;
		}
		}

		attrib.srcRect = srcRect;
		attrib.angle = 0.0f;
		graphics::render_texture(attrib);
	}
}

void Map::get_map_pos(int sX, int sY, int* wX, int* wY)
{
	sX -= mapL;
	sY -= mapT;
	*wX = sX / tileSize;
	*wY = sY / tileSize;
}

bool Map::aabb_at(int x, int y, AABB* aabb)
{
	if(x < 0 || x >= w || y < 0 || y >= h)
		return false;

	if(props[x + y * w] == PropType::NONE)
		return false;

	switch(props[x + y * w])
	{
	case PropType::NONE:
		return false;
	case PropType::TREE:
	{
		aabb->minX = ( x      * tileSize + mapL) + (tileSize / MAP_SRC_SIZE);
		aabb->maxX = ((x + 1) * tileSize + mapL) - (tileSize / MAP_SRC_SIZE);
		aabb->minY = ( y      * tileSize + mapT) + (tileSize / MAP_SRC_SIZE);
		aabb->maxY = ((y + 1) * tileSize + mapT) - (tileSize / MAP_SRC_SIZE);
		return true;
	}
	}
}