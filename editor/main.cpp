#include <QtWidgets/QApplication>

#include "MainWindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	gtgeditor::MainWindow mainWindow;

	mainWindow.show();

	return app.exec();
}
