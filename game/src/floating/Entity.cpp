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

#include <QtCore/QTimer>

#include <QtQuick/QSGNode>

#include "map/Tile.h"
#include "map/Map.h"

#include "util/QmlListAdapter.h"


using gtg::floating::Entity;

using gtg::map::Map;
using gtg::map::Tile;

using gtg::gfx::Layer;
using gtg::gfx::LayerStack;

using gtg::Registry;


Entity::Entity(QString type, QQuickItem* parentItem)
	: QQuickItem(parentItem)
	, Registered()
	, m_layers(this)

	, m_type(type)
	, m_map(nullptr)
{
	setFlag(QQuickItem::ItemHasContents);
}

Entity::~Entity()
{
}


const LayerStack* Entity::layers() const
{
	return &m_layers;
}

LayerStack* Entity::layers()
{
	return &m_layers;
}

QQmlListProperty<Layer> Entity::layersQml()
{
	return gtg::qml_adapt<Layer>(m_layers, this);
}


QTimer* Entity::timer() const
{
	static QTimer timer;
	return &timer;
}


QString Entity::type() const
{
	return m_type;
}


Map* Entity::map() const
{
	return m_map? m_map : qobject_cast<Map*>(parentItem());
}

void Entity::setMap(Map* map)
{
	m_map = map;
}


int Entity::tiledX() const
{
	return std::floor(x() / map()->tileSize());
}

int Entity::tiledX2() const
{
	return std::ceil((x() + width()) / map()->tileSize());
}

int Entity::tiledY() const
{
	return std::floor(y() / map()->tileSize());
}

int Entity::tiledY2() const
{
	return std::ceil((y() + height()) / map()->tileSize());
}

int Entity::tiledWidth() const
{
	return tiledX2() - tiledX();
}

int Entity::tiledHeight() const
{
	return tiledY2() - tiledY();
}


bool Entity::intersects(Entity* tile) const
{
	return tile->boundingRect().intersects(boundingRect());
}

bool Entity::intersectsTile(int x, int y) const
{
	return QRect(
			QPoint(tiledX(), tiledY()),
			QPoint(tiledX2(), tiledY2()))
					.intersects({x,y,1,1});
}


QSGNode* Entity::updatePaintNode(QSGNode* node, QQuickItem::UpdatePaintNodeData*)
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
