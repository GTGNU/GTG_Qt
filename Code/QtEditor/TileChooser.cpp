#include "TileChooser.h"

TileChooser::TileChooser(const QString& path) : currentTileIndex(0)
{
	QDir directory(path);

	for(const QString& i : directory.entryList(QDir::Files))
	{
		QPixmap pixmap(path+"/"+i);

		QIcon* icon = new QIcon(pixmap.copy(64, 64, 64, 64));

		this->tileList.push_back(icon);
	}

	this->setIcon(*(this->tileList[this->currentTileIndex]));
	this->setIconSize(QSize(64, 64));
	this->setFixedSize(80, 80);

	this->connect(this, SIGNAL(released()), SLOT(releasedHandler()));
}

const QIcon* TileChooser::getCurrentTile() const
{
	return this->tileList[this->currentTileIndex];
}

void TileChooser::releasedHandler()
{
	this->currentTileIndex
		= (this->currentTileIndex+1)%this->tileList.size();

	this->setIcon(*(this->tileList[this->currentTileIndex]));
}
