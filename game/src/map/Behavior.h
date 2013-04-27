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

#include <QtQuick/QQuickItem>

#include "util/Registered.h"

namespace gtg
{
	namespace map
	{
		/*! \brief Encapsulates how a tile interacts with events
		 *
		 * This class mainly contains basic behavioral properties
		 * such as trespassability for tiles and emits signals
		 * when events are triggered
		 */
		class Behavior
			: public QObject
			, public Registered
		{
			Q_OBJECT

			GTG_REGISTERED(Behavior)

			Q_PROPERTY(
					bool trespassable
					READ isTrespassable
					WRITE setTrespassable
					NOTIFY trespassabilityChanged)

			private:
				bool m_trespassable;

			public:
				explicit Behavior(QObject* parent = nullptr);
				~Behavior();

				Registry* registry() const override;

				bool isTrespassable() const;
				void setTrespassable(bool trespassable);

			signals:
				void trespassabilityChanged(bool trespassable);
		};
	}
}

QML_DECLARE_TYPE(gtg::map::Behavior)

#endif
