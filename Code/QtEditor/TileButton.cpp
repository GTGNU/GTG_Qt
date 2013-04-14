#include "TileButton.h"

TileButton::TileButton(const TileChooser* chooser) : tileChooser(chooser)
{
	this->tile = this->tileChooser->getCurrentTile();

	this->setIcon(*(this->tile->getIcon()));
	this->setIconSize(QSize(TILE_WIDTH, TILE_HEIGHT));
	this->setFixedSize(TILE_WIDTH, TILE_HEIGHT);

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
