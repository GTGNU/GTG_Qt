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
