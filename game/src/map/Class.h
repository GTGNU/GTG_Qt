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

#ifndef TILECLASS_H
#define TILECLASS_H

#include <QtCore/QObject>

#include <QtQuick/QQuickItem>

#include "util/Registered.h"

namespace gtg
{
	namespace gfx
	{
		class Texture;
	}

	namespace map
	{
		class Behavior;

		/*! \brief Composition of a Texture and a Behavior
		 *
		 * This class is used to define new tile classes outside
		 * of the map definition file so instances can be shared
		 * so many layers point to a single texture or emit signals
		 * to the same behavior.
		 *
		 * It also reduces verboseness of map files.
		 */
		class Class
			: public QObject
			, public Registered
		{
			Q_OBJECT

			GTG_REGISTERED(Class)

			Q_PROPERTY(
					gtg::gfx::Texture* texture
					READ texture
					WRITE setTexture
					NOTIFY textureChanged)

			Q_PROPERTY(
					gtg::map::Behavior* behavior
					READ behavior
					WRITE setBehavior
					NOTIFY behaviorChanged)

			private:
				Registry* registry() const override;

				gfx::Texture* m_texture;
				Behavior* m_behavior;

			public:
				explicit Class(QObject* parent = nullptr);
				~Class();

				gtg::gfx::Texture* texture() const;
				void setTexture(gtg::gfx::Texture* texture);

				gtg::map::Behavior* behavior() const;
				void setBehavior(gtg::map::Behavior* behavior);

			signals:
				void textureChanged(
						gtg::gfx::Texture* oldTexture,
						gtg::gfx::Texture* newTexture);

				void behaviorChanged(
						gtg::map::Behavior* oldBehavior,
						gtg::map::Behavior* newBehavior);
		};
	}
}

QML_DECLARE_TYPE(gtg::map::Class)

#endif
