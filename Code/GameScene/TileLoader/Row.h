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
		Q_PROPERTY(QQmlListProperty<gtg::Tile*> tiles READ tiles)
		Q_CLASSINFO("DefaultProperty", "tiles")

		private:
			QQmlListProperty<Tile*> m_tiles;

		public:
			Row(QQuickItem* parent);
			~Row();

			QQmlListProperty<Tile*> tiles() const;
	};
}

Q_DECLARE_METATYPE(gtg::Row)

#endif
