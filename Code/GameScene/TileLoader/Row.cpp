#include "Row.h"
#include "Map.h"
#include "Tile.h"

#include "ListFunctions.h"

#include <QtQuick/QQuickWindow>

#include <QtQuick/QSGSimpleRectNode>

gtg::Row::Row(QQuickItem* parent)
	: QQuickItem(parent)
{
	setFlag(QQuickItem::ItemHasContents);
}

gtg::Row::~Row()
{
}


int gtg::Row::mapY() const
{
	return qobject_cast<Map*>(parentItem())->indexOf(this);
}


QQmlListProperty<gtg::Tile> gtg::Row::qmlTiles()
{
	return QQmlListProperty<Tile>(this,
			&m_tiles,
			qqmllistproperty_append<Tile>,
			qqmllistproperty_count<Tile>,
			qqmllistproperty_at<Tile>,
			qqmllistproperty_clear<Tile>);
}


int gtg::Row::indexOf(const Tile* object) const
{
	int i = 0;

	for (Tile* tile : m_tiles) {
		if (tile == object)
			return i;
		else
			i++;
	}

	return -1;
}


QSGNode* gtg::Row::updatePaintNode(QSGNode* node,
		QQuickItem::UpdatePaintNodeData* updatePaintNodeData)
{
	QSGSimpleRectNode* n = static_cast<QSGSimpleRectNode*>(node);

	if (!n) n = new QSGSimpleRectNode;

	n->setRect(boundingRect());

	qDebug() << "bounding rect: " << boundingRect();

	return n;
}
