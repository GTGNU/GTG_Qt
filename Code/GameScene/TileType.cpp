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

#include "TileType.h"

gtg::TileType::TileType(QObject* parent)
	: TileDef<TileType>(parent)

	, m_view(nullptr)
	, m_behavior(nullptr)
{
}

gtg::TileType::~TileType()
{
}


gtg::TileView* gtg::TileType::view() const
{
	return m_view;
}

void gtg::TileType::setView(gtg::TileView* view)
{
	auto prev = m_view;
	m_view = view;
	emit viewChanged(prev, m_view);
}


gtg::TileBehavior* gtg::TileType::behavior() const
{
	return m_behavior;
}

void gtg::TileType::setBehavior(gtg::TileBehavior* behavior)
{
	auto prev = m_behavior;
	m_behavior = behavior;
	emit behaviorChanged(prev, m_behavior);
}
