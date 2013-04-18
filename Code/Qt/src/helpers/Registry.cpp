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

#include "Registered.h"

using gtg::Registry;
using gtg::Registered;


Registry::Registry(QObject* parent)
	: QObject(parent)
	, Registered()
{
	qDebug() << "Initialized static registry";
}

Registry::Registry(QString staticKey, QObject* parent)
	: QObject(parent)
	, Registered()
	, m_staticKey(staticKey)
{
	setName<Registry>(m_staticKey);
	qDebug() << "Registry" << name() << "initialized with key" << staticKey;
}

Registry::~Registry()
{
	qDebug() << "Deleting" << (this == global()?"global":"") << "registry with name" << name();
}


Registry* Registry::registry() const
{
	return global();
}

Registry* Registry::global()
{
	static Registry reg;
	return &reg;
}

QList<QString> Registry::names() const
{
	return m_table.keys();
}

QObject* Registry::find(const QString& name) const
{
	return static_cast<QObject*>(m_table.find(name).value());
}

