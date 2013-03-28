#include <QtGui/QGuiApplication>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);

	MainWindow window("qml/");
	window.show();

	return app.exec();
}
