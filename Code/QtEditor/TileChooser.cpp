#include "TileChooser.h"

TileChooser::TileChooser(const QString& path) : currentTileIndex(0)
{
	QDir directory(path);

	for(	const QString& i
		: directory.entryList(QStringList("*.qml"), QDir::Files) ) {

		this->tileList.push_back(new Tile(path+"/"+i));
	}

	this->setIcon(*(this->tileList[this->currentTileIndex]->getIcon()));
	this->setIconSize(QSize(TILE_WIDTH, TILE_HEIGHT));

	this->connect(this, SIGNAL(released()), SLOT(releasedHandler()));
}

const Tile* TileChooser::getCurrentTile() const
{
	return this->tileList[this->currentTileIndex];
}

const Tile* TileChooser::getTileByName(const QString& name) const
{
	const Tile* result = NULL;

	for(int i = 0; i < this->tileList.size() && result == NULL; i++) {
		if(this->tileList[i]->getName() == name)
			result = this->tileList[i];
	}

	return result;
}

void TileChooser::wheelEvent(QWheelEvent* event)
{
	if(event->delta() < 0) {
		this->currentTileIndex
			= (this->currentTileIndex+1)%this->tileList.size();
	}
	else {
		if(this->currentTileIndex <= 0)
			this->currentTileIndex = this->tileList.size();

		this->currentTileIndex
			= this->currentTileIndex-1;
	}

	this->setIcon(*(this->tileList[this->currentTileIndex]->getIcon()));
}

void TileChooser::releasedHandler()
{
	this->currentTileIndex
		= (this->currentTileIndex+1)%this->tileList.size();

	this->setIcon(*(this->tileList[this->currentTileIndex]->getIcon()));
}
