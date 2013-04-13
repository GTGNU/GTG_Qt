#include "MapDisplay.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QScrollArea>

MapDisplay::MapDisplay()
{
	QHBoxLayout* layout = new QHBoxLayout();

	QScrollArea* scrollArea = new QScrollArea();

	layout->addWidget(scrollArea);
	this->setLayout(layout);
}
