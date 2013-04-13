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
	Q_OBJECT

public:
	TopPanel();
	~TopPanel();

protected:
	QHBoxLayout* layout;
	QFormLayout* formLayout;
	QFormLayout* buttonLayout;

	QPushButton* tileButton;
	QPushButton* saveButton;
	QPushButton* resetButton;
	QLineEdit* widthLineEdit;
	QLineEdit* heightLineEdit;

signals:
	void gridSizeChanged(const int width, const int height);

public slots:
	void editingFinishedHandler();
};
