#include "Row.h"
#include "Map.h"
#include "Tile.h"

#include <QtQuick/QQuickWindow>

#include <QtQuick/QSGSimpleRectNode>

QDebug& operator<<(QDebug& dbg, gtg::Row* row)
{
	dbg.nospace()
		<< "Row { parentItem:"
			<< QString(row->parentItem()->metaObject()->className())
			+ "(" + QString::number((int)row->parentItem(), 16) + ")"

		<< ", window:"
			<< QString(row->window()->metaObject()->className())
			+ "(" + QString::number((int)row->window(), 16) + ")"

		<< "}";

	return dbg.space();
}


gtg::Row::Row(QQuickItem* parent)
	: QQuickItem(parent)
	, m_tiles(this)
{
	setFlag(QQuickItem::ItemHasContents);
}

gtg::Row::~Row()
{
}


int gtg::Row::x() const
{
	return 0;
}

int gtg::Row::y() const
{
	return mapY() * map()->tileSize();
}

int gtg::Row::width() const
{
	return m_tiles.size() * map()->tileSize();
}

int gtg::Row::height() const
{
	return m_tiles.size() ? m_tiles.at(0)->height() : 0;
}

QRectF gtg::Row::boundingRect() const
{
	return QRect(x(), y(), width(), height());
}


int gtg::Row::mapY() const
{
	return map()->indexOf(this);
}

gtg::Map* gtg::Row::map() const
{
	return qobject_cast<Map*>(parentItem());
}


gtg::ChildList<gtg::Tile> gtg::Row::tiles() const
{
	return m_tiles;
}

QQmlListProperty<gtg::Tile> gtg::Row::qmlTiles()
{
	return m_tiles.toQmlListProperty();
}


int gtg::Row::indexOf(const Tile* object) const
{
	int i = 0;

	for (QQuickItem* tile : m_tiles) {
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
	qDebug() << "----------------------------------------";
	qDebug() << "Drawing " << this;
	qDebug() << "Children:";

	for (auto child : childItems()) {
		child->update();
		qDebug() << child;
	}

	QSGSimpleRectNode* n = static_cast<QSGSimpleRectNode*>(node);

	if (!n) {
		n = new QSGSimpleRectNode;

		int tileSize = map()->tileSize();
		setX(0);
		setY(mapY() * tileSize);
		setWidth(m_tiles.size() * tileSize);
		setHeight(tileSize);
	}

	qDebug() << "Bounding rect: " << boundingRect();

	n->setRect(boundingRect());

	return n;
}
