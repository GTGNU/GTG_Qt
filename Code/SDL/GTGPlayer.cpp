#include "GTGPlayer.h"
#include "GTGTile.h"
#include "GTGMap.h"

GTGPlayer::GTGPlayer()
{
	Construct();
}

GTGPlayer::~GTGPlayer()
{
	Destruct();
}

void GTGPlayer::Construct()
{
	tileWalkLeft = NULL;
	tileWalkRight = NULL;
	tileWalkUp = NULL;
	tileWalkDown = NULL;
	tileIdleLeft = NULL;
	tileIdleRight = NULL;
	tileIdleUp = NULL;
	tileIdleDown = NULL;
	currentTile = NULL;
}

void GTGPlayer::Destruct()
{
	Construct();
}

void GTGPlayer::Frame(SDLTimer *timer, bool left, bool right, bool up, bool down, GTGMap *map)
{
	if(isMoving) {
		float d = (timer->now - moveTime)/400.;
		if(d > 1.) {
			isMoving = false;
			prevX = x;
			prevY = y;
			drawX = x;
			drawY = y;
			if(currentTile == tileWalkLeft)currentTile = tileIdleLeft;
			else if(currentTile == tileWalkRight)currentTile = tileIdleRight;
			else if(currentTile == tileWalkUp)currentTile = tileIdleUp;
			else if(currentTile == tileWalkDown)currentTile = tileIdleDown;
		} else {
			drawX = prevX + (float)(x - prevX)*sin(d);
			drawY = prevY + (float)(y - prevY)*sin(d);
		}
	} else {
		if(left) {
			prevX = x;
			prevY = y;
			if(map->IsSolid(x-1,y))return;
			x--;
			currentTile = tileWalkLeft;
			moveTime = timer->now;
			isMoving = true;
		} else if(right) {
			prevX = x;
			prevY = y;
			if(map->IsSolid(x+1,y))return;
			x++;
			currentTile = tileWalkRight;
			moveTime = timer->now;
			isMoving = true;
		} else if(up) {
			prevX = x;
			prevY = y;
			if(map->IsSolid(x,y-1))return;
			y--;
			currentTile = tileWalkUp;
			moveTime = timer->now;
			isMoving = true;
		} else if(down) {
			prevX = x;
			prevY = y;
			if(map->IsSolid(x,y+1))return;
			y++;
			currentTile = tileWalkDown;
			moveTime = timer->now;
			isMoving = true;
		}
	}
}

void GTGPlayer::Spawn(int px, int py)
{
	x = px;
	y = py;
	drawX = px;
	drawY = py;
	currentTile = tileIdleDown;
	prevX = px;
	prevY = py;
	moveTime = 0;
	isMoving = false;
}

GTGPlayer::Orientation GTGPlayer::GetOrientation()
{
	Orientation result;

	if(this->currentTile == this->tileWalkLeft
	|| this->currentTile == this->tileIdleLeft)
		result = LEFT;
	else if(this->currentTile == this->tileWalkRight
	|| this->currentTile == this->tileIdleRight)
		result = RIGHT;
	else if(this->currentTile == this->tileWalkUp
	|| this->currentTile == this->tileIdleUp)
		result = UP;
	else if(this->currentTile == this->tileWalkDown
	|| this->currentTile == this->tileIdleDown)
		result = DOWN;

	return result;
}
