#ifndef MAP_H
#define MAP_H

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

#include "ListFunctions.h"

namespace gtg
{
	class Tile;
	class Row;

	class Map
	: public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(QQmlListProperty<gtg::Row> rows READ qmlRows)
		Q_CLASSINFO("DefaultProperty", "rows")

		private:
			QQmlListPropertyHelper<Row*> m_rows;

		public:
			Map(QQuickItem* parent = nullptr);
			~Map();

			QQmlListProperty<gtg::Row> qmlRows();

			int indexOf(const Row* object) const;

			Q_INVOKABLE Tile* tileAt(int x, int y);
	};
}

QML_DECLARE_TYPE(gtg::Map)

#endif
