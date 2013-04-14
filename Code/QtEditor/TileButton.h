#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include <QtWidgets/QPushButton>
#include <QtGui/QIcon>

#include "TileChooser.h"

class TileButton : public QPushButton
{
	Q_OBJECT

public:
	TileButton(const TileChooser* chooser);

	const Tile* getTile() const;

protected:
	const Tile* tile;
	const TileChooser* tileChooser;

public slots:
	void releasedHandler();
};

#endif
