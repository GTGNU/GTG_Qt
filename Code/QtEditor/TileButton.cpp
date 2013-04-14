#pragma once

#include "TileButton.h"

TileButton::TileButton(const TileChooser* chooser) : tileChooser(chooser)
{
	this->setIcon(*(this->tileChooser->getCurrentTile()->getIcon()));
	this->setIconSize(QSize(64, 64));
	this->setFixedSize(64, 64);

	this->connect(this, SIGNAL(released()), SLOT(releasedHandler()));
}

void TileButton::releasedHandler()
{
	this->setIcon(*(this->tileChooser->getCurrentTile()->getIcon()));
}
