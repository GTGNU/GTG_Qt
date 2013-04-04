/*
 * Copyright 2013 xcv_
 *
 * This file is part of Grand Theft Gentoo.
 *
 * Foobar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3.
 *
 * Grand Theft Gentoo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Grand Theft Gentoo.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Map.h"
#include "Row.h"
#include "Tile.h"
#include "TileView.h"

#include <QtQuick/QSGNode>
#include <QtQuick/QSGSimpleRectNode>

QDebug& operator<<(QDebug& dbg, gtg::Map* map)
{
	return dbg
		<< "Map { parentItem:"
			<< QString(map->parentItem()->metaObject()->className())
			+ "(" + QString::number((uintptr_t)map->parentItem(), 16) + ")"

		<< ", rows:" << map->rows().size()

		<< ", window:"
			<< QString(map->window()->metaObject()->className())
			+ "(" + QString::number((uintptr_t)map->window(), 16) + ")"

		<< "}";
}

gtg::Map::Map(QQuickItem* parent)
	: QQuickItem(parent)
	, m_rows(this)
{
	setFlag(QQuickItem::ItemHasContents);
}

gtg::Map::~Map()
{
}


unsigned int gtg::Map::tileSize() const
{
	return m_tileSize;
}

void gtg::Map::setTileSize(unsigned int tileSize)
{
	m_tileSize = tileSize;
}


gtg::ChildList<gtg::Row> gtg::Map::rows() const
{
	return m_rows;
}

QQmlListProperty<gtg::Row> gtg::Map::qmlRows()
{
	return m_rows.toQmlListProperty();
}


int gtg::Map::indexOf(const Row* object) const
{
	int i = 0;
	for (QQuickItem* row : m_rows) {
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


QSGNode* gtg::Map::updatePaintNode(QSGNode* node,
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

	if (!n)
		n = new QSGSimpleRectNode;

	setWidth(m_rows.at(0)->width());
	setHeight(m_rows.size() * tileSize());

	qDebug() << "Bounding rect: " << boundingRect();

	n->setRect(boundingRect());

	return n;
}
