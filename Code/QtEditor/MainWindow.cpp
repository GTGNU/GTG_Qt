#include "MainWindow.h"

MainWindow::MainWindow()
{
	this->layout = new QVBoxLayout();

	this->topPanel = new TopPanel();
	this->mapDisplay = new MapDisplay();

	this->layout->addWidget(this->topPanel);
	this->layout->addWidget(this->mapDisplay);

	this->setCentralWidget(new QWidget);
	this->centralWidget()->setLayout(layout);

	this->setWindowTitle("Map Editor");
}

MainWindow::~MainWindow()
{
	delete this->topPanel;
	delete this->mapDisplay;

	delete this->layout;
}
