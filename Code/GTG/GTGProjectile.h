#pragma once
#ifndef _GTGPROJECTILE_H_
#define _GTGPROJECTILE_H_

#include <vector>
#include "SDLHelper.h"

class GTGProjectile
{
public:
	int x; // Reference coordinates
	int y;
	float xSpeed; // Speed in pixels per frame delay
	float ySpeed;

	GTGProjectile(	SDL_Surface* screen,
			std::vector<SDL_Surface*> frameList,
			int x,
			int y,
			int cooldown = 60,
			int damage = 1,
			float xSpeed = 10,
			float ySpeed = 0,
			float xAcceleration = 0,
			float yAcceleration = 0,
			int frameDelay = 10 );

	void Draw(); // Draw the projectile on screen
	void Fire(); // Fire the projectile

	// Accessors
	bool GetReady() const;
	int GetXOffset() const;
	int GetYOffset() const
	int GetDamage() const;
	int GetXAcceleration() const;
	int GetYAcceleration() const;

protected:
	SDL_Surface* screen; // The screen to draw on
	bool fired; // Whether the projectile has been fired
	bool ready; // Whether the projectile is ready to be fired (again)
	float xOffset; // Distance from origin
	float yOffset;
	int cooldownCount; // Number of frames since last shot
	int cooldown; // Number of frames before becoming ready to fire again
	int damage; // Damage to inflict on target
	float xSpeedOffset; // Speed offset of reference speed
	float ySpeedOffset;
	float xAcceleration; // Acceration once fired
	float yAcceleration;
	int frameDrawCount; // Number of times the current frame has been drawn
	int frameDelay; // Delay between animation frames
	int frameIndex; // Index of the current animation frame
	std::vector<SDL_Surface*> frameList;

	void Reset();
};

#endif
