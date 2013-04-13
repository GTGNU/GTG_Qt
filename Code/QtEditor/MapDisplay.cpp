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

	this->setGridSize(2, 2);
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

		for(TileButton* j : i)
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

	this->setGeometry(QRect(0, 0, width*64, height*64));
}

void MapDisplay::gridSizeChangedHandler(const int width, const int height)
{
	if(width != this->grid.size()
	||(this->grid[0].size() > 0
	&& height != this->grid[0].size()))
		this->setGridSize(width, height);
}
