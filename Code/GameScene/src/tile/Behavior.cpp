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

#include "Behavior.h"


using gtg::tile::Behavior;

using gtg::Player;


Behavior::Behavior(QObject* parent)
	: Registered<Behavior>(parent)
	, m_trespassable(false)
{
}

Behavior::~Behavior()
{
}


bool Behavior::isTrespassable() const
{
	return m_trespassable;
}

void Behavior::setTrespassable(bool trespassable)
{
	m_trespassable = trespassable;
	emit trespassabilityChanged(m_trespassable);
}


void Behavior::emitPlayerEnteredArea(Player* player)
{
	emit playerEnteredArea(player);
}

void Behavior::emitPlayerExitedArea(Player* player)
{
	emit playerExitedArea(player);
}
