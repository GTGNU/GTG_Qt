#include "MainWindow.h"

MainWindow::MainWindow() : mapEdited(false)
{
	this->layout = new QVBoxLayout();

	this->topPanel = new TopPanel();
	this->mapDisplay = new MapDisplay(this->topPanel->getTileChooser());
	this->mapArea = new QScrollArea();

	this->connect(	this->mapDisplay,
			SIGNAL(edited()),
			SLOT(mapEditedHandler()) );

	this->connect(	this->topPanel,
			SIGNAL(save()),
			SLOT(mapResetHandler()) );

	this->connect(	this->topPanel,
			SIGNAL(gridSizeChanged(const int, const int)),
			SLOT(mapResetHandler()) );

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
			SLOT(mapEditedHandler()) );

	this->mapArea->setWidget(this->mapDisplay);

	this->layout->addWidget(this->topPanel);
	this->layout->addWidget(this->mapArea);

	this->setCentralWidget(new QWidget);
	this->centralWidget()->setLayout(layout);

	this->setWindowTitle(WINDOW_TITLE);
}

MainWindow::~MainWindow()
{
	delete this->mapDisplay;

	delete this->topPanel;
	delete this->mapArea;

	delete this->layout;
}

void MainWindow::mapEditedHandler()
{
	this->mapEdited = true;
}

void MainWindow::mapResetHandler()
{
	this->mapEdited = false;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if(this->mapEdited) {
		QMessageBox::StandardButton result;

		result = QMessageBox::warning(	this,
						WARNING_TITLE,
						WARNING_EXIT,
						QMessageBox::Yes |
						QMessageBox::No,
						QMessageBox::No );

		if(result == QMessageBox::No)
			event->ignore();
	}
}
