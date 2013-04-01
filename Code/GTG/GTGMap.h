#pragma once
#ifndef _GTGMAP_H_
#define _GTGMAP_H_

#include "GTGPlayer.h"
#include "SDLHelper.h"
#include "SDL_gfxPrimitives.h"
#include <vector>

class GTGTile;
class GTGTileSet;
class GTGMap{
	struct GTGMapBackTile{ GTGTile *tile; bool solid; };

	Uint32 width, height, spaceX, spaceY, backgroundColor;
	std::vector< std::vector< GTGMapBackTile > > backTiles;
	int spawnX, spawnY;

	GTGPlayer player;
	char error[128];
	friend class GTG;

public:

	GTGMap(); ~GTGMap();
	void Construct(); void Destruct();
	void Clear();
	const char *GetLastError();
	bool Load(const char *root, const char *filename, GTGTileSet *tileSet);
	bool IsSolid(int x, int y);
	void Frame(SDLTimer *timer);
};

#endif
