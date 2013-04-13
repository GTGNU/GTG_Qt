#include "MapDisplay.h"

MapDisplay::MapDisplay() : gridWidth(0), gridHeight(0), grid(0)
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

	for(std::vector<QPushButton*>& i : this->grid)
	{
		for(QPushButton* j : i)
		{
			delete j;
		}
	}

	this->grid.clear();
	this->grid.resize(width);

	int rowIndex = 0;
	int columnIndex = 0;

	for(std::vector<QPushButton*>& i : this->grid)
	{
		rowIndex = 0;

		i.resize(height, NULL);

		for(QPushButton* j : i)
		{
			QPixmap pixmap("../Qt/assets/grass_tall.png");

			QIcon icon(pixmap.copy(64, 64, 64, 64));

			if(j == NULL)
			{
				j = new QPushButton();

				j->setIcon(icon);
				j->setIconSize(QSize(64, 64));
				j->setFixedSize(64, 64);

				this->layout->addWidget(j, rowIndex, columnIndex);
			}

			rowIndex++;
		}

		columnIndex++;
	}

	this->setGeometry(QRect(0, 0, width*64, height*64));
}

void MapDisplay::gridSizeChangedHandler(const int width, const int height)
{
	this->setGridSize(width, height);
}
