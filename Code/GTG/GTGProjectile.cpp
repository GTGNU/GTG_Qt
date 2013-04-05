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

:frameDrawCount(0), frameIndex(0)
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
	this->xOffset += this->xSpeed;
	this->yOffset += this->ySpeed;

	this->xSpeed += this->xAcceleration;
	this->ySpeed += this->yAcceleration;

	if(++(this->frameDrawCount) >= this->frameDelay)
	{
		this->frameIndex = (this->frameIndex+1)%this->frameList.size();

		this->frameDrawCount = 0;
	}


	SDLBlit(	this->frameList[this->frameIndex],
			this->screen,
			this->x+this->xOffset,
			this->y+this->yOffset );
}

// Accessors
int GTGProjectile::GetX()
{
	return this->x;
}

int GTGProjectile::GetY()
{
	return this->y;
}

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

int GTGProjectile::GetXSpeed()
{
	return this->xSpeed;
}

int GTGProjectile::GetYSpeed()
{
	return this->ySpeed;
}

int GTGProjectile::GetXAcceleration()
{
	return this->xAcceleration;
}

int GTGProjectile::GetYAcceleration()
{
	return this->yAcceleration;
}
