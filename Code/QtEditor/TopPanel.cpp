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

	QPushButton* tileButton = new QPushButton();
	QPushButton* saveButton = new QPushButton("Save");
	QPushButton* resetButton = new QPushButton("Reset");
	QLineEdit* widthLineEdit = new QLineEdit();
	QLineEdit* heightLineEdit = new QLineEdit();

	tileButton->setIcon(icon);
	tileButton->setIconSize(QSize(64, 64));
	tileButton->setFixedSize(80, 80);

	formLayout->addRow(new QLabel("Width:"), widthLineEdit);
	formLayout->addRow(new QLabel("Height:"), heightLineEdit);

	buttonLayout->addWidget(saveButton);
	buttonLayout->addWidget(resetButton);

	layout->addWidget(tileButton);
	layout->addLayout(formLayout);
	layout->addLayout(buttonLayout);

	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	this->setLayout(layout);
}
