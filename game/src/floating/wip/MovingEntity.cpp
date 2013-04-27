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

#include "MovingEntity.h"

#include "map/Tile.h"
#include "map/Row.h"
#include "map/Map.h"
#include "map/Behavior.h"


using gtg::floating::MovingEntity;

using gtg::map::Behavior;
using gtg::map::Tile;
using gtg::map::Row;
using gtg::map::Map;


MovingEntity::MovingEntity(QQuickItem* parent)
	: QQuickItem(parent)
	, m_currentTile(nullptr)
{
}

MovingEntity::~MovingEntity()
{
}


QTimer& MovingEntity::timer() const
{
	static QTimer timer;
	timer.setInterval(timerInterval());

}

Registry* MovingEntity::registry() const
{
	static Registry* playerRegistry = new Registry("MovingEntity");
	return playerRegistry;
}


double MovingEntity::speed() const
{
	return m_speed;
}

void MovingEntity::setSpeed(double speed)
{
	m_speed = speed;
}


Tile* MovingEntity::currentTile() const
{
	return m_currentTile;
}

void MovingEntity::moveBy(int dx, int dy)
{
	Tile* target = map()->tileAt(x() + dx, y() + dy);
	bool differentBehavior = currentTile()->behavior() != target->behavior();

	if (differentBehavior)
		m_currentTile->behavior()->emitMovingEntityExitedArea(this);

	m_currentTile = target;

	if (differentBehavior)
		m_currentTile->behavior()->emitMovingEntityEnteredArea(this);
}
