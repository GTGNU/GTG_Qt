#ifndef LISTFUNCTIONS_H
#define LISTFUNCTIONS_H

#include <vector>

#include <QtQml/QQmlListProperty>

namespace gtg
{
	template <class T>
	using QQmlListPropertyHelper = std::vector<T>;

	template <class T>
	void qqmllistproperty_append(QQmlListProperty<T>* data, T* value)
	{
		//std::cout << data << " passed to append()" << std::endl;

		reinterpret_cast<std::vector<T*>*>(data)->push_back(value);
	}

	template <class T>
	T* qqmllistproperty_at(QQmlListProperty<T>* data, int index)
	{
		//std::cout << data << " passed to at()" << std::endl;

		return reinterpret_cast<std::vector<T*>*>(data)->at(index);
	}

	template <class T>
	void qqmllistproperty_clear(QQmlListProperty<T>* data)
	{
		//std::cout << data << " passed to clear()" << std::endl;

		reinterpret_cast<std::vector<T*>*>(data)->clear();
	}

	template <class T>
	int qqmllistproperty_count(QQmlListProperty<T>* data)
	{
		//std::cout << data << " passed to count()" << std::endl;

		return reinterpret_cast<std::vector<T*>*>(data)->size();
	}
}

#endif
