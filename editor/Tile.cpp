#include "Tile.h"

using namespace gtgeditor;

Tile::Tile(const QString& path) : m_path(path)
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

			m_name = line.mid(openQuotePos+1, closeQuotePos-1);

			foundName = true;
		}
		else if(line.contains(fileRegExp) && !foundImage) {
			int openQuotePos = line.indexOf('\'');
			int closeQuotePos = line.lastIndexOf('\'')-openQuotePos;

			line = line.mid(openQuotePos+1, closeQuotePos-1);

			QPixmap pixmap(QString(IMAGES_DIR)+"/"+line);

			m_icon = new QIcon(pixmap.copy(	TILE_OFFSET_X,
							TILE_OFFSET_Y,
							TILE_WIDTH,
							TILE_HEIGHT ));

			foundImage = true;
		}
	}
}

Tile::~Tile()
{
	delete m_icon;
}

const QIcon* Tile::getIcon() const
{
	return m_icon;
}

const QString& Tile::getName() const
{
	return m_name;
}

const QString& Tile::getPath() const
{
	return m_path;
}

const QString Tile::getFileName() const
{
	QRegExp regExp("[^\\/]*$");

	regExp.indexIn(m_path);

	return regExp.cap(0);
}

QString Tile::serialize() const
{
	return QString(TILE_TEMPLATE).arg(m_name);
}
