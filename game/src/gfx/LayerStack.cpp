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

#include "LayerStack.h"

#include <iterator>
#include <algorithm>

#include <QtQuick/QSGNode>
#include <QtQuick/QSGSimpleTextureNode>

#include "Texture.h"
#include "Layer.h"


using gtg::gfx::LayerStack;
using gtg::gfx::Layer;


LayerStack::LayerStack(QObject* parent)
	: QObject(parent)
	, m_item(nullptr)
{
}

LayerStack::LayerStack(QQuickItem* item, QObject* parent)
	: QObject(parent)
	, m_item(item)
{
}

LayerStack::~LayerStack()
{
}


unsigned LayerStack::count() const
{
	return m_layers.size();
}

Layer* LayerStack::at(unsigned index) const
{
	return m_layers.at(index);
}

unsigned LayerStack::indexOf(Layer* layer) const
{
	return m_layers.indexOf(layer);
}


void LayerStack::append(Layer* layer)
{
	insert(m_layers.size(), layer);
}

void LayerStack::unshift(Layer* layer)
{
	insert(0, layer);
}

void LayerStack::push(Layer* layer)
{
	append(layer);
}

void LayerStack::insert(unsigned index, Layer* layer)
{
	// Schedule an update of the item if the layer changed
	QObject::connect(layer, &Layer::changed,
			m_item, &QQuickItem::update,
			Qt::DirectConnection);

	m_changes.push_back({Change::ADD, index, layer});
	m_layers.insert(index, layer);

	m_item->update();
}


void LayerStack::remove(Layer* layer)
{
	QObject::disconnect(layer, &Layer::changed,
			m_item, &QQuickItem::update);

	QList<Layer*>::iterator it =
		std::find(m_layers.begin(), m_layers.end(), layer);

	m_changes.push_back({
			Change::REMOVE,
			static_cast<unsigned>(std::distance(m_layers.begin(), it)),
			layer
		});

	m_layers.erase(it);

	m_item->update();
}

void LayerStack::remove(unsigned index)
{
	auto it = m_layers.begin() + index;

	QObject::disconnect(*it, &Layer::changed,
			m_item, &QQuickItem::update);

	m_changes.push_back({Change::REMOVE, index, *it});
	m_layers.erase(it);

	m_item->update();
}


void LayerStack::clear()
{
	m_changes.push_back({Change::CLEAR, 0, nullptr});
	m_layers.clear();

	m_item->update();
}


void LayerStack::replace(Layer* prev, Layer* layer)
{
	replace(indexOf(prev), layer);
}

void LayerStack::replace(unsigned index, Layer* layer)
{
	remove(index);
	insert(index, layer);
}



bool LayerStack::applyChanges(QSGNode* node)
{
	QSGNode* newNode;

	for (const Change& change : m_changes) {
		switch (change.action) {
			case Change::ADD:
				// Ask the layer to generate a new node
				newNode = change.layer->updateNode(node, m_item);

				// Add it to the node
				if (change.index == (unsigned)node->childCount()) {
					node->appendChildNode(newNode);
				} else if (change.index < (unsigned)node->childCount()) {
					node->insertChildNodeBefore(newNode,
							node->childAtIndex(change.index));
				} else {
					qWarning() << "Warning: change index is greater than the number of childs of the node"
						<< "\tin the LayerStack of" << m_item;
				}

				break;

			case Change::REMOVE:
				node->removeChildNode(
						node->childAtIndex(change.index));
				break;

			case Change::CLEAR:
				node->removeAllChildNodes();
		}
	}

	// Changes have been applied, clear for the next call
	m_changes.clear();

	return m_changes.size() > 0;
}

void LayerStack::updateNode(QSGNode* node)
{
	// We just need to call layer->updateNode for each layer
	for (Layer* layer : m_layers)
		layer->updateNode(node, m_item);
}
