#include "MapDisplay.h"

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
	delete this->layout;

	this->layout = new QGridLayout();

	this->layout->setContentsMargins(QMargins(0, 0, 0, 0));
	this->layout->setSpacing(0);

	this->setLayout(this->layout);

	for(QVector<TileButton*>& i : this->grid)
	{
		for(TileButton* j : i)
		{
			delete j;
		}
	}

	this->grid.clear();
	this->grid.resize(width);

	int rowIndex = 0;
	int columnIndex = 0;

	for(QVector<TileButton*>& i : this->grid)
	{
		rowIndex = 0;

		i.resize(height);

		for(TileButton*& j : i)
		{
			if(j == NULL)
			{
				j = new TileButton(tileChooser);

				this->layout->addWidget(	j,
								rowIndex,
								columnIndex );
			}

			rowIndex++;
		}

		columnIndex++;
	}

	this->setGeometry(QRect(0, 0, width*TILE_WIDTH, height*TILE_HEIGHT));
}

void MapDisplay::gridSizeChangedHandler(const int width, const int height)
{
	if(width != this->grid.size()
	||(this->grid[0].size() > 0
	&& height != this->grid[0].size()))
		this->setGridSize(width, height);
}

void MapDisplay::resetHandler()
{
	if(!this->grid.empty())
		this->setGridSize(this->grid.size(), this->grid[0].size());
}

void MapDisplay::saveHandler()
{
	QFile file(QFileDialog::getSaveFileName());

	if(!file.fileName().isEmpty())
	{
		file.open(QIODevice::WriteOnly | QIODevice::Text);

		QTextStream out(&file);

		out << this->serialize();

		file.close();
	}
}

QString MapDisplay::serialize() const
{
	QString gridString;

	for(QVector<TileButton*> i : this->grid)
	{
		QString tileRowString;

		for(TileButton* j : i)
		{
			tileRowString.append(j->getTile()->serialize());
		}

		gridString.append(QString(ROW_TEMPLATE).arg(tileRowString));
	}

	return QString(MAP_TEMPLATE).arg(gridString);
}
