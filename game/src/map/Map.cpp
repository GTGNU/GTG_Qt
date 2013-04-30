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

#include <utility>

#include <QtQuick/QSGNode>
#include <QtQuick/QSGSimpleRectNode>

#include "Row.h"
#include "Tile.h"

#include "gfx/Texture.h"

#include "util/QmlListAdapter.h"
#include "util/qmlengine.h"


using gtg::map::Tile;
using gtg::map::Row;
using gtg::map::Map;

using gtg::ChildList;


Map::Map(QQuickItem* parent)
	: QQuickItem(parent)
	, m_requiresSet(false)
	, m_rows(this)
{
	setFlag(QQuickItem::ItemHasContents);
}

Map::~Map()
{
}


QStringList Map::requires() const
{
	return m_requires;
}

void Map::setRequires(QStringList requires)
{
	if (!m_requiresSet) {
		m_requires = std::move(requires);
		m_requiresSet = true;

		for (auto& requirement : m_requires)
			gtg::qmlengine::loadDefinition(requirement);

	} else {
		qWarning() << "Map: 'requires' is read-only";
	}
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

QQmlListProperty<Row> Map::rowsQml()
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



QSGNode* Map::updatePaintNode(QSGNode* node, QQuickItem::UpdatePaintNodeData*)
{
	/*qDebug() << "----------------------------------------";
	qDebug() << "Drawing " << this;*/

	QSGSimpleRectNode* n = static_cast<QSGSimpleRectNode*>(node);

	// First draw
	if (!n)
		n = new QSGSimpleRectNode;

	setWidth(m_rows.at(0)->width());
	setHeight(m_rows.count() * tileSize());

	n->setRect(boundingRect());

	return n;
}
