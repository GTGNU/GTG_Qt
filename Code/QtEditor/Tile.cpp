#include "Tile.h"

Tile::Tile(const QString& path)
{
	QFile file(path);

	file.open(QIODevice::ReadOnly);

	QTextStream in(&file);
	QRegExp regexp("file:\\s*'[^']*'", Qt::CaseInsensitive);

	bool foundImage = false;

	while(!in.atEnd() && !foundImage)
	{
		QString line = in.readLine();

		if(line.contains(regexp))
		{
			int openQuotePos = line.indexOf('\'');
			int closeQuotePos = line.lastIndexOf('\'')-openQuotePos;

			line = line.mid(openQuotePos+1, closeQuotePos-1);

			QPixmap pixmap("assets/"+line);

			this->icon = new QIcon(pixmap.copy(64, 64, 64, 64));

			foundImage = true;
		}
	}
}

Tile::~Tile()
{
	delete this->icon;
}

const QIcon* Tile::getIcon() const
{
	return this->icon;
}
