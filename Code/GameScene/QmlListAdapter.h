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

#ifndef LISTADAPTER_H
#define LISTADAPTER_H

#include <QtCore/QDebug>
#include <QtCore/QList>

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickWindow>

namespace gtg
{
	template <class List, class T>
	struct QmlListAdapter
	{
		QmlListAdapter(List* list)
			: m_list(list)
		{
		}

		static void append(QQmlListProperty<T>* p, T* value)
		{
			reinterpret_cast<List*>(p->data)->append(value);
		}

		static int count(QQmlListProperty<T>* p)
		{
			return reinterpret_cast<List*>(p->data)->count();
		}

		static T* at(QQmlListProperty<T>* p, int index)
		{
			return reinterpret_cast<List*>(p->data)->at(index);
		}

		static void clear(QQmlListProperty<T>* p)
		{
			reinterpret_cast<List*>(p->data)->clear();
		}

		QQmlListProperty<T> toQmlListProperty(QObject* parent = nullptr)
		{
			return QQmlListProperty<T>(parent, m_list,
					QmlListAdapter<List,T>::append,
					QmlListAdapter<List,T>::count,
					QmlListAdapter<List,T>::at,
					QmlListAdapter<List,T>::clear);
		}

		private:
			List* m_list;
	};


	template <class T, class List>
	QQmlListProperty<T> adapt(List& list, QObject* parent = nullptr)
	{
		return QmlListAdapter<List, T>(&list).toQmlListProperty(nullptr);
	}
}

#endif
