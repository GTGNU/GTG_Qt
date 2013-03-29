#include "Row.h"

#include "Map.h"

gtg::Row::Row(QQuickItem* parent)
	: QQuickItem(parent)
{
	setFlag(QQuickItem::ItemHasContents);

	m_mapY = qobject_cast<Map*>(parent)->indexOf(this);
}

gtg::Row::~Row()
{
}


int gtg::Row::mapY() const
{
	return m_mapY;
}


QQmlListProperty<gtg::Tile*> gtg::Row::tiles() const
{
	return m_tiles;
}


int gtg::Row::indexOf(Tile* object)
{
	int count = m_tiles.count(&m_tiles);

	for (int i = 0; i < count; i++) {
		if (*m_tiles.at(&m_tiles, i) == object)
			return i;
	}

	return -1;
}
