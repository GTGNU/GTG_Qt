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

	while(!in.atEnd() && (!foundName || !foundImage))
	{
		QString line = in.readLine();

		if(line.contains(nameRegExp) && !foundName)
		{
			int openQuotePos = line.indexOf('\'');
			int closeQuotePos = line.lastIndexOf('\'')-openQuotePos;

			this->name = line.mid(openQuotePos+1, closeQuotePos-1);

			foundName = true;
		}
		else if(line.contains(fileRegExp) && !foundImage)
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

QString Tile::serialize() const
{
	QTextStream tileString(new QString());

	tileString	<< "\t\tTile {\n"
			<< "\t\t	T.Layer { texture: %1.texture }\n"
			<< "\n"
			<< "\t\t	behavior: %1.behavior\n"
			<< "\t\t}\n\n";

	return tileString.string()->arg(this->name);
}
