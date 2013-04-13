#include "MainWindow.h"

MainWindow::MainWindow()
{
	this->layout = new QVBoxLayout();

	this->topPanel = new TopPanel();
	this->mapDisplay = new MapDisplay(this->topPanel->getTileChooser());
	this->mapArea = new QScrollArea();

	this->connect(	this->topPanel,
			SIGNAL(gridSizeChanged(const int, const int)),
			this->mapDisplay,
			SLOT(gridSizeChangedHandler(const int, const int)) );

	this->connect(	this->topPanel,
			SIGNAL(reset()),
			this->mapDisplay,
			SLOT(resetHandler()) );

	this->mapArea->setWidget(this->mapDisplay);

	this->layout->addWidget(this->topPanel);
	this->layout->addWidget(this->mapArea);

	this->setCentralWidget(new QWidget);
	this->centralWidget()->setLayout(layout);

	this->setWindowTitle("Map Editor");
}

MainWindow::~MainWindow()
{
	delete this->mapDisplay;

	delete this->topPanel;
	delete this->mapArea;

	delete this->layout;
}
