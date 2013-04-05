#pragma once
#ifndef _GTGPROJECTILE_H_
#define _GTGPROJECTILE_H_

#include <vector>
#include "SDLHelper.h"

class GTGProjectile
{
public:
	GTGProjectile(	SDL_Surface* screen,
			std::vector<SDL_Surface*> frameList,
			int x,
			int y,
			int damage = 1,
			int speed = 1,
			int acceleration = 0,
			int frameDelay = 50 );

	void Draw();

protected:
	SDL_Surface* screen;
	int x;
	int y;
	float xOffset;
	float yOffset;
	int damage;
	int speed; // Pixels per frame delay
	double acceleration;
	int frameDrawCount; // Number of times the current frame has been drawn
	int frameDelay;
	int frameIndex;
	std::vector<SDL_Surface*> frameList;

	int GetDamage();
	int GetSpeed();
	int GetAcceleration();
	int GetXOffset();
	int GetYOffset();
};

#endif
