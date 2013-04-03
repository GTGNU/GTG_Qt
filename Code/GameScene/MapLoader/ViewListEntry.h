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

#ifndef VIEWLISTENTRY_H
#define VIEWLISTENTRY_H

#include <QtCore/QObject>

#include "TileView.h"

namespace gtg
{
	class ViewListEntry
		: public QObject
	{
		Q_OBJECT
		Q_PROPERTY(gtg::TileView* view READ view WRITE setView)
		Q_PROPERTY(gtg::TileView::Area area READ area WRITE setArea)

		private:
			TileView* m_view;
			TileView::Area m_area;

		public:
			ViewListEntry(QObject* parent = nullptr);
			~ViewListEntry();

			gtg::TileView* view() const;
			void setView(gtg::TileView* view);

			gtg::TileView::Area area() const;
			void setArea(gtg::TileView::Area area);

		signals:
			void textureChanged();
	};
}

QML_DECLARE_TYPE(gtg::ViewListEntry)

#endif
