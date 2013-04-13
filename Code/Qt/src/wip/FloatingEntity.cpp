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

#include "FloatingEntity.h"

#include <algorithm>
#include <cmath>

#include "Tile.h"
#include "Map.h"

#include "helpers/QmlListAdapter.h"


using gtg::FloatingEntity;
using gtg::Map;
using gtg::Tile;


FloatingEntity::FloatingEntity(QQuickItem* parentItem)
	: QQuickItem(parentItem)
	, m_map(nullptr)
{
}

FloatingEntity::~FloatingEntity()
{
}


QList<Tile*> FloatingEntity::intersectingTiles() const
{
	QList<Tile*> tiles;
	Map* map = this->map();

	for (int x = mapX(); x < mapX2(); x++) {
		for (int y = mapY(); y < mapY2(); y++)
			tiles.push_back(map->tileAt(x,y));
	}

	return std::move(tiles);
}

QQmlListProperty<Tile> FloatingEntity::intersectingTilesQml()
{
	return gtg::qml_adapt<Tile>(intersectingTiles(), this);
}


Map* FloatingEntity::map() const
{
	return m_map? m_map : qobject_cast<Map*>(parentItem());
}

void FloatingEntity::setMap(Map* map)
{
	m_map = map;
}


int FloatingEntity::mapX() const
{
	return std::floor(double(x()) / map()->tileSize());
}

int FloatingEntity::mapX2() const
{
	return std::ceil((double(x()) + width()) / map()->tileSize());
}

int FloatingEntity::mapY() const
{
	return std::floor(double(y()) / map()->tileSize());
}

int FloatingEntity::mapY2() const
{
	return std::ceil((double(y()) + height()) / map()->tileSize());
}

int FloatingEntity::mapWidth() const
{
	return mapX2() - mapX();
}

int FloatingEntity::mapHeight() const
{
	return mapY2() - mapY();
}


bool FloatingEntity::intersects(gtg::Tile* tile) const
{
	return tile->boundingRect().intersects(boundingRect());
}


void FloatingEntity::move(int dx, int dy)
{
	setX(x() + dx);
	setY(y() + dy);
}

void FloatingEntity::move(QPoint p)
{
	move(p.x(), p.y());
}


QSGNode* FloatingEntity::updatePaintNode(QSGNode* node,
		QQuickItem::UpdatePaintNodeData* updatePaintNodeData)
{

}
