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

#ifndef NAMEDOBJECT_H
#define NAMEDOBJECT_H

#include <QtCore/QObject>
#include <QtCore/QString>

namespace gtg
{
	class NamedObject
		: public QObject
	{
		Q_OBJECT
		Q_PROPERTY(QString name READ name WRITE setName)

		private:
			QString m_name;

		public:
			NamedObject(QObject* parent = nullptr);
			virtual ~NamedObject();

			QString name() const;
			virtual void setName(const QString& name);
	};
}

#endif
