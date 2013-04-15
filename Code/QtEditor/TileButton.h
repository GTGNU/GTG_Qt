#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include <QtWidgets/QPushButton>
#include <QtGui/QIcon>

#include "config.h"
#include "TileChooser.h"

class TileButton : public QPushButton
{
public:
	TileButton(const TileChooser* chooser);

	void setTile(const Tile* tile);
	const Tile* getTile() const;

protected:
	const Tile* tile;
	const TileChooser* tileChooser;
};

#endif
