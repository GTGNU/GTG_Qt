#pragma once
#ifndef _GTGPLAYER_H_
#define _GTGPLAYER_H_

#include "SDLHelper.h"
#include <math.h>

class GTGTileSet;
class GTGTile;
class GTGPlayer{
  char error[128];
  char action;
  /* 0 = left idle, 1 = right idle, 2 = up idle, 3 = down idle
     4 = left walk, 5 = right walk, 6 = up walk, 7 = down walk
  */
  Uint32 moveTime; float fromX, fromY, targetX, targetY;
public:
  float x, y;
  GTGTile *tileLeft, *tileRight, *tileUp, *tileDown;
  GTGTile *tileIdleLeft, *tileIdleRight, *tileIdleUp, *tileIdleDown;

  GTGPlayer(); ~GTGPlayer();
  void Construct(); void Destruct();
  const char *GetLastError();
  bool Load(const char *root, GTGTileSet *tileSet);
  SDL_Surface *GetSurface();
  void Frame(SDLTimer *timer);

  void GoLeft(SDLTimer *timer);
  void GoRight(SDLTimer *timer);
  void GoUp(SDLTimer *timer);
  void GoDown(SDLTimer *timer);
};

#endif
