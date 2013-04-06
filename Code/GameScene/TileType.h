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

#ifndef TILETYPE_H
#define TILETYPE_H

#include <QtCore/QObject>

#include <QtQml>

#include "TileDef.h"
#include "ViewList.h"

namespace gtg
{
	class TileView;
	class TileBehavior;

	class TileType
		: public TileDef<TileType>
	{
		Q_OBJECT
		Q_PROPERTY(gtg::TileView* view READ view WRITE setView NOTIFY viewChanged)
		Q_PROPERTY(gtg::TileBehavior* behavior READ behavior WRITE setBehavior NOTIFY behaviorChanged)

		private:
			TileView* m_view;
			TileBehavior* m_behavior;

		public:
			TileType(QObject* parent = nullptr);
			~TileType();

			gtg::TileView* view() const;
			void setView(gtg::TileView* view);

			gtg::TileBehavior* behavior() const;
			void setBehavior(gtg::TileBehavior* behavior);

		signals:
			void viewChanged(gtg::TileView* oldView,
					gtg::TileView* newView);

			void behaviorChanged(gtg::TileBehavior* oldBehavior,
					gtg::TileBehavior* newBehavior);
	};
}

QML_DECLARE_TYPE(gtg::TileType)

#endif
