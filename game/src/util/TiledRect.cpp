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

#include "TiledRect.h"

#include <cmath>

using std::floor;
using std::ceil;

using gtg::TiledRect;

TiledRect::TiledRect()
	: TiledRect({0,0,0,0}, 1)
{
}

TiledRect::TiledRect(const QRectF& rect, unsigned tileSize)
	: m_rect(rect)
	, m_tileSize(tileSize)
{
}

int TiledRect::x() const
{
	return floor(m_rect.x() / m_tileSize);
}

int TiledRect::y() const
{
	return floor(m_rect.y() / m_tileSize);
}


int TiledRect::x2() const
{
	return ceil((m_rect.x() + m_rect.width()) / m_tileSize);
}

int TiledRect::y2() const
{
	return ceil((m_rect.y() + m_rect.height()) / m_tileSize);
}


int TiledRect::width() const
{
	return x2() - x();
}

int TiledRect::height() const
{
	return y2() - y();
}


QRectF& TiledRect::rect()
{
	return m_rect;
}
