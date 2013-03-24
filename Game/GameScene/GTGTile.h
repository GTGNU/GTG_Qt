#pragma once
#ifndef _GTGTILE_H_
#define _GTGTILE_H_

#include "SDLHelper.h"
#include <vector>

struct GTGTileTex{
  SDL_Surface *surface;
  Uint32 duration;
};

class GTGTile{
  std::vector<GTGTileTex> tex;
  Uint32 lastFrame, lastTex, lastTexFrame;
public:
  GTGTile(); ~GTGTile();
  void Construct(); void Destruct();
  void AddFrame(SDL_Surface *s, Uint32 duration);
  void Free();
  void Frame(SDLTimer *timer);
  SDL_Surface *GetSurface();
};

class GTGTileSet{
  char error[128];
public:
  std::vector<GTGTile> tiles;

  GTGTileSet(); ~GTGTileSet();
  void Construct(); void Destruct();
  const char *GetLastError();
  int Load(const char *root); //return -1 on error, or the number of tiles loaded
  void Free();
  void Frame(SDLTimer *timer);
};

#endif
