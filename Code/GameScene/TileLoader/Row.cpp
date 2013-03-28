#include "Row.h"

gtg::Row::Row(QQuickItem* parent)
	: QQuickItem(parent)
{
	setFlag(ItemHasContents);
}

gtg::Row::~Row()
{
}


QQmlListProperty<Tile*> gtg::Row::tiles() const
{
	return m_tiles;
}
