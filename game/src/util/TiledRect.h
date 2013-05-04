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

#ifndef TILEDRECT_H
#define TILEDRECT_H

#include <QtCore/QRectF>

namespace gtg
{
	class TiledRect
	{
		private:
			QRectF m_rect;
			unsigned m_tileSize;

		public:
			TiledRect();
			TiledRect(const QRectF& rect, unsigned tileSize);

			TiledRect(const TiledRect&) = default;
			TiledRect& operator=(const TiledRect&) = default;

			TiledRect(TiledRect&&) = default;
			TiledRect& operator=(TiledRect&&) = default;

			int x() const;
			int y() const;

			int x2() const;
			int y2() const;

			int width() const;
			int height() const;

			QRectF& rect();
	};
}

#endif
