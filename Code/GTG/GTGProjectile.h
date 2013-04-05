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
	float xSpeed; // Pixels per frame delay
	float ySpeed;

	GTGProjectile(	SDL_Surface* screen,
			std::vector<SDL_Surface*> frameList,
			int x,
			int y,
			int cooldown = 30,
			int damage = 1,
			float xSpeed = 10,
			float ySpeed = 0,
			float xAcceleration = 0,
			float yAcceleration = 0,
			int frameDelay = 10 );

	void Draw();
	void Fire();

	// Accessors
	bool GetFired();
	int GetXOffset();
	int GetYOffset();
	int GetDamage();
	int GetXAcceleration();
	int GetYAcceleration();
protected:
	SDL_Surface* screen;
	bool fired;
	float xOffset;
	float yOffset;
	int cooldownCount;
	int cooldown;
	int damage;
	float xSpeedOffset;
	float ySpeedOffset;
	float xAcceleration;
	float yAcceleration;
	int frameDrawCount; // Number of times the current frame has been drawn
	int frameDelay;
	int frameIndex;
	std::vector<SDL_Surface*> frameList;

	void Reset();
};

#endif
