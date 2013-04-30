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


using gtg::map::Class;
using gtg::map::Behavior;

using gtg::gfx::Texture;

using gtg::Registry;


Class::Class(QObject* parent)
	: QObject(parent)
	, Registered()
	, m_texture(nullptr)
	, m_behavior(nullptr)
{
}

Class::~Class()
{
	registry()->unregisterObj(this);
}


Registry* Class::registry() const
{
	static Registry* classRegistry = new Registry("Class");
	return classRegistry;
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
