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

#include <QtCore/QString>
#include <QtCore/QDebug>

#include <QtQuick/QQuickItem>


#define GTG_REGISTERED(TYPE) \
		Q_PROPERTY(QString name READ name WRITE __setName) \
		public: \
		void __setName(const QString& name) { Registered::setName<TYPE>(name); } \
		private:

namespace gtg
{
	class Registry;

	/*! \brief Simple QObject that has a name property
	 */
	class Registered
	{
		private:
			QString m_name;
			bool m_nameSet;

		public:
			Registered();
			virtual ~Registered();

			Registered(const Registered& other) = delete;
			Registered& operator= (const Registered& other) = delete;

			QString name() const;

			template <class T>
			void setName(const QString& name);

			virtual Registry* registry() const = 0;
	};


	/*! \brief Base class of anything that can be queried to a static map.
	 *
	 * Inheriting this class provides a static map to find objects of the
	 * given class by name (as specified through the base NamedObejct class)
	 */
	class Registry
		: public QObject
		, public Registered
	{
		Q_OBJECT

		GTG_REGISTERED(Registry)

		private:
			QString m_staticKey;
			QHash<QString, QObject*> m_table;

		public:
			Registry(QObject* parent = nullptr);
			Registry(QString staticKey, QObject* parent = global());
			virtual ~Registry();

			Registry(const Registry& other) = delete;
			Registry& operator= (const Registry& other) = delete;

			Registry* registry() const override;

			//! Store a new object in the map
			template <class T>
			void registerObj(T* obj);

			//! Remove an object from the map
			template <class T>
			void unregisterObj(T* obj);

			//! \brief Returns the static registry
			Q_INVOKABLE static gtg::Registry* global();

			//! \brief Get all names in this registry
			Q_INVOKABLE QList<QString> names() const;

			/*! \brief Find an object
			 * \param name
			 * \return Object registered with the given name or null if not found
			 */
			Q_INVOKABLE QObject* find(const QString& name) const;
	};
}

template <class T>
void gtg::Registry::registerObj(T* obj)
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
void gtg::Registry::unregisterObj(T* obj)
{
	auto it = m_table.find(obj->name());

	if (it != m_table.end()) {
		if (it.value() == static_cast<QObject*>(obj)) {
			m_table.erase(it);
			qDebug() << obj << obj->name() << "unregisterObjed successfully";
			return;
		} else {
			qWarning() << "Found partial match at unregisterObj(" << obj << "):"
				<< it.key() << "=>" << it.value();
		}
	}
}

QML_DECLARE_TYPE(gtg::Registry)


template <class T>
void gtg::Registered::setName(const QString& name)
{
	if (name != this->name()) {
		if (m_nameSet)
			registry()->unregisterObj(static_cast<T*>(this));

		m_name = name;
		registry()->registerObj(static_cast<T*>(this));
		m_nameSet = true;
	}
}


#endif
