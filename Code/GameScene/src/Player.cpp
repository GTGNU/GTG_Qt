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

#include "Player.h"

#include "Tile.h"
#include "Row.h"
#include "Map.h"
#include "tile/Behavior.h"


using gtg::tile::Behavior;

using gtg::Player;
using gtg::Tile;
using gtg::Row;
using gtg::Map;


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


Tile* Player::currentTile() const
{
	return m_currentTile;
}

void Player::moveBy(int dx, int dy)
{
	moveTo(map()->tileAt(currentTile()->mapX() + dx, currentTile()->mapY() + dy));
}

void Player::moveTo(Tile* tile)
{
	bool differentBehavior = tile->behavior() != m_currentTile->behavior();

	m_currentTile->setPlayer(nullptr);
	if (differentBehavior)
		m_currentTile->behavior()->emitPlayerExitedArea(this);

	m_currentTile = tile;

	m_currentTile->setPlayer(this);
	if (differentBehavior)
		m_currentTile->behavior()->emitPlayerEnteredArea(this);
}


Map* Player::map() const
{
	return qobject_cast<Map*>(qobject_cast<Row*>(parent())->parent());
}
