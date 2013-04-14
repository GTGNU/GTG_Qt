#include <QtWidgets/QApplication>

#include "MainWindow.h"

#include "Tile.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	Tile tile("tiles/water.qml");

	MainWindow mainWindow;

	mainWindow.show();

	return app.exec();
}
