#ifndef TILE_H
#define TILE_H

#include <QtCore/QFile>
#include <QtCore/QRegExp>
#include <QtCore/QTextStream>
#include <QtGui/QIcon>

#include "config.h"

class Tile
{
public:
	Tile(const QString& path);
	~Tile();

	const QIcon* getIcon() const;
	const QString& getName() const;
	QString serialize() const;

protected:
	QString m_name;
	QIcon* m_icon;
};

#endif
