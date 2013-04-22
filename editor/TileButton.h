#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include <QtCore/QEvent>
#include <QtWidgets/QApplication>
#include <QtGui/QIcon>
#include <QtGui/QPainter>

#include "config.h"
#include "TileChooser.h"

namespace gtgeditor
{
	class TileButton : public QAbstractButton
	{
	public:
		TileButton(const TileChooser* chooser);

		void setTile(const Tile* tile);
		const Tile* getTile() const;

	protected:
		const Tile* m_tile;
		const TileChooser* m_tileChooser;

		virtual void enterEvent(QEvent* event);
		virtual void paintEvent(QPaintEvent* event);
	};
}

#endif
