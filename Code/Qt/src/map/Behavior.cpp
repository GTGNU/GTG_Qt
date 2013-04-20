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

#include "Behavior.h"

#include "helpers/Registered.h"


using gtg::map::Behavior;

using gtg::Registry;


Behavior::Behavior(QObject* parent)
	: Registered()
	, m_trespassable(false)
{
}

Behavior::~Behavior()
{
}


Registry* Behavior::registry() const
{
	static Registry* behaviorRegistry = new Registry("Behavior");

	return behaviorRegistry;
}


bool Behavior::isTrespassable() const
{
	return m_trespassable;
}

void Behavior::setTrespassable(bool trespassable)
{
	m_trespassable = trespassable;
	emit trespassabilityChanged(m_trespassable);
}

