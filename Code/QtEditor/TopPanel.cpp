#include "TopPanel.h"

TopPanel::TopPanel()
{
	this->layout = new QHBoxLayout();
	this->formLayout = new QFormLayout();
	this->buttonLayout = new QFormLayout();

	this->tileChooser = new TileChooser(TILES_DIR);
	this->saveButton = new QPushButton(SAVE_BTN_LABEL);
	this->resetButton = new QPushButton(RESET_BTN_LABEL);

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

	this->connect(	this->resetButton,
			SIGNAL(released()),
			SLOT(resetHandler()) );

	this->connect(	this->saveButton,
			SIGNAL(released()),
			SLOT(saveHandler()) );

	this->formLayout->addRow(	new QLabel(WIDTH_FORM_LABEL),
					this->widthLineEdit );

	this->formLayout->addRow(	new QLabel(HEIGHT_FORM_LABEL),
					this->heightLineEdit );

	this->buttonLayout->addWidget(this->saveButton);
	this->buttonLayout->addWidget(this->resetButton);

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
	delete this->resetButton;
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

void TopPanel::editingFinishedHandler()
{
	emit gridSizeChanged(	this->widthLineEdit->text().toInt(),
				this->heightLineEdit->text().toInt() );
}

void TopPanel::resetHandler()
{
	emit reset();
}

void TopPanel::saveHandler()
{
	emit save();
}
