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

#include "Entity.h"

#include <algorithm>
#include <cmath>

#include "map/Tile.h"
#include "map/Map.h"

#include "helpers/QmlListAdapter.h"


using gtg::floating::Entity;
using gtg::map::Map;
using gtg::map::Tile;


Entity::Entity(QQuickItem* parentItem)
	: QQuickItem(parentItem)
	, m_map(nullptr)
{
}

Entity::~Entity()
{
}


QList<Tile*> Entity::intersectingTiles() const
{
	QList<Tile*> tiles;
	Map* map = this->map();

	for (int x = mapX(); x < mapX2(); x++) {
		for (int y = mapY(); y < mapY2(); y++)
			tiles.push_back(map->tileAt(x,y));
	}

	return std::move(tiles);
}

QQmlListProperty<Tile> Entity::intersectingTilesQml()
{
	return gtg::qml_adapt<Tile>(intersectingTiles(), this);
}


Map* Entity::map() const
{
	return m_map? m_map : qobject_cast<Map*>(parentItem());
}

void Entity::setMap(Map* map)
{
	m_map = map;
}


int Entity::x() const
{
	return QQuickItem::x();
}

void Entity::setX(int x)
{
	int oldX = x();
	QQuickItem::setX(x);
	updateIntersectingTiles({oldX, y()}, {x(), y()});
}


int Entity::y() const
{
	return QQuickItem::y();
}

void Entity::setY(int y)
{
	int oldY = y();
	QQuickItem::setY(y);
	updateIntersectingTiles({x(), oldY}, {x(), y()});
}


int Entity::mapX() const
{
	return std::floor(double(x()) / map()->tileSize());
}

int Entity::mapX2() const
{
	return std::ceil((double(x()) + width()) / map()->tileSize());
}

int Entity::mapY() const
{
	return std::floor(double(y()) / map()->tileSize());
}

int Entity::mapY2() const
{
	return std::ceil((double(y()) + height()) / map()->tileSize());
}

int Entity::mapWidth() const
{
	return mapX2() - mapX();
}

int Entity::mapHeight() const
{
	return mapY2() - mapY();
}


bool Entity::intersects(Tile* tile) const
{
	return tile->boundingRect().intersects(boundingRect());
}


void Entity::move(int dx, int dy)
{
	// to get animations, this needs to be used instead of the setter
	setProperty("x", x() + dx);
	setProperty("y", y() + dy);
}

void Entity::move(QPoint p)
{
	move(p.x(), p.y());
}


void Entity::updateIntersectingTiles(int oldOriginValue,
		int oldBottomRightValue, bool isX)
{
	using namespace std;
	using namespace std::placeholders;

	QSet<Tile*> added, removed;

	int mx = mapX();
	int my = mapY();

	int mx2 = mapX2();
	int my2 = mapY2();

	auto getTile = bind(mem_fn(&Map::tileAt), map());

	if (isX) {
		updateIntersectingTiles(oldOriginValue, mx,
				bind(getTile, _1, my), true, added, removed);

		updateIntersectingTiles(oldBottomRightValue, mx2,
				bind(getTile, _1, my2), false, added, removed);

	} else {
		updateIntersectingTiles(oldOriginValue, my,
				bind(getTile, mx, _1), true, added, removed);

		updateIntersectingTiles(oldBottomRightValue, my2,
				bind(getTile, mx2, _1), false, added, removed);
	}

	for (Tile* t : removed)
		emit leftTile(t);

	for (Tile* t : added)
		emit enteredTile(t);
}

void Entity::updateIntersectingTiles(
		int oldMapCoord, int newMapCoord,
		std::function<Tile*(int)> getTile, bool atOrigin,
		QSet<Tile*>& removed, QSet<Tile*>& added)
{
	Tile* tmp;
	if (oldMapCoord < newMapCoord) {
		for (int mc = oldMapX; mc < newMapCoord; mc++) {
			tmp = getTile(mc);
			if (atOrigin) {
				m_intersectingTiles.remove(tmp);
				removed.insert(tmp);
			} else {
				m_intersectingTiles.insert(tmp);
				added.insert(tmp);
			}
		}
	} else if (oldMapCoord > newMapCoord) {
		for (int mc = newMapCoord; mc < oldMapCoord; mc++) {
			tmp = getTile(mc);
			if (atOrigin) {
				m_intersectingTiles.insert(tmp);
				added.insert(tmp);
			} else {
				m_intersectingTiles.remove(tmp);
				removed.insert(tmp);
			}
		}
	}
}

QSGNode* Entity::updatePaintNode(QSGNode* node,
		QQuickItem::UpdatePaintNodeData* updatePaintNodeData)
{
	qDebug() << "----------------------------------------";
	qDebug() << "Drawing " << this;

	// First draw, we need to initialize the node and set the geometry
	if (!node)
		node = new QSGNode;

	// Delegate drawing to the layer stack
	m_layers.applyChanges(node);
	m_layers.updateNode(node);

	return node;
}
