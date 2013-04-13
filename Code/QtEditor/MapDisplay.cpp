#include "MapDisplay.h"

#include <iostream>

MapDisplay::MapDisplay() : gridWidth(0), gridHeight(0), grid(0)
{
	this->layout = new QGridLayout();

	this->setLayout(layout);

	this->setGridSize(5, 5);
}

MapDisplay::~MapDisplay()
{
	delete this->layout;
}

void MapDisplay::setGridSize(const int width, const int height)
{
	this->grid.resize(width);

	int rowIndex = 0;
	int columnIndex = 0;

	for(std::vector<QPushButton*> i : this->grid)
	{
		i.resize(height);

		rowIndex = 0;

		for(QPushButton* j : i)
		{
			QPixmap pixmap("../Qt/assets/grass_tall.png");

			QIcon icon(pixmap.copy(64, 64, 64, 64));

			j = new QPushButton();

			j->setIcon(icon);
			j->setIconSize(QSize(64, 64));
			j->setFixedSize(64, 64);

			this->layout->addWidget(j, rowIndex++, columnIndex);
		}

		columnIndex++;
	}
}
