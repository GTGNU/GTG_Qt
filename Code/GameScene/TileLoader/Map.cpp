#include "Map.h"

#include "Row.h"

gtg::Map::Map(QQuickItem* parent)
	: QQuickItem(parent)
{
	setFlag(QQuickItem::ItemHasContents);
}

gtg::Map::~Map()
{
}


QQmlListProperty<gtg::Row*> gtg::Map::rows() const
{
	return m_rows;
}


int gtg::Map::indexOf(const Row* object)
{
	int count = m_rows.count(&m_rows);

	for (int i = 0; i < count; i++) {
		if (*m_rows.at(&m_rows, i) == object)
			return i;
	}

	return -1;
}


gtg::Tile* gtg::Map::tileAt(int x, int y)
{
	Row* row = *m_rows.at(&m_rows, y);
	return *row->m_tiles.at(&row->m_tiles, x);
}

