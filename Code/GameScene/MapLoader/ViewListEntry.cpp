/*
 * Copyright 2013 xcv_
 *
 * This file is part of Grand Theft Gentoo.
 *
 * Foobar is free software: you can redistribute it and/or modify
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

