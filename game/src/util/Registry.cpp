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

#include <QtQml/QJSValue>
#include <QtQml/QJSValueList>
#include <QtQml/QQmlEngine>

#include "qmlengine.h"


using gtg::Registry;
using gtg::Registered;


bool Registry::m_staticDeleted = false;


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
	qDebug() << "Registry initialized with key" << staticKey;
}

Registry::~Registry()
{
	qDebug() << "Deleting" << (this == global()?"global":"") << "registry with name" << name();

	// If there's still a global register, cleanup first
	if (!m_staticDeleted && this != global())
		registry()->unregisterObj(this);
	// If the static register, mark as deleted to avoid segfaults
	else
		m_staticDeleted = true;
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

void Registry::for_each(QJSValue block) const
{
	if (block.isCallable()) {
		for (QObject* entry : m_table) {
			QJSValueList args;
			args << qmlengine::engine()->toScriptValue(entry);
			block.call(args);
		}
	}
}


void gtg::Registry::unregisterObj(Registered* obj)
{
	auto it = m_table.find(obj->name());

	if (it != m_table.end()) {
		// dynamic_cast<void*> returns a pointer to the "most derived object"
		// so we can compare by identity (base pointers don't hold the same address)
		if (dynamic_cast<void*>(it.value()) == dynamic_cast<void*>(obj)) {
			m_table.erase(it);
			qDebug() << obj << obj->name() << "unregistered successfully";
			return;
		} else {
			qWarning() << "Found partial match at unregisterObj(" << obj << "):"
				<< it.key() << "=>" << it.value();
		}
	}
}
