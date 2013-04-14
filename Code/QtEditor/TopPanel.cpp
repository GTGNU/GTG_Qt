#include "TopPanel.h"

TopPanel::TopPanel()
{
	this->layout = new QHBoxLayout();
	this->formLayout = new QFormLayout();
	this->buttonLayout = new QFormLayout();

	this->tileChooser = new TileChooser("tiles");
	this->saveButton = new QPushButton("Save");
	this->resetButton = new QPushButton("Reset");
	this->widthLineEdit = new QLineEdit("2");
	this->heightLineEdit = new QLineEdit("2");

	this->connect(	this->widthLineEdit,
			SIGNAL(editingFinished()),
			SLOT(editingFinishedHandler()) );

	this->connect(	this->heightLineEdit,
			SIGNAL(editingFinished()),
			SLOT(editingFinishedHandler()) );

	this->connect(	this->resetButton,
			SIGNAL(released()),
			SLOT(resetHandler()) );

	this->formLayout->addRow(new QLabel("Width:"), this->widthLineEdit);
	this->formLayout->addRow(new QLabel("Height:"), this->heightLineEdit);

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
