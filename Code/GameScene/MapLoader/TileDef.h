#ifndef TILEDEF_H
#define TILEDEF_H

#include <QtCore/QObject>

#include "NamedObject.h"

namespace gtg
{
	template <class Def>
	class TileDef
		: public NamedObject
	{
		protected:
			bool m_nameSet;

		protected:
			QString m_name;
			static QHash<QString, Def*> m_defs;

		public:
			TileDef(QObject* parent = nullptr);
			virtual ~TileDef();

			virtual void setName(const QString& name);

			static Def* find(const QString& key);
			static void registerDef(Def* def);
			static void unregisterDef(Def* def);
	};
}

template <class Def>
QHash<QString, Def*> gtg::TileDef<Def>::m_defs;

template <class Def>
gtg::TileDef<Def>::TileDef(QObject* parent)
	: NamedObject(parent)
	, m_nameSet(false)
{}

template <class Def>
gtg::TileDef<Def>::~TileDef()
{}

template <class Def>
void gtg::TileDef<Def>::setName(const QString& name)
{
	qDebug() << "TileDef<" << this << "> setName(" << name << ")";
	if (name != m_name) {
		if (m_nameSet)
			unregisterDef(static_cast<Def*>(this));

		NamedObject::setName(name);
		registerDef(static_cast<Def*>(this));
		m_nameSet = true;
	}
}

template <class Def>
Def* gtg::TileDef<Def>::find(const QString& key)
{
	return m_defs[key];
}

template <class Def>
void gtg::TileDef<Def>::registerDef(Def* def)
{
	if (!m_defs.contains(def->name())) {
		m_defs.insert(def->name(), def);
		qDebug() << "Registered " << def << def->name();
	} else {
		qWarning() << "Could not register" << def << def->name()
			<< ": already exists";
	}
}

template <class Def>
void gtg::TileDef<Def>::unregisterDef(Def* def)
{
	for (auto it = m_defs.begin(); it != m_defs.end(); it++) {
		if (it.key() == def->name()) {
			if (it.value() == def) {
				m_defs.erase(it);
				qDebug() << def << def->name() << "unregistered successfully";
				return;
			} else {
				qWarning() << "Found partial match at unregisterDef(" << def << "):"
					<< it.key() << "=>" << it.value();
			}
		}
	}
}

#endif
