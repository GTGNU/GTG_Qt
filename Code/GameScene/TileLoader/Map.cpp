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


QQmlListProperty<gtg::Row> gtg::Map::qmlRows()
{
	return QQmlListProperty<Row>(this,
			&m_rows,
			qqmllistproperty_append<Row>,
			qqmllistproperty_count<Row>,
			qqmllistproperty_at<Row>,
			qqmllistproperty_clear<Row>);
}


int gtg::Map::indexOf(const Row* object) const
{
	int i = 0;
	for (Row* row : m_rows) {
		if (row == object)
			return i;
		else
			i++;
	}

	return -1;
}


gtg::Tile* gtg::Map::tileAt(int x, int y)
{
	return m_rows.at(y)->m_tiles.at(x);
}

