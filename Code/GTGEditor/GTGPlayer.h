#pragma once
#ifndef _GTGPLAYER_H_
#define _GTGPLAYER_H_

#include "SDLHelper.h"
#include <math.h>

class GTGMap;
class GTGTile;
class GTGPlayer{public:
  GTGTile *tileWalkLeft, *tileWalkRight, *tileWalkUp, *tileWalkDown;
  GTGTile *tileIdleLeft, *tileIdleRight, *tileIdleUp, *tileIdleDown;

  GTGTile *currentTile; bool isMoving;
  int x, y; float drawX, drawY; int prevX, prevY; Uint32 moveTime;

  friend class GTG;
  friend class GTGMap;
public:

  GTGPlayer(); ~GTGPlayer();
  void Construct(); void Destruct();
  void Frame(SDLTimer *timer, bool left, bool right, bool up, bool down, GTGMap *map);
  void Spawn(int px, int py);

};

#endif
