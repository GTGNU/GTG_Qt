#ifndef ROW_H
#define ROW_H

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

#include "ListFunctions.h"

namespace gtg
{
	class Tile;

	class Row
		: public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(int mapY READ mapY)
		Q_PROPERTY(QQmlListProperty<gtg::Tile> tiles READ qmlTiles)
		Q_CLASSINFO("DefaultProperty", "tiles")

		private:
			QQmlListPropertyHelper<Tile*> m_tiles;

			int m_mapY;

			QSGNode* updatePaintNode(QSGNode* node,
					QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

		public:
			Row(QQuickItem* parent = nullptr);
			~Row();

			int mapY() const;

			QQmlListProperty<gtg::Tile> qmlTiles();

			int indexOf(const Tile* object) const;

			friend class Map;
	};
}

QML_DECLARE_TYPE(gtg::Row)

#endif
