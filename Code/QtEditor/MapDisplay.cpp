#include "MapDisplay.h"

#include <iostream>

MapDisplay::MapDisplay(const TileChooser* chooser)
:	m_gridWidth(0),
	m_gridHeight(0),
	m_grid(0),
	m_tileChooser(chooser)
{
	m_layout = new QGridLayout();

	m_layout->setContentsMargins(QMargins(0, 0, 0, 0));
	m_layout->setSpacing(0);

	this->setLayout(m_layout);

	this->setGridSize(DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT);
}

MapDisplay::~MapDisplay()
{
	delete m_layout;
}

void MapDisplay::setGridSize(const int width, const int height)
{
	if(height > m_grid.size())
		m_grid.resize(height);

	for(int i = 0; i < m_grid.size(); i++) {

		if(width > m_grid[i].size())
			m_grid[i].resize(width);

		for(int j = 0; j < m_grid[i].size(); j++) {

			TileButton*& button = m_grid[i][j];

			if(i > height-1 || j > width-1) {
				m_layout->removeWidget(button);
			}
			else if(button == NULL) {
				button = new TileButton(m_tileChooser);

				this->connect(	button,
						SIGNAL(pressed()),
						SLOT(tilePressedHandler()) );

				m_layout->addWidget(	button,
								i,
								j );
			}
		}

		if(width < m_grid[i].size())
			m_grid[i].resize(width);
	}

	if(height < m_grid.size())
		m_grid.resize(height);

	this->setGeometry(QRect(0, 0, width*TILE_WIDTH, height*TILE_HEIGHT));

	emit edited();
}

void MapDisplay::gridSizeChangedHandler(const int width, const int height)
{
	if(width != m_grid.size()
	||(m_grid[0].size() > 0
	&& height != m_grid[0].size()))
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

	sender->setTile(m_tileChooser->getCurrentTile());

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
			m_grid.push_back(QVector<TileButton*>());

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

			TileButton* button = new TileButton(m_tileChooser);

			button->setTile(m_tileChooser->getTileByName(name));

			m_grid.last().push_back(button);

			this->connect(	button,
					SIGNAL(released()),
					SLOT(tileClickHandler()) );

			m_layout->addWidget(	button,
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

	for(QVector<TileButton*> i : m_grid) {
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
	delete m_layout;

	m_layout = new QGridLayout();

	m_layout->setContentsMargins(QMargins(0, 0, 0, 0));
	m_layout->setSpacing(0);

	this->setLayout(m_layout);

	for(QVector<TileButton*>& i : m_grid) {
		for(TileButton* j : i) {
			delete j;
		}
	}

	m_grid.clear();
}
