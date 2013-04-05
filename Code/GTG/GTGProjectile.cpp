#include "GTGProjectile.h"

#include <iostream>

GTGProjectile::GTGProjectile(	SDL_Surface* screen,
				std::vector<SDL_Surface*> frameList,
				int x,
				int y,
				int damage,
				int speed,
				int acceleration,
				int frameDelay )
{
	this->screen = screen;
	this->frameList = frameList;
	this->x = x;
	this->y = y;
	this->damage = damage;
	this->speed = speed;
	this->acceleration = acceleration;
	this->frameDelay = frameDelay;
}

void GTGProjectile::Draw()
{
	//this->xOffset += this->speed;
	//this->yOffset += this->speed;

	this->speed += this->acceleration;

	if(++(this->frameDrawCount) >= this->frameDelay)
	{
		this->frameIndex = (this->frameIndex+1)%this->frameList.size();

		std::cerr << this->frameDelay << std::endl;
		this->frameDrawCount = 0;
	}


	SDLBlit(	this->frameList[this->frameIndex],
			this->screen,
			this->x+this->xOffset,
			this->y+this->yOffset );
}
