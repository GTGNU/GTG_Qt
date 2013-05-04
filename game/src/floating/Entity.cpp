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
#include <QtQuick/QSGSimpleRectNode>

#include "map/Tile.h"
#include "map/Map.h"

#include "util/QmlListAdapter.h"


using gtg::floating::Entity;

using gtg::map::Map;
using gtg::map::Tile;

using gtg::gfx::Layer;
using gtg::gfx::LayerStack;

using gtg::Registry;

Entity::Entity(QQuickItem* parentItem)
	: Entity("TestEntity", parentItem)
{
}

Entity::Entity(QString type, QQuickItem* parentItem)
	: QQuickItem(parentItem)
	, Registered()
	, m_layers(this)

	, m_type(type)
	, m_map(nullptr)
{
	setFlag(QQuickItem::ItemHasContents);

	connect(this, &QQuickItem::xChanged,
			this, &Entity::updateContainerTiles,
			Qt::DirectConnection);

	connect(this, &QQuickItem::yChanged,
			this, &Entity::updateContainerTiles,
			Qt::DirectConnection);

	connect(this, &QQuickItem::widthChanged,
			this, &Entity::updateContainerTiles,
			Qt::DirectConnection);

	connect(this, &QQuickItem::heightChanged,
			this, &Entity::updateContainerTiles,
			Qt::DirectConnection);
}

Entity::~Entity()
{
	disconnect(this, &QQuickItem::xChanged,
			this, &Entity::updateContainerTiles);

	disconnect(this, &QQuickItem::yChanged,
			this, &Entity::updateContainerTiles);

	disconnect(this, &QQuickItem::widthChanged,
			this, &Entity::updateContainerTiles);

	disconnect(this, &QQuickItem::heightChanged,
			this, &Entity::updateContainerTiles);

	registry()->unregisterObj(this);
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
	qDebug() << "Entity::layersQml()";
	return gtg::qml_adapt<Layer>(m_layers, this);
}


QTimer* Entity::timer() const
{
	qDebug() << "Entity::timer()";
	static QTimer timer;
	return &timer;
}

Registry* Entity::registry() const
{
	qDebug() << "Entity::registry()";
	static Registry* entityRegistry = new Registry("Class");
	return entityRegistry;
}


QString Entity::type() const
{
	qDebug() << "Entity::type()";
	return m_type;
}


Map* Entity::map() const
{
	qDebug() << "Entity::map()";
	return m_map? m_map : qobject_cast<Map*>(parentItem());
}

void Entity::setMap(Map* map)
{
	qDebug() << "Entity::setMap()";
	m_map = map;
}


QList<QObject*> Entity::containerTiles() const
{
	qDebug() << "Entity::containerTiles()";
	return m_containerTiles;
}


bool Entity::intersects(const QQuickItem* other) const
{
	return boundingRect().intersects(other->boundingRect());
}


void Entity::updateContainerTiles()
{
	qDebug() << "Entity::updateContainerTiles()";
	m_tiledRect.rect().setTopLeft({x(), y()});

	int newX = m_tiledRect.x();
	int newX2 = m_tiledRect.x2();

	int newY = m_tiledRect.y();
	int newY2 = m_tiledRect.y2();

	m_containerTiles.clear();

	for (int i = newX; i < newX2; i++) {
		for (int j = newY; j < newY2; j++)
			m_containerTiles << map()->tileAt(i, j);
	}
}


QSGNode* Entity::updatePaintNode(QSGNode* node, QQuickItem::UpdatePaintNodeData*)
{
	qDebug() << "----------------------------------------";
	qDebug() << "Drawing " << this;

	// First draw, we need to initialize the node and set the geometry
	if (!node) {
		auto* n = new QSGSimpleRectNode;

		n->setRect(boundingRect());

		node = n;
	}

	// Delegate drawing to the layer stack
	m_layers.applyChanges(node);
	m_layers.updateNode(node);

	return node;
}

