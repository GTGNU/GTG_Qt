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

#ifndef TILEBEHAVIOR_H
#define TILEBEHAVIOR_H

#include <QtCore/QObject>

#include <QtQml>

#include "TileDef.h"
#include "NamedObject.h"

namespace gtg
{
	class Player;

	class TileBehavior
		: public TileDef<TileBehavior>
	{
		Q_OBJECT
		Q_PROPERTY(bool trespassable READ isTrespassable WRITE setTrespassable)

		private:
			bool m_trespassable;

			void emitPlayerEnteredArea(Player* player);
			void emitPlayerExitedArea(Player* player);

		public:
			TileBehavior(QObject* parent = nullptr);
			~TileBehavior();

			bool isTrespassable() const;
			void setTrespassable(bool trespassable);

		signals:
			void playerEnteredArea(Player*);
			void playerExitedArea(Player*);

		friend class Player;
	};
}

QML_DECLARE_TYPE(gtg::TileBehavior)

#endif
