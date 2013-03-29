#ifndef ROW_H
#define ROW_H

#include <QtCore/QRectF>

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

#include "ChildList.h"

namespace gtg
{
	class Tile;
	class Map;

	class Row
		: public QQuickItem
	{
		Q_OBJECT

		Q_PROPERTY(int mapY READ mapY)
		Q_PROPERTY(gtg::Map* map READ map)

		Q_PROPERTY(QQmlListProperty<gtg::Tile> tiles READ qmlTiles)
		Q_CLASSINFO("DefaultProperty", "tiles")

		private:
			ChildList<Tile> m_tiles;

			int m_mapY;

			QSGNode* updatePaintNode(QSGNode* node,
					QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

		public:
			Row(QQuickItem* parent = nullptr);
			~Row();

			int x() const;
			int y() const;
			int width() const;
			int height() const;
			QRectF boundingRect() const;

			int mapY() const;
			gtg::Map* map() const;

			ChildList<gtg::Tile> tiles() const;
			QQmlListProperty<gtg::Tile> qmlTiles();

			int indexOf(const Tile* object) const;

			friend class Map;
	};
}

QML_DECLARE_TYPE(gtg::Row)

#endif
