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
			float xSpeed = 10,
			float ySpeed = 0,
			float xAcceleration = 0,
			float yAcceleration = 0,
			int frameDelay = 10 );

	void Draw();
	void Fire();

protected:
	SDL_Surface* screen;
	bool fired;
	int x;
	int y;
	float xOffset;
	float yOffset;
	int damage;
	float xSpeed; // Pixels per frame delay
	float ySpeed;
	float xAcceleration;
	float yAcceleration;
	int frameDrawCount; // Number of times the current frame has been drawn
	int frameDelay;
	int frameIndex;
	std::vector<SDL_Surface*> frameList;

	// Accessors
	int GetX();
	int GetY();
	int GetXOffset();
	int GetYOffset();
	int GetDamage();
	int GetXSpeed();
	int GetYSpeed();
	int GetXAcceleration();
	int GetYAcceleration();
};

#endif
