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

/*! This macro is needed in objects that derive from Registered.
 *  It should be used similarly to Q_OBJECT or Q_PROPERTY, in the private section.
 *  NOTE: There's a known issue in some systems where moc doesn't preprocess
 *        this macro correctly and doesn't generate the QObject code for
 *        Q_PROPERTY(QString name)
 */
#define GTG_REGISTERED(TYPE) \
		Q_PROPERTY(QString name READ name WRITE __gtg_Registered_setName) \
		public: \
		void __gtg_Registered_setName(const QString& name) { Registered::setName<TYPE>(name); } \
		private:

namespace gtg
{
	class Registry;

	/*! \brief Base class of anything that can be queried to a Registry.
	 *
	 * Inheriting this class provides a way to find objects of the
	 * derived class by name in a given Registry.
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

			//! Returns the current name of the object
			QString name() const;

			/*! \brief Change and register with the new name
			 *
			 * If it was previously registered, it is unregistered,
			 * the name is changed and then re-registered.
			 *
			 * \param name The new name
			 */
			template <class T>
			void setName(const QString& name);

			/*! Pure virtual function that returns the registry where
			 *  objects of this class should be registered
			 */
			virtual Registry* registry() const = 0;
	};


	/*! \brief Encapsulation of a map of QString,Registered* pairs.
	 *
	 * This class is the main way to keep track of objects required
	 * by the GTG QML API. They are loaded transparently and can be
	 * found through the global registry where registries of derived
	 * Registered objects are stored by (usually) class name.
	 *   Example:
	 *     property var myObject: Registry.find("ClassName").find("myObject")
	 */
	class Registry
		: public QObject
		, public Registered //<! Registered in the global registry
	{
		Q_OBJECT

		GTG_REGISTERED(Registry)

		private:
			static bool m_staticDeleted;

			QString m_staticKey;
			QHash<QString, QObject*> m_table;

		public:
			//! Reserved for the global registry. Public is needed for QML exposure
			Registry(QObject* parent = nullptr);

			/*! \brief Constructor for Registry
			 * \param staticKey The key that should be inserted into the static registry
			 * \param parent The parent QObject for garbage collection. If global() is left,
			 *               it will be removed automatically when the global registry is destroyed
			 */
			Registry(QString staticKey, QObject* parent = global());

			virtual ~Registry();

			//! Copy is not allowed
			Registry(const Registry& other) = delete;
			Registry& operator= (const Registry& other) = delete;

			//! Retuns the static registry for the registry class
			Registry* registry() const override;

			//! Store a new object in the map. Use with care, may be private in future versions.
			template <class T>
			void registerObj(T* obj);

			//! Remove an object from the map. Use with care, may be private in future versions.
			void unregisterObj(Registered* obj);

			//! \brief Returns the static registry. Used to implement registry()
			static gtg::Registry* global();

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

QML_DECLARE_TYPE(gtg::Registry)



template <class T>
void gtg::Registered::setName(const QString& name)
{
	if (name != this->name()) {
		if (m_nameSet)
			registry()->unregisterObj(this);

		m_name = name;
		registry()->registerObj(static_cast<T*>(this));
		m_nameSet = true;
	}
}


#endif
