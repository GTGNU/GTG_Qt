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

/*
#include "Player.h"

#include "map/Tile.h"
#include "map/Row.h"
#include "map/Map.h"
#include "map/Behavior.h"


using gtg::floating::Player;

using gtg::map::Behavior;
using gtg::map::Tile;
using gtg::map::Row;
using gtg::map::Map;


Player::Player(QQuickItem* parent)
	: QQuickItem(parent)
	, m_currentTile(nullptr)
{
}

Player::~Player()
{
}


QString Player::name() const
{
	return m_name;
}

void Player::setName(const QString& name)
{
	m_name = name;
}


double Player::speed() const
{
	return m_speed;
}

void Player::setSpeed(double speed)
{
	m_speed = speed;
}


Map* Player::map() const
{
	return qobject_cast<Map*>(qobject_cast<Row*>(parent())->parent());
}


Tile* Player::currentTile() const
{
	return m_currentTile;
}

void Player::moveBy(int dx, int dy)
{
	Tile* target = map()->tileAt(x() + dx, y() + dy);
	bool differentBehavior = currentTile()->behavior() != target->behavior();

	if (differentBehavior)
		m_currentTile->behavior()->emitPlayerExitedArea(this);

	m_currentTile = target;

	if (differentBehavior)
		m_currentTile->behavior()->emitPlayerEnteredArea(this);
}
*/
