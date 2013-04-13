#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class TopPanel : public QWidget
{
public:
	TopPanel();

protected:
	QHBoxLayout* layout;
	QFormLayout* formLayout;
	QFormLayout* buttonLayout;

	QPushButton* tileButton;
	QPushButton* saveButton;
	QPushButton* resetButton;
	QLineEdit* widthLineEdit;
	QLineEdit* heightLineEdit;
};
