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

#include "Class.h"


using gtg::tile::Class;
using gtg::tile::Texture;
using gtg::tile::Behavior;


Class::Class(QObject* parent)
	: Registered<Class>(parent)

	, m_texture(nullptr)
	, m_behavior(nullptr)
{
}

Class::~Class()
{
}


Texture* Class::texture() const
{
	return m_texture;
}

void Class::setTexture(Texture* texture)
{
	auto prev = m_texture;
	m_texture = texture;
	emit textureChanged(prev, m_texture);
}


Behavior* Class::behavior() const
{
	return m_behavior;
}

void Class::setBehavior(Behavior* behavior)
{
	auto prev = m_behavior;
	m_behavior = behavior;
	emit behaviorChanged(prev, m_behavior);
}
