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

#include "Map.h"
#include <QtQuick/QSGNode>
#include <QtQuick/QSGSimpleRectNode>

#include "Row.h"
#include "Tile.h"
#include "tile/Texture.h"
#include "helpers/QmlListAdapter.h"


using gtg::Tile;
using gtg::Row;
using gtg::Map;

using gtg::ChildList;


Map::Map(QQuickItem* parent)
	: QQuickItem(parent)
	, m_rows(this)
{
	setFlag(QQuickItem::ItemHasContents);
}

Map::~Map()
{
}


unsigned int Map::tileSize() const
{
	return m_tileSize;
}

void Map::setTileSize(unsigned int tileSize)
{
	m_tileSize = tileSize;
}


ChildList<Row> Map::rows() const
{
	return m_rows;
}

QQmlListProperty<Row> Map::qmlRows()
{
	return gtg::qml_adapt<Row>(m_rows, this);
}


int Map::indexOf(const Row* object) const
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


Tile* Map::tileAt(int x, int y)
{
	return m_rows.at(y)->m_tiles.at(x);
}


QSGNode* Map::updatePaintNode(QSGNode* node,
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
	setHeight(m_rows.count() * tileSize());

	n->setRect(boundingRect());

	return n;
}
