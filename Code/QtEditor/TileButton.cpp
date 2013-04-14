#pragma once

#include "TileButton.h"

TileButton::TileButton(const TileChooser* chooser) : tileChooser(chooser)
{
	this->tile = this->tileChooser->getCurrentTile();

	this->setIcon(*(this->tile->getIcon()));
	this->setIconSize(QSize(64, 64));
	this->setFixedSize(64, 64);

	this->connect(this, SIGNAL(released()), SLOT(releasedHandler()));
}

void TileButton::releasedHandler()
{
	this->tile = this->tileChooser->getCurrentTile();

	this->setIcon(*(this->tile->getIcon()));
}

const Tile* TileButton::getTile() const
{
	return this->tile;
}
