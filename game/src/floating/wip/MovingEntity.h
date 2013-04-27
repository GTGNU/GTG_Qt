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

#ifndef PLAYER_H
#define PLAYER_H

#include <QtCore/QString>

#include <QtQuick/QQuickItem>

#include "Entity.h"

namespace gtg
{
	namespace map
	{
		class Map;
		class Tile;
	}

	namespace floating
	{
		class MovingEntity
			: public Entity
		{
			Q_OBJECT

			Q_PROPERTY(
					double speedX
					READ speedX
					WRITE setSpeedX)

			Q_PROPERTY(
					double speedY
					READ speedY
					WRITE setSpeedY)

			private:
				QString m_name;
				double m_speed;

				map::Tile* m_currentTile;

				QTimer& timer() const override;

			public:
				Player(QQuickItem* parent = nullptr);
				~Player();

				Registry* registry() const override;

				qreal speedX() const;
				void setSpeedX(qreal speed);

				qreal speedY() const;
				void setSpeedY(qreal speed);

			signals:
				void moved(int, int);
		};
	}
}

QML_DECLARE_TYPE(gtg::floating::Player)

#endif
