#include "ViewListEntry.h"

gtg::ViewListEntry::ViewListEntry(QObject* parent)
	: QObject(parent)
	, m_view(nullptr)
	, m_area(TileView::MIDDLE)
{
}

gtg::ViewListEntry::~ViewListEntry()
{
}


gtg::TileView* gtg::ViewListEntry::view() const
{
	return m_view;
}

void gtg::ViewListEntry::setView(gtg::TileView* view)
{
	if (m_view) {
		disconnect(m_view, &TileView::textureChanged,
				this, &ViewListEntry::textureChanged);
	}

	m_view = view;
	connect(m_view, &TileView::textureChanged,
			this, &ViewListEntry::textureChanged);
}


gtg::TileView::Area gtg::ViewListEntry::area() const
{
	return m_area;
}

void gtg::ViewListEntry::setArea(gtg::TileView::Area area)
{
	m_area = area;
}

