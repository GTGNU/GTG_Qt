#include "MainWindow.h"

MainWindow::MainWindow()
{
	QVBoxLayout* layout = new QVBoxLayout();

	this->topPanel = new TopPanel;
	this->mapDisplay = new MapDisplay;

	layout->addWidget(this->topPanel);
	layout->addWidget(this->mapDisplay);

	this->setCentralWidget(new QWidget);
	this->centralWidget()->setLayout(layout);

	this->setWindowTitle("Map Editor");
}
