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
