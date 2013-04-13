#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>

#include "TopPanel.h"
#include "MapDisplay.h"

class MainWindow : public QMainWindow
{
public:
	MainWindow();
	~MainWindow();

protected:
	QVBoxLayout* layout;

	TopPanel* topPanel;
	MapDisplay* mapDisplay;
};
