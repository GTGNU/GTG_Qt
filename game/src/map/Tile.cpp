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

#include <QtGui/QImage>

#include <QtQuick/QSGNode>
#include <QtQuick/QSGSimpleRectNode>
#include <QtQuick/QSGTexture>
#include <QtQuick/QQuickWindow>

#include "Row.h"
#include "Map.h"
#include "Behavior.h"

#include "gfx/Layer.h"

#include "util/QmlListAdapter.h"


using gtg::gfx::Layer;

using gtg::map::Behavior;
using gtg::map::Tile;
using gtg::map::Row;
using gtg::map::Map;


Tile::Tile(QQuickItem* parent)
	: QQuickItem(parent)
	, m_layers(this)
	, m_behavior(nullptr)
{
	setFlag(QQuickItem::ItemHasContents);
}

Tile::~Tile()
{
}


QQmlListProperty<Layer> Tile::layersQml()
{
	return gtg::qml_adapt<Layer>(m_layers, this);
}


Behavior* Tile::behavior() const
{
	return m_behavior;
}

void Tile::setBehavior(Behavior* behavior)
{
	if (m_behavior != behavior) {
		Behavior* prev = m_behavior;
		m_behavior = behavior;
		emit behaviorChanged(prev, m_behavior);
	}
}


int Tile::mapX() const
{
	return row()->indexOf(this);
}

int Tile::mapY() const
{
	return row()->mapY();
}


Row* Tile::row() const
{
	return qobject_cast<Row*>(parentItem());
}

Map* Tile::map() const
{
	return row()->map();
}


unsigned Tile::layerCount() const
{
	return m_layers.count();
}

unsigned Tile::indexOfLayer(Layer* layer) const
{
	return m_layers.indexOf(layer);
}


void Tile::unshiftLayer(Layer* layer)
{
	addLayer(0, layer);
}

void Tile::pushLayer(Layer* layer)
{
	addLayer(layerCount(), layer);
}

void Tile::addLayer(unsigned index, Layer* layer)
{
	m_layers.insert(index, layer);
}


void Tile::removeLayer(Layer* layer)
{
	removeLayer(indexOfLayer(layer));
}

void Tile::removeLayer(unsigned index)
{
	m_layers.remove(index);
}


void Tile::replaceLayer(Layer* prev, Layer* layer)
{
	replaceLayer(indexOfLayer(prev), layer);
}

void Tile::replaceLayer(unsigned index, Layer* layer)
{
	m_layers.remove(index);
	m_layers.insert(index, layer);
}


QSGNode* Tile::updatePaintNode(QSGNode* node,
		QQuickItem::UpdatePaintNodeData* updatePaintNodeData)
{
	/*qDebug() << "----------------------------------------";
	qDebug() << "Drawing " << this;*/

	// First draw, we need to initialize the node and set the geometry
	if (!node) {
		auto* n = new QSGSimpleRectNode;

		int tileSize = map()->tileSize();
		setX(mapX() * tileSize);
		setY(0); // relative to row
		setWidth(tileSize);
		setHeight(tileSize);

		n->setRect(boundingRect());
		node = n;
	}

	//qDebug() << "Bounding rect: " << boundingRect();

	// Delegate drawing to the layer stack
	m_layers.applyChanges(node);
	m_layers.updateNode(node);

	return node;
}

