#include "TopPanel.h"

TopPanel::TopPanel()
{
	m_layout = new QHBoxLayout();
	m_formLayout = new QFormLayout();
	m_buttonLayout = new QFormLayout();

	m_tileChooser = new TileChooser(TILES_DIR);
	m_openButton = new QPushButton(OPEN_BTN_LABEL);
	m_saveButton = new QPushButton(SAVE_BTN_LABEL);

	m_widthLineEdit
		= new QLineEdit(QString::number(DEFAULT_GRID_WIDTH));

	m_heightLineEdit
		= new QLineEdit(QString::number(DEFAULT_GRID_HEIGHT));

	m_tileChooser->setFixedSize(	TILE_CHOOSER_WIDTH,
						TILE_CHOOSER_HEIGHT );

	this->connect(	m_widthLineEdit,
			SIGNAL(editingFinished()),
			SLOT(editingFinishedHandler()) );

	this->connect(	m_heightLineEdit,
			SIGNAL(editingFinished()),
			SLOT(editingFinishedHandler()) );

	this->connect(	m_openButton,
			SIGNAL(released()),
			SLOT(openHandler()) );

	this->connect(	m_saveButton,
			SIGNAL(released()),
			SLOT(saveHandler()) );

	m_formLayout->addRow(	new QLabel(WIDTH_FORM_LABEL),
					m_widthLineEdit );

	m_formLayout->addRow(	new QLabel(HEIGHT_FORM_LABEL),
					m_heightLineEdit );

	m_buttonLayout->addWidget(m_openButton);
	m_buttonLayout->addWidget(m_saveButton);

	m_layout->addWidget(m_tileChooser);
	m_layout->addLayout(m_formLayout);
	m_layout->addLayout(m_buttonLayout);

	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	this->setLayout(m_layout);
}

TopPanel::~TopPanel()
{
	delete m_tileChooser;
	delete m_saveButton;
	delete m_widthLineEdit;
	delete m_heightLineEdit;

	delete m_formLayout;
	delete m_buttonLayout;

	delete m_layout;
}

const TileChooser* TopPanel::getTileChooser() const
{
	return m_tileChooser;
}

void TopPanel::setShowWarning(bool value)
{
	m_showWarning = value;
}

void TopPanel::editingFinishedHandler()
{
	int width = m_widthLineEdit->text().toInt();
	int height = m_heightLineEdit->text().toInt();

	if(width < 1)
	{
		width = 1;

		m_widthLineEdit->setText("1");
	}

	if(height < 1)
	{
		height = 1;

		m_heightLineEdit->setText("1");
	}

	emit gridSizeChanged(width, height);
}

void TopPanel::openHandler()
{
	emit open();
}

void TopPanel::saveHandler()
{
	emit save();
}

void TopPanel::mapLoadHandler(const int width, const int height)
{
	m_widthLineEdit->setText(QString::number(width));
	m_heightLineEdit->setText(QString::number(height));
}

void TopPanel::mapEditedHandler()
{
	this->setShowWarning(true);
}
