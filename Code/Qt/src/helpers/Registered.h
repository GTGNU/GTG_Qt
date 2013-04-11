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

#ifndef REGISTERED_H
#define REGISTERED_H

#include <QtCore/QObject>

#include "NamedObject.h"

namespace gtg
{
	/*! \brief Base class of anything that can be queried to a static map.
	 *
	 * Inheriting this class provides a static map to find objects of the
	 * given class by name (as specified through the base NamedObejct class)
	 */
	template <class T>
	class Registered
		: public NamedObject
	{
		protected:
			bool m_nameSet;
			static QHash<QString, T*> m_table;

		protected:
			QString m_name;

			//! Store a new object in the map
			static void registerObj(T* obj);
			//! Remove an object from the map
			static void unregisterObj(T* obj);

		public:
			Registered(QObject* parent = nullptr);
			virtual ~Registered();

			virtual void setName(const QString& name);

			/*! \brief Find an object
			 * \param name
			 * \return Object registered with the given name or null if not found
			 */
			static T* find(const QString& key);
	};
}

template <class T>
QHash<QString, T*> gtg::Registered<T>::m_table;

template <class T>
gtg::Registered<T>::Registered(QObject* parent)
	: NamedObject(parent)
	, m_nameSet(false)
{}

template <class T>
gtg::Registered<T>::~Registered()
{}

template <class T>
void gtg::Registered<T>::setName(const QString& name)
{
	if (name != m_name) {
		if (m_nameSet)
			unregisterObj(static_cast<T*>(this));

		NamedObject::setName(name);
		registerObj(static_cast<T*>(this));
		m_nameSet = true;
	}
}

template <class T>
T* gtg::Registered<T>::find(const QString& key)
{
	return m_table[key];
}

template <class T>
void gtg::Registered<T>::registerObj(T* obj)
{
	if (!m_table.contains(obj->name())) {
		m_table.insert(obj->name(), obj);
		qDebug() << "Registered" << obj << "as" << obj->name();
	} else {
		qWarning() << "Could not registerObj" << obj << obj->name()
			<< ": already exists";
	}
}

template <class T>
void gtg::Registered<T>::unregisterObj(T* obj)
{
	for (auto it = m_table.begin(); it != m_table.end(); it++) {
		if (it.key() == obj->name()) {
			if (it.value() == obj) {
				m_table.erase(it);
				qDebug() << obj << obj->name() << "unregisterObjed successfully";
				return;
			} else {
				qWarning() << "Found partial match at unregisterObj(" << obj << "):"
					<< it.key() << "=>" << it.value();
			}
		}
	}
}

#endif
