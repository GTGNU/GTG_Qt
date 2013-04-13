#include "MapDisplay.h"

MapDisplay::MapDisplay()
{
	this->layout = new QHBoxLayout();

	this->scrollArea = new QScrollArea();

	this->layout->addWidget(scrollArea);

	this->setLayout(layout);
}

MapDisplay::~MapDisplay()
{
	delete this->scrollArea;

	delete this->layout;
}
