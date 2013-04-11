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

#ifndef TILEBEHAVIOR_H
#define TILEBEHAVIOR_H

#include <QtCore/QObject>

#include <QtQml>

#include "helpers/Registered.h"
#include "helpers/NamedObject.h"

namespace gtg
{
	class Player;

	namespace tile
	{
		/*! \brief Encapsulates how a tile interacts with events
		 *
		 * This class mainly contains basic behavioral properties
		 * such as trespassability for tiles and emits signals
		 * when events are triggered
		 */
		class Behavior
			: public Registered<Behavior>
		{
			Q_OBJECT
			Q_PROPERTY(
					bool trespassable
					READ isTrespassable
					WRITE setTrespassable
					NOTIFY trespassabilityChanged)

			private:
				bool m_trespassable;

				//! Allow classes emit this signal from the outside
				void emitPlayerEnteredArea(Player* player);
				//! Allow classes emit this signal from the outside
				void emitPlayerExitedArea(Player* player);

			public:
				Behavior(QObject* parent = nullptr);
				~Behavior();

				bool isTrespassable() const;
				void setTrespassable(bool trespassable);

			signals:
				void trespassabilityChanged(bool trespassable);
				void playerEnteredArea(gtg::Player* player);
				void playerExitedArea(gtg::Player* player);

				friend class gtg::Player;
		};
	}
}

QML_DECLARE_TYPE(gtg::tile::Behavior)

#endif
