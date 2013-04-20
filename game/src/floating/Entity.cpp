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

#include <QtQuick/QSGNode>

#include "map/Tile.h"
#include "map/Map.h"

#include "helpers/QmlListAdapter.h"


using gtg::floating::Entity;

using gtg::map::Map;
using gtg::map::Tile;

using gtg::gfx::Layer;

using gtg::Registry;


Entity::Entity(QString type, Registry* registry, QQuickItem* parentItem)
	: QQuickItem(parentItem)
	, Registered()
	, m_layers(this)
	, m_type(type)
	, m_map(nullptr)
{
}

Entity::~Entity()
{
}


Registry* Entity::registry() const
{
	static Registry reg {"Entity"};
	return &reg;
}


QQmlListProperty<Layer> Entity::layersQml()
{
	return gtg::qml_adapt<Layer>(m_layers, this);
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


QSGNode* Entity::updatePaintNode(QSGNode* node,
		QQuickItem::UpdatePaintNodeData* updatePaintNodeData)
{
	qDebug() << "----------------------------------------";
	qDebug() << "Drawing " << this;

	// First draw, we need to initialize the node and set the geometry
	if (!node) {
		node = new QSGNode;
	}

	// Delegate drawing to the layer stack
	m_layers.applyChanges(node);
	m_layers.updateNode(node);

	return node;
}
