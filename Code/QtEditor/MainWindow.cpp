#include "MainWindow.h"

MainWindow::MainWindow() : m_mapEdited(false)
{
	m_layout = new QVBoxLayout();

	m_topPanel = new TopPanel();
	m_mapDisplay = new MapDisplay(m_topPanel->getTileChooser());
	m_mapArea = new QScrollArea();

	this->connect(	m_mapDisplay,
			SIGNAL(edited()),
			SLOT(mapEditedHandler()) );

	this->connect(	m_topPanel,
			SIGNAL(save()),
			SLOT(mapResetHandler()) );

	this->connect(	m_topPanel,
			SIGNAL(gridSizeChanged(const int, const int)),
			SLOT(mapResetHandler()) );

	this->connect(	m_topPanel,
			SIGNAL(gridSizeChanged(const int, const int)),
			m_mapDisplay,
			SLOT(gridSizeChangedHandler(const int, const int)) );

	this->connect(	m_topPanel,
			SIGNAL(open()),
			m_mapDisplay,
			SLOT(openHandler()) );

	this->connect(	m_topPanel,
			SIGNAL(save()),
			m_mapDisplay,
			SLOT(saveHandler()) );

	this->connect(	m_mapDisplay,
			SIGNAL(load(const int, const int)),
			m_topPanel,
			SLOT(mapLoadHandler(const int, const int)) );

	this->connect(	m_mapDisplay,
			SIGNAL(edited()),
			m_topPanel,
			SLOT(mapEditedHandler()) );

	m_mapArea->setWidget(m_mapDisplay);

	m_layout->addWidget(m_topPanel);
	m_layout->addWidget(m_mapArea);

	this->setCentralWidget(new QWidget);
	this->centralWidget()->setLayout(m_layout);

	this->setWindowTitle(WINDOW_TITLE);
}

MainWindow::~MainWindow()
{
	delete m_mapDisplay;

	delete m_topPanel;
	delete m_mapArea;

	delete m_layout;
}

void MainWindow::mapEditedHandler()
{
	m_mapEdited = true;
}

void MainWindow::mapResetHandler()
{
	m_mapEdited = false;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if(m_mapEdited) {
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
