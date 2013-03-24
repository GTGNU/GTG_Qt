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
  char error[128];
  std::vector< std::vector< GTGTile* > > tiles;
  Uint32 backgroundColor;
  Uint16 spaceX, spaceY, width, height;
  float cameraX, cameraY, camTargetX, camTargetY, camFromX, camFromY; Uint32 camTime;
public:

  GTGPlayer player;

  GTGMap(); ~GTGMap();
  void Construct(); void Destruct();
  void Clear();
  const char *GetLastError();
  bool Load(const char *root, GTGTileSet *tileSet);
  void Draw(SDL_Surface *dst, Uint16 posX1, Uint16 posY1, Uint16 posX2, Uint16 posY2);
  void Frame(SDLTimer *timer, Uint16 posX1, Uint16 posY1, Uint16 posX2, Uint16 posY2);
};

#endif
