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

#include "NamedObject.h"

#include <QtCore/QDebug>

gtg::NamedObject::NamedObject(QObject* parent)
	: QObject(parent)
	, m_name()
{}

gtg::NamedObject::~NamedObject()
{
}

QString gtg::NamedObject::name() const
{
	return m_name;
}


void gtg::NamedObject::setName(const QString& name)
{
	m_name = name;
}
