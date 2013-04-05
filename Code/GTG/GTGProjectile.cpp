#include "GTGProjectile.h"

#include <iostream>

GTGProjectile::GTGProjectile(	SDL_Surface* screen,
				std::vector<SDL_Surface*> frameList,
				int x,
				int y,
				int damage,
				float xSpeed,
				float ySpeed,
				float xAcceleration,
				float yAcceleration,
				int frameDelay )

:	fired(false),
	xSpeedOffset(0),
	ySpeedOffset(0),
	frameDrawCount(0),
	frameIndex(0)
{
	this->screen = screen;
	this->frameList = frameList;
	this->x = x;
	this->y = y;
	this->damage = damage;
	this->xSpeed = xSpeed;
	this->ySpeed = ySpeed;
	this->xAcceleration = xAcceleration;
	this->yAcceleration = yAcceleration;
	this->frameDelay = frameDelay;
}

void GTGProjectile::Draw()
{
	if(this->fired)
	{
		this->xOffset += this->xSpeed+this->xSpeedOffset;
		this->yOffset += this->ySpeed+this->ySpeedOffset;

		this->xSpeedOffset += this->xAcceleration;
		this->ySpeedOffset += this->yAcceleration;

		if(++(this->frameDrawCount) >= this->frameDelay)
		{
			this->frameIndex =	(this->frameIndex+1)%
						this->frameList.size();

			this->frameDrawCount = 0;
		}


		SDLBlit(	this->frameList[this->frameIndex],
				this->screen,
				this->x+this->xOffset,
				this->y+this->yOffset );
	}
}

void GTGProjectile::Fire()
{
	if(!this->fired)
		this->fired = true;
}

void GTGProjectile::Reset()
{
	this->fired = false;
	this->xOffset = 0;
	this->yOffset = 0;
	this->xSpeedOffset = xSpeed;
	this->ySpeedOffset = ySpeed;
	this->frameDrawCount = 0;
	this->frameIndex = 0;
}

// Accessors
int GTGProjectile::GetXOffset()
{
	return this->xOffset;
}

int GTGProjectile::GetYOffset()
{
	return this->yOffset;
}

int GTGProjectile::GetDamage()
{
	return this->damage;
}

int GTGProjectile::GetXAcceleration()
{
	return this->xAcceleration;
}

int GTGProjectile::GetYAcceleration()
{
	return this->yAcceleration;
}
