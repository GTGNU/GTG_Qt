#pragma once
#ifndef _GTGPROJECTILE_H_
#define _GTGPROJECTILE_H_

#include <vector>
#include "SDLHelper.h"

class GTGProjectile
{
public:
	int x;
	int y;

	GTGProjectile(	SDL_Surface* screen,
			std::vector<SDL_Surface*> frameList,
			int x,
			int y,
			int damage = 1,
			float xSpeed = 10,
			float ySpeed = 0,
			float xAcceleration = 0,
			float yAcceleration = 0,
			int frameDelay = 10 );

	void Draw();
	void Fire();
	void Reset();
protected:
	SDL_Surface* screen;
	bool fired;
	float xOffset;
	float yOffset;
	int damage;
	float xSpeed; // Pixels per frame delay
	float ySpeed;
	float xSpeedOffset;
	float ySpeedOffset;
	float xAcceleration;
	float yAcceleration;
	int frameDrawCount; // Number of times the current frame has been drawn
	int frameDelay;
	int frameIndex;
	std::vector<SDL_Surface*> frameList;

	// Accessors
	int GetXOffset();
	int GetYOffset();
	int GetDamage();
	int GetXSpeed();
	int GetYSpeed();
	int GetXAcceleration();
	int GetYAcceleration();
};

#endif
