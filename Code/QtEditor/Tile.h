#pragma once

#include <QtCore/QFile>
#include <QtCore/QRegExp>
#include <QtCore/QTextStream>
#include <QtGui/QIcon>

class Tile
{
public:
	Tile(const QString& path);
	~Tile();

	const QIcon* getIcon() const;
	QString serialize() const;

protected:
	QString name;
	QIcon* icon;
};
