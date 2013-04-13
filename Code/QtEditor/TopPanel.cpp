#include "TopPanel.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtGui/QPixmap>
#include <QtGui/QIcon>

TopPanel::TopPanel()
{
	QHBoxLayout* layout = new QHBoxLayout();
	QFormLayout* formLayout = new QFormLayout;
	QFormLayout* buttonLayout = new QFormLayout;

	QPixmap pixmap("../Qt/assets/grass_tall.png");

	QIcon icon(pixmap.copy(64, 64, 64, 64));

	this->tileButton = new QPushButton();
	this->saveButton = new QPushButton("Save");
	this->resetButton = new QPushButton("Reset");
	this->widthLineEdit = new QLineEdit();
	this->heightLineEdit = new QLineEdit();

	this->tileButton->setIcon(icon);
	this->tileButton->setIconSize(QSize(64, 64));
	this->tileButton->setFixedSize(80, 80);

	formLayout->addRow(new QLabel("Width:"), this->widthLineEdit);
	formLayout->addRow(new QLabel("Height:"), this->heightLineEdit);

	buttonLayout->addWidget(this->saveButton);
	buttonLayout->addWidget(this->resetButton);

	layout->addWidget(this->tileButton);
	layout->addLayout(formLayout);
	layout->addLayout(buttonLayout);

	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	this->setLayout(layout);
}
