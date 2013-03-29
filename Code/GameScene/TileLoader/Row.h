#ifndef ROW_H
#define ROW_H

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

namespace gtg
{
	class Tile;

	class Row
		: public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(int mapY READ mapY)
		Q_PROPERTY(QQmlListProperty<gtg::Tile*> tiles READ tiles)
		Q_CLASSINFO("DefaultProperty", "tiles")

		private:
			QQmlListProperty<Tile*> m_tiles;

			int m_mapY;

		public:
			Row(QQuickItem* parent = nullptr);
			~Row();

			int mapY() const;

			QQmlListProperty<Tile*> tiles() const;

			int indexOf(Tile* object);

			friend class Map;
	};
}

QML_DECLARE_TYPE(gtg::Row)

#endif
