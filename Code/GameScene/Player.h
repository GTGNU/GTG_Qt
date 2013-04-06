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

namespace gtg
{
	class Map;
	class Tile;

	class Player
	: public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(Map* map READ map)
		Q_PROPERTY(double speed READ speed WRITE setSpeed)
		Q_PROPERTY(Tile* currentTile READ currentTile WRITE moveTo)
		Q_ENUMS(Direction)

		public:
			enum Direction { LEFT, RIGHT, UP, DOWN };

		private:
			QString m_name;
			double m_speed;
			Direction m_direction;

			Tile* m_currentTile;

		public:

			Player(QQuickItem* parent);
			~Player();

			QString name() const;
			void setName(const QString& name);

			double speed() const;
			void setSpeed(double speed);

			Tile* currentTile() const;

			Q_INVOKABLE void moveBy(int dx, int dy);
			void moveTo(Tile* target);

			Map* map() const;

		signals:
			void moved(int, int);
	};
}

QML_DECLARE_TYPE(gtg::Player)

#endif
