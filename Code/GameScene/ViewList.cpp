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

#include "ViewList.h"

#include "Tile.h"
#include "TileView.h"
#include "ViewListEntry.h"

#include <iterator>
#include <algorithm>

#include <QtQuick/QSGNode>
#include <QtQuick/QSGSimpleTextureNode>

gtg::ViewList::ViewList(Tile* tile)
	: m_tile(tile)
{
}

gtg::ViewList::~ViewList()
{
}


void gtg::ViewList::append(ViewListEntry* entry)
{
	insert(m_entries.size(), entry);
}

void gtg::ViewList::insert(unsigned index, ViewListEntry* entry)
{
	QObject::connect(entry, &ViewListEntry::changed,
			m_tile, &QQuickItem::update,
			Qt::DirectConnection);

	m_changes.push_back({Change::ADD, index, entry});
	m_entries.insert(index, entry);

	m_tile->update();
}


void gtg::ViewList::remove(ViewListEntry* entry)
{
	QObject::disconnect(entry, &ViewListEntry::changed,
			m_tile, &QQuickItem::update);

	auto it = std::find(m_entries.begin(), m_entries.end(), entry);
	m_changes.push_back({Change::REMOVE, std::distance(m_entries.begin(), it), entry});
	m_entries.erase(it);

	m_tile->update();
}

void gtg::ViewList::remove(unsigned index)
{
	auto it = m_entries.begin() + index;

	QObject::disconnect(*it, &ViewListEntry::changed,
			m_tile, &QQuickItem::update);

	m_changes.push_back({Change::REMOVE, index, *it});
	m_entries.erase(it);

	m_tile->update();
}


int gtg::ViewList::count() const
{
	return m_entries.size();
}

gtg::ViewListEntry* gtg::ViewList::at(unsigned index) const
{
	return m_entries.at(index);
}

unsigned gtg::ViewList::indexOf(ViewListEntry* entry) const
{
	return m_entries.indexOf(entry);
}


void gtg::ViewList::clear()
{
	m_changes.push_back({Change::CLEAR, 0, nullptr});
	m_entries.clear();

	m_tile->update();
}


bool gtg::ViewList::applyChanges(QSGNode* node)
{
	QSGNode* newNode;

	for (const Change& change : m_changes) {
		switch (change.action) {
			case Change::ADD:
				newNode = change.entry->updateNode(node, m_tile);

				if (change.index == node->childCount()) {
					node->appendChildNode(newNode);
				} else if (change.index < node->childCount()) {
					node->insertChildNodeBefore(newNode,
							node->childAtIndex(change.index));
				} else {
					qWarning() << "Warning: change index is greater than the number of childs of the node"
						<< "\tin the ViewList of" << m_tile;
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

	m_changes.clear();
	return m_changes.size() > 0;
}

void gtg::ViewList::updateNode(QSGNode* node)
{
	for (ViewListEntry* entry : m_entries)
		QSGNode* result = entry->updateNode(node, m_tile);

		/*if (child != result) {
			node->insertChildNodeBefore(result, child);
			node->removeChildNode(child);
		}*/
}
