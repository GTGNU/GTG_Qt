#ifndef MAP_H
#define MAP_H

#include <QtQuick/QQuickItem>

namespace gtg
{
	class Row;
	class Tile;

	class Map
		: public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(QQmlListProperty<gtg::Row*> rows READ rows)
		Q_CLASSINFO("DefaultProperty", "rows")

		private:
			QQmlListProperty<Row*> m_rows;

		public:
			Map(QQuickItem* parent);
			~Map();

			QQmlListProperty<Tile*> rows();
	};
}

#endif
