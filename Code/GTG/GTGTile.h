#pragma once
#ifndef _GTGTILE_H_
#define _GTGTILE_H_

#include "SDLHelper.h"
#include <vector>

class GTGTile{

	struct GTGTileTex{
		SDL_Surface *surface;
		Uint32 duration;
	};

	std::vector<GTGTileTex> tex;
	Uint32 lastFrame, lastTex, lastTexFrame;
public:
	GTGTile(); ~GTGTile();
	void Construct(); void Destruct();
	void AddFrame(SDL_Surface *s, Uint32 duration);
	void Free();
	void SetTime(Uint32 time);
	void Frame();
	SDL_Surface *GetSurface();
};

class GTGTileSet{
	char error[128];
public:
	std::vector<GTGTile> tiles;

	GTGTileSet(); ~GTGTileSet();
	void Construct(); void Destruct();
	const char *GetLastError();
	int Load(const char *root, const char *filename); //return -1 on error, or the number of tiles loaded
	void Free();
	void Frame();
	bool IsValidID(int id);
};

#endif
