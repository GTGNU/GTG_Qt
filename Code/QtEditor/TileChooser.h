#pragma once

#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtCore/QDir>
#include <QtCore/QVector>
#include <QtWidgets/QPushButton>

#include "Tile.h"

class TileChooser : public QPushButton
{
	Q_OBJECT

public:
	TileChooser(const QString& path);

	const Tile* getCurrentTile() const;

protected:
	int currentTileIndex;

	QVector<const Tile*> tileList;

public slots:
	void releasedHandler();
};
