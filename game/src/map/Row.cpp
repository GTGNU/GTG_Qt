/*
 * Copyright 2013 xcv_
 *
 * This file is part of Grand Theft Gentoo.
 *
 * Grand Theft Gentoo is free software: you can redistribute it and/or modify
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

#include "Row.h"

#include <QtQuick/QQuickWindow>
#include <QtQuick/QSGSimpleRectNode>

#include "Tile.h"
#include "Map.h"

#include "util/QmlListAdapter.h"

using gtg::map::Tile;
using gtg::map::Row;
using gtg::map::Map;

using gtg::ChildList;


Row::Row(QQuickItem* parent)
	: QQuickItem(parent)
	, m_tiles(this)
{
	setFlag(QQuickItem::ItemHasContents);
}

Row::~Row()
{
}


int Row::x() const
{
	return 0;
}

int Row::y() const
{
	return mapY() * map()->tileSize();
}

int Row::width() const
{
	return m_tiles.count() * map()->tileSize();
}

int Row::height() const
{
	return m_tiles.count() ? m_tiles.at(0)->height() : 0;
}

QRectF Row::boundingRect() const
{
	return QRect(x(), y(), width(), height());
}


int Row::mapY() const
{
	return map()->indexOf(this);
}

Map* Row::map() const
{
	return qobject_cast<Map*>(parentItem());
}


ChildList<Tile> Row::tiles() const
{
	return m_tiles;
}

QQmlListProperty<Tile> Row::tilesQml()
{
	return gtg::qml_adapt<Tile>(m_tiles, this);
}


int Row::indexOf(const Tile* object) const
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



QSGNode* Row::updatePaintNode(QSGNode* node, QQuickItem::UpdatePaintNodeData*)
{
	/*qDebug() << "----------------------------------------";
	qDebug() << "Drawing " << this;*/

	QSGSimpleRectNode* n = static_cast<QSGSimpleRectNode*>(node);

	// First draw
	if (!n) {
		n = new QSGSimpleRectNode;

		int tileSize = map()->tileSize();
		setX(0);
		setY(mapY() * tileSize);
		setWidth(m_tiles.count() * tileSize);
		setHeight(tileSize);
	}

	//qDebug() << "Bounding rect: " << boundingRect();

	n->setRect(boundingRect());

	return n;
}
