#ifndef TILECHOOSER_H
#define TILECHOOSER_H

#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtGui/QWheelEvent>
#include <QtCore/QDir>
#include <QtCore/QVector>
#include <QtWidgets/QPushButton>

#include "config.h"
#include "Tile.h"

namespace gtgeditor
{
	class TileChooser : public QPushButton
	{
		Q_OBJECT

	public:
		TileChooser(const QString& path);

		const Tile* getCurrentTile() const;
		const Tile* getTileByName(const QString& name) const;

	protected:
		int m_currentTileIndex;

		QVector<const Tile*> m_tileList;

		virtual void wheelEvent(QWheelEvent* event);

	public slots:
		void releasedHandler();
	};
}

#endif
