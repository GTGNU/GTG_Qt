#include "TopPanel.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>

TopPanel::TopPanel()
{
	QHBoxLayout* layout = new QHBoxLayout;

	QPushButton* button = new QPushButton("Tile");

	layout->addWidget(button);
	this->setLayout(layout);
}
