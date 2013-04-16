#include "TopPanel.h"

TopPanel::TopPanel()
{
	this->layout = new QHBoxLayout();
	this->formLayout = new QFormLayout();
	this->buttonLayout = new QFormLayout();

	this->tileChooser = new TileChooser(TILES_DIR);
	this->openButton = new QPushButton(OPEN_BTN_LABEL);
	this->saveButton = new QPushButton(SAVE_BTN_LABEL);

	this->widthLineEdit
		= new QLineEdit(QString::number(DEFAULT_GRID_WIDTH));

	this->heightLineEdit
		= new QLineEdit(QString::number(DEFAULT_GRID_HEIGHT));

	this->tileChooser->setFixedSize(	TILE_CHOOSER_WIDTH,
						TILE_CHOOSER_HEIGHT );

	this->connect(	this->widthLineEdit,
			SIGNAL(editingFinished()),
			SLOT(editingFinishedHandler()) );

	this->connect(	this->heightLineEdit,
			SIGNAL(editingFinished()),
			SLOT(editingFinishedHandler()) );

	this->connect(	this->openButton,
			SIGNAL(released()),
			SLOT(openHandler()) );

	this->connect(	this->saveButton,
			SIGNAL(released()),
			SLOT(saveHandler()) );

	this->formLayout->addRow(	new QLabel(WIDTH_FORM_LABEL),
					this->widthLineEdit );

	this->formLayout->addRow(	new QLabel(HEIGHT_FORM_LABEL),
					this->heightLineEdit );

	this->buttonLayout->addWidget(this->openButton);
	this->buttonLayout->addWidget(this->saveButton);

	this->layout->addWidget(this->tileChooser);
	this->layout->addLayout(formLayout);
	this->layout->addLayout(buttonLayout);

	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	this->setLayout(layout);
}

TopPanel::~TopPanel()
{
	delete this->tileChooser;
	delete this->saveButton;
	delete this->widthLineEdit;
	delete this->heightLineEdit;

	delete this->formLayout;
	delete this->buttonLayout;

	delete this->layout;
}

const TileChooser* TopPanel::getTileChooser() const
{
	return this->tileChooser;
}

void TopPanel::setShowWarning(bool value)
{
	this->showWarning = value;
}

void TopPanel::editingFinishedHandler()
{
	const int width = this->widthLineEdit->text().toInt();
	const int height = this->heightLineEdit->text().toInt();

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
	this->widthLineEdit->setText(QString::number(width));
	this->heightLineEdit->setText(QString::number(height));
}

void TopPanel::mapEditedHandler()
{
	this->setShowWarning(true);
}
