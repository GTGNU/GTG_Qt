#ifndef TILE_H
#define TILE_H

#include <QtCore/QFile>
#include <QtCore/QRegExp>
#include <QtCore/QTextStream>
#include <QtGui/QIcon>

#include "config.h"

namespace gtgeditor
{
	class Tile
	{
	public:
		Tile(const QString& path);
		~Tile();

		const QIcon* getIcon() const;
		const QString& getName() const;
		const QString& getPath() const;
		const QString getFileName() const;
		QString serialize() const;

	protected:
		QIcon* m_icon;
		QString m_name;
		QString m_path;
	};
}

#endif
