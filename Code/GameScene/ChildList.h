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

#ifndef CHILDLIST_H
#define CHILDLIST_H

#include <QtCore/QDebug>
#include <QtCore/QList>

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickWindow>

namespace gtg
{
	template <class T>
	class ChildList
	{
		private:
			QQuickItem& m_parent;

		public:
			ChildList(QQuickItem* parent)
				: m_parent(*parent)
			{}

			~ChildList()
			{}

			void append(T* value)
			{
				value->setParentItem(&m_parent);
			}

			int count() const
			{
				return m_parent.childItems().size();
			}

			T* at(int index) const
			{
				return qobject_cast<T*>(m_parent.childItems().at(index));
			}

			void clear()
			{
				for (QQuickItem* child : m_parent.childItems())
					child->setParentItem(m_parent.window()->contentItem());
			}

			int size() const
			{
				return count();
			}

			auto begin() const -> decltype(m_parent.childItems().begin())
			{
				return m_parent.childItems().begin();
			}

			auto begin() -> decltype(m_parent.childItems().begin())
			{
				return m_parent.childItems().begin();
			}

			auto end() const -> decltype(m_parent.childItems().end())
			{
				return m_parent.childItems().end();
			}

			auto end() -> decltype(m_parent.childItems().end())
			{
				return m_parent.childItems().end();
			}


			static void append(QQmlListProperty<T>* data, T* value)
			{
				reinterpret_cast<ChildList<T>*>(data)->append(value);
			}

			static int count(QQmlListProperty<T>* data)
			{
				return reinterpret_cast<ChildList<T>*>(data)->count();
			}

			static T* at(QQmlListProperty<T>* data, int index)
			{
				return reinterpret_cast<ChildList<T>*>(data)->at(index);
			}

			static void clear(QQmlListProperty<T>* data)
			{
				reinterpret_cast<ChildList<T>*>(data)->clear();
			}


			QQmlListProperty<T> toQmlListProperty()
			{
				return QQmlListProperty<T>(&m_parent, this,
						ChildList::append,
						ChildList::count,
						ChildList::at,
						ChildList::clear);
			}
	};
}

#endif
