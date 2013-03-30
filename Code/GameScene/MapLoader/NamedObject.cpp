#include "NamedObject.h"

#include <QtCore/QDebug>

gtg::NamedObject::NamedObject(QObject* parent)
	: QObject(parent)
	, m_name()
{}

gtg::NamedObject::~NamedObject()
{
}

QString gtg::NamedObject::name() const
{
	return m_name;
}


void gtg::NamedObject::setName(const QString& name)
{
	m_name = name;
}
