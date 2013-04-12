#include "MapDisplay.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>

MapDisplay::MapDisplay()
{
	QHBoxLayout* layout = new QHBoxLayout;

	QPushButton* button = new QPushButton("DRAWAREA");

	layout->addWidget(button);
	this->setLayout(layout);
}
