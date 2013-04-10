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

#include <QtQml>

#include "helpers/Registered.h"

namespace gtg
{
	namespace tile
	{
		class Texture;
		class Behavior;

		class Class
			: public Registered<Class>
		{
			Q_OBJECT

				Q_PROPERTY(
						gtg::tile::Texture* texture
						READ texture
						WRITE setTexture
						NOTIFY textureChanged)

				Q_PROPERTY(
						gtg::tile::Behavior* behavior
						READ behavior
						WRITE setBehavior
						NOTIFY behaviorChanged)

			private:
				Texture* m_texture;
				Behavior* m_behavior;

			public:
				Class(QObject* parent = nullptr);
				~Class();

				gtg::tile::Texture* texture() const;
				void setTexture(gtg::tile::Texture* texture);

				gtg::tile::Behavior* behavior() const;
				void setBehavior(gtg::tile::Behavior* behavior);

			signals:
				void textureChanged(
						gtg::tile::Texture* oldTexture,
						gtg::tile::Texture* newTexture);

				void behaviorChanged(
						gtg::tile::Behavior* oldBehavior,
						gtg::tile::Behavior* newBehavior);
		};
	}
}

QML_DECLARE_TYPE(gtg::tile::Class)

#endif
