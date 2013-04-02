#include "ViewList.h"

#include "Tile.h"
#include "TileView.h"
#include "ViewListEntry.h"

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
	QObject::connect(entry, &ViewListEntry::textureChanged,
			m_tile, &QQuickItem::update);

	m_changes.insert(ADD, m_entries.size());
	m_entries.push_back(entry);
}


void gtg::ViewList::remove(ViewListEntry* entry)
{
	QObject::disconnect(entry, &ViewListEntry::textureChanged,
			m_tile, &QQuickItem::update);

	m_changes.insert(REMOVE, m_entries.indexOf(entry));
	m_entries.removeOne(entry);
}

void gtg::ViewList::remove(int index)
{
	auto it = m_entries.begin() + index;

	QObject::disconnect(*it, &ViewListEntry::textureChanged,
			m_tile, &QQuickItem::update);

	m_changes.insert(REMOVE, index);
	m_entries.erase(it);
}


int gtg::ViewList::count() const
{
	return m_entries.size();
}


gtg::ViewListEntry* gtg::ViewList::at(int index) const
{
	return m_entries.at(index);
}


void gtg::ViewList::clear()
{
	m_changes.insert(CLEAR, {});
	m_entries.clear();
}


bool gtg::ViewList::applyChanges(QSGNode* node)
{
	QSGSimpleTextureNode* n;

	for (auto change = m_changes.begin(); change != m_changes.end(); change++) {
		switch (change.key()) {
			case ADD:
				n = new QSGSimpleTextureNode;
				n->setRect(m_tile->boundingRect());
				if (change.value() >= node->childCount()) {
					node->appendChildNode(n);
				} else {
					node->insertChildNodeBefore(n,
							node->childAtIndex(change.value()));
				}
				break;

			case REMOVE:
				node->removeChildNode(node->childAtIndex(change.value()));
				break;

			case CLEAR:
				node->removeAllChildNodes();
		}
	}

	m_changes.clear();
	return m_changes.size() > 0;
}

void gtg::ViewList::updateTextures(QSGNode* node)
{
	int i = 0;
	for (ViewListEntry* entry : m_entries) {
		entry->view()->updateTextureOf(
			static_cast<QSGSimpleTextureNode*>( node->childAtIndex(i) ),
			m_tile->window(),
			entry->area());
		i++;
	}
}
