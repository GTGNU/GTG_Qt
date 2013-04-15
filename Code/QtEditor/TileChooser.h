#ifndef TILECHOOSER_H
#define TILECHOOSER_H

#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtCore/QDir>
#include <QtCore/QVector>
#include <QtWidgets/QPushButton>

#include "config.h"
#include "Tile.h"

class TileChooser : public QPushButton
{
	Q_OBJECT

public:
	TileChooser(const QString& path);

	const Tile* getCurrentTile() const;
	const Tile* getTileByName(const QString& name) const;

protected:
	int currentTileIndex;

	QVector<const Tile*> tileList;

public slots:
	void releasedHandler();
};

#endif
