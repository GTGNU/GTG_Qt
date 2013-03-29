#ifndef MAP_H
#define MAP_H

#include <QtQml/QQmlListProperty>

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
			Map(QQuickItem* parent = nullptr);
			~Map();

			QQmlListProperty<Row*> rows() const;

			int indexOf(const Row* object);

			Tile* tileAt(int x, int y);
	};
}

QML_DECLARE_TYPE(gtg::Map)

#endif
