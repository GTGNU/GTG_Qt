#include "MapDisplay.h"

#include <iostream>

MapDisplay::MapDisplay(const TileChooser* chooser)
:	gridWidth(0),
	gridHeight(0),
	grid(0),
	tileChooser(chooser)
{
	this->layout = new QGridLayout();

	this->layout->setContentsMargins(QMargins(0, 0, 0, 0));
	this->layout->setSpacing(0);

	this->setLayout(layout);

	this->setGridSize(DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT);
}

MapDisplay::~MapDisplay()
{
	delete this->layout;
}

void MapDisplay::setGridSize(const int width, const int height)
{
	if(height > this->grid.size())
		this->grid.resize(height);

	for(int i = 0; i < this->grid.size(); i++) {

		if(width > this->grid[i].size())
			this->grid[i].resize(width);

		for(int j = 0; j < this->grid[i].size(); j++) {

			TileButton*& button = this->grid[i][j];

			if(i > height-1 || j > width-1) {
				this->layout->removeWidget(button);
			}
			else if(button == NULL) {
				button = new TileButton(tileChooser);

				this->connect(	button,
						SIGNAL(pressed()),
						SLOT(tilePressedHandler()) );

				this->layout->addWidget(	button,
								i,
								j );
			}
		}

		if(width < this->grid[i].size())
			this->grid[i].resize(width);
	}

	if(height < this->grid.size())
		this->grid.resize(height);

	this->setGeometry(QRect(0, 0, width*TILE_WIDTH, height*TILE_HEIGHT));

	emit edited();
}

void MapDisplay::gridSizeChangedHandler(const int width, const int height)
{
	if(width != this->grid.size()
	||(this->grid[0].size() > 0
	&& height != this->grid[0].size()))
		this->setGridSize(width, height);
}

void MapDisplay::openHandler()
{
	this->load(QFileDialog::getOpenFileName());
}

void MapDisplay::saveHandler()
{
	QFile file(QFileDialog::getSaveFileName());

	if(!file.fileName().isEmpty()) {
		file.open(QIODevice::WriteOnly | QIODevice::Text);

		QTextStream out(&file);

		out << this->serialize();

		file.close();
	}
}

void MapDisplay::tilePressedHandler()
{
	TileButton* sender = (TileButton*)QObject::sender();

	sender->setTile(this->tileChooser->getCurrentTile());

	emit edited();
}

void MapDisplay::load(const QString& path)
{
	QFile file(path);

	file.open(QIODevice::ReadOnly | QIODevice::Text);

	QTextStream in(&file);
	QRegExp rowRegExp("\\s*Row", Qt::CaseInsensitive);
	QRegExp tileRegExp("\\s*Tile", Qt::CaseInsensitive);
	QRegExp textureRegExp("\\s*texture:\\s*[^\\s]", Qt::CaseInsensitive);

	this->clear();

	int rowIndex = -1;
	int columnIndex = -1;

	while(!in.atEnd()) {
		QString line = in.readLine();

		bool foundTexture = false;

		if(line.contains(rowRegExp)) {
			this->grid.push_back(QVector<TileButton*>());

			rowIndex++;

			columnIndex = -1;
		}
		else if(line.contains(tileRegExp)) {
			columnIndex++;

			foundTexture = false;
		}
		else if(line.contains(textureRegExp) && !foundTexture) {
			const int labelLength = QString(TEXTURE_LABEL).length();
			const int labelPos = line.indexOf(TEXTURE_LABEL);

			QRegExp spaceRegExp("\\s*");
			QRegExp valueRegExp("[^ ]*");

			spaceRegExp.indexIn(line, labelPos+labelLength+1);

			const int valuePos =	spaceRegExp.pos(0)+
						spaceRegExp.cap(0).length();

			valueRegExp.indexIn(line, valuePos);

			const int lastDotPos
				= valueRegExp.cap(0).lastIndexOf('.');

			const QString name(valueRegExp.cap(0).left(lastDotPos));

			TileButton* button = new TileButton(this->tileChooser);

			button->setTile(this->tileChooser->getTileByName(name));

			this->grid.last().push_back(button);

			this->connect(	button,
					SIGNAL(released()),
					SLOT(tileClickHandler()) );

			this->layout->addWidget(	button,
							rowIndex,
							columnIndex );

			foundTexture = true;
		}
	}

	QRect rect(0, 0, (columnIndex+1)*TILE_WIDTH, (rowIndex+1)*TILE_HEIGHT);

	this->setGeometry(rect);

	file.close();

	emit load(columnIndex+1, rowIndex+1);
}

QString MapDisplay::serialize() const
{
	QString gridString;

	for(QVector<TileButton*> i : this->grid) {
		QString tileRowString;

		for(TileButton* j : i) {
			tileRowString.append(j->getTile()->serialize());
		}

		gridString.append(QString(ROW_TEMPLATE).arg(tileRowString));
	}

	return QString(MAP_TEMPLATE).arg(gridString);
}

void MapDisplay::clear()
{
	delete this->layout;

	this->layout = new QGridLayout();

	this->layout->setContentsMargins(QMargins(0, 0, 0, 0));
	this->layout->setSpacing(0);

	this->setLayout(this->layout);

	for(QVector<TileButton*>& i : this->grid) {
		for(TileButton* j : i) {
			delete j;
		}
	}

	this->grid.clear();
}
