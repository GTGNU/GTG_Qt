#ifndef MAP_H
#define MAP_H

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

#include "ChildList.h"

namespace gtg
{
	class Tile;
	class Row;

	class Map
	: public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(unsigned int tileSize READ tileSize WRITE setTileSize)

		Q_PROPERTY(QQmlListProperty<gtg::Row> rows READ qmlRows)
		Q_CLASSINFO("DefaultProperty", "rows")

		private:
			unsigned int m_tileSize;
			ChildList<Row> m_rows;

			QSGNode* updatePaintNode(QSGNode* node,
					QQuickItem::UpdatePaintNodeData* updatePaintNodeData) override;

		public:
			Map(QQuickItem* parent = nullptr);
			~Map();

			unsigned int tileSize() const;
			void setTileSize(unsigned int tileSize);

			ChildList<gtg::Row> rows() const;
			QQmlListProperty<gtg::Row> qmlRows();

			int indexOf(const Row* object) const;

			Q_INVOKABLE Tile* tileAt(int x, int y);
	};
}

QML_DECLARE_TYPE(gtg::Map)

#endif
