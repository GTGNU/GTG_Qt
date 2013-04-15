#include "Tile.h"

Tile::Tile(const QString& path)
{
	QFile file(path);

	file.open(QIODevice::ReadOnly | QIODevice::Text);

	QTextStream in(&file);
	QRegExp nameRegExp("name:\\s*'[^']*'", Qt::CaseInsensitive);
	QRegExp fileRegExp("file:\\s*'[^']*'", Qt::CaseInsensitive);

	bool foundName = false;
	bool foundImage = false;

	while(!in.atEnd() && (!foundName || !foundImage)) {
		QString line = in.readLine();

		if(line.contains(nameRegExp) && !foundName) {
			int openQuotePos = line.indexOf('\'');
			int closeQuotePos = line.lastIndexOf('\'')-openQuotePos;

			this->name = line.mid(openQuotePos+1, closeQuotePos-1);

			foundName = true;
		}
		else if(line.contains(fileRegExp) && !foundImage) {
			int openQuotePos = line.indexOf('\'');
			int closeQuotePos = line.lastIndexOf('\'')-openQuotePos;

			line = line.mid(openQuotePos+1, closeQuotePos-1);

			QPixmap pixmap(QString(ASSETS_DIR)+"/"+line);

			this->icon = new QIcon(pixmap.copy(	TILE_OFFSET_X,
								TILE_OFFSET_Y,
								TILE_WIDTH,
								TILE_HEIGHT ));

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

const QString& Tile::getName() const
{
	return this->name;
}

QString Tile::serialize() const
{
	return QString(TILE_TEMPLATE).arg(this->name);
}
