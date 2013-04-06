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

#include "TileBehavior.h"

gtg::TileBehavior::TileBehavior(QObject* parent)
	: TileDef<TileBehavior>(parent)

	, m_trespassable(false)
{
}

gtg::TileBehavior::~TileBehavior()
{
}


bool gtg::TileBehavior::isTrespassable() const
{
	return m_trespassable;
}

void gtg::TileBehavior::setTrespassable(bool trespassable)
{
	m_trespassable = trespassable;
}


void gtg::TileBehavior::emitPlayerEnteredArea(Player* player)
{
	emit playerEnteredArea(player);
}

void gtg::TileBehavior::emitPlayerExitedArea(Player* player)
{
	emit playerExitedArea(player);
}
