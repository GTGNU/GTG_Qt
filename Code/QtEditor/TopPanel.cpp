#include "TopPanel.h"

TopPanel::TopPanel()
{
	this->layout = new QHBoxLayout();
	this->formLayout = new QFormLayout();
	this->buttonLayout = new QFormLayout();

	QPixmap pixmap("assets/grass_tall.png");

	QIcon icon(pixmap.copy(64, 64, 64, 64));

	this->tileButton = new QPushButton();
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

	this->tileButton->setIcon(icon);
	this->tileButton->setIconSize(QSize(64, 64));
	this->tileButton->setFixedSize(80, 80);

	this->formLayout->addRow(new QLabel("Width:"), this->widthLineEdit);
	this->formLayout->addRow(new QLabel("Height:"), this->heightLineEdit);

	this->buttonLayout->addWidget(this->saveButton);
	this->buttonLayout->addWidget(this->resetButton);

	this->layout->addWidget(this->tileButton);
	this->layout->addLayout(formLayout);
	this->layout->addLayout(buttonLayout);

	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	this->setLayout(layout);
}

TopPanel::~TopPanel()
{
	delete this->tileButton;
	delete this->saveButton;
	delete this->resetButton;
	delete this->widthLineEdit;
	delete this->heightLineEdit;

	delete this->formLayout;
	delete this->buttonLayout;

	delete this->layout;
}

void TopPanel::editingFinishedHandler()
{
	emit gridSizeChanged(	this->widthLineEdit->text().toInt(),
				this->heightLineEdit->text().toInt() );
}
