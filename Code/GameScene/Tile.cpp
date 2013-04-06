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

#include "Tile.h"
#include "Row.h"
#include "Map.h"

#include "TileType.h"
#include "TileView.h"
#include "TileBehavior.h"

#include "QmlListAdapter.h"

#include <QtGui/QImage>

#include <QtQuick/QSGNode>
#include <QtQuick/QSGTexture>
#include <QtQuick/QQuickWindow>

QDebug& operator<<(QDebug& dbg, gtg::Tile* tile)
{
	return dbg
		<< "Tile { parentItem:"
			<< QString(tile->parentItem()->metaObject()->className())
			+ "(" + QString::number((uintptr_t)tile->parentItem(), 16) + ")"

		<< ", window:"
			<< QString(tile->window()->metaObject()->className())
			+ "(" + QString::number((uintptr_t)tile->window(), 16) + ")"

		<< "}";
}

gtg::Tile::Tile(QQuickItem* parent)
	: QQuickItem(parent)
	, m_views(this)
	, m_behavior(nullptr)
{
	qDebug() << "Tile()";
	setFlag(QQuickItem::ItemHasContents);
}

gtg::Tile::~Tile()
{
}


QQmlListProperty<gtg::ViewListEntry> gtg::Tile::viewsQml()
{
	return adapt<ViewListEntry>(m_views, this);
}


gtg::TileBehavior* gtg::Tile::behavior() const
{
	return m_behavior;
}

void gtg::Tile::setBehavior(TileBehavior* behavior)
{
	if (m_behavior != behavior) {
		TileBehavior* prev = m_behavior;
		m_behavior = behavior;
		emit behaviorChanged(prev, m_behavior);
	}
}


int gtg::Tile::mapX() const
{
	return qobject_cast<const Row*>(parentItem())->indexOf(this);
}

int gtg::Tile::mapY() const
{
	return qobject_cast<const Row*>(parentItem())->mapY();
}


gtg::Row* gtg::Tile::row() const
{
	return qobject_cast<Row*>(parentItem());
}

gtg::Map* gtg::Tile::map() const
{
	return row()->map();
}


void gtg::Tile::setPlayer(Player* player)
{
	if (m_player)
		emit playerExited(m_player);

	m_player = player;

	if (m_player)
		emit playerEntered(m_player);
}

QSGNode* gtg::Tile::updatePaintNode(QSGNode* node,
		QQuickItem::UpdatePaintNodeData* updatePaintNodeData)
{
	qDebug() << "----------------------------------------";
	qDebug() << "Drawing " << this;

	if (!node) {
		node = new QSGNode;

		int tileSize = map()->tileSize();
		setX(mapX() * tileSize);
		setY(0); // relative to row
		setWidth(tileSize);
		setHeight(tileSize);
	}

	qDebug() << "Bounding rect: " << boundingRect();

	m_views.applyChanges(node);
	m_views.updateNode(node);

	return node;
}

