#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include <QtCore/QEvent>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QApplication>
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
	const Tile* m_tile;
	const TileChooser* m_tileChooser;

	virtual void enterEvent(QEvent* event);
};

#endif
