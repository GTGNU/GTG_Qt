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
			SIGNAL(open()),
			this->mapDisplay,
			SLOT(openHandler()) );

	this->connect(	this->topPanel,
			SIGNAL(save()),
			this->mapDisplay,
			SLOT(saveHandler()) );

	this->connect(	this->mapDisplay,
			SIGNAL(load(const int, const int)),
			this->topPanel,
			SLOT(mapLoadHandler(const int, const int)) );

	this->connect(	this->mapDisplay,
			SIGNAL(edited()),
			this->topPanel,
			SLOT(mapEditHandler()) );

	this->mapArea->setWidget(this->mapDisplay);

	this->layout->addWidget(this->topPanel);
	this->layout->addWidget(this->mapArea);

	this->setCentralWidget(new QWidget);
	this->centralWidget()->setLayout(layout);

	this->setWindowTitle(WINDOW_TITLE);

	this->mapDisplay->load("foo.qml");
	this->topPanel->setShowWarning(true);
}

MainWindow::~MainWindow()
{
	delete this->mapDisplay;

	delete this->topPanel;
	delete this->mapArea;

	delete this->layout;
}
