#include <QtGui/QGuiApplication>

#include <QtQuick/QQuickView>

#include "Map.h"
#include "Row.h"
#include "Tile.h"

int main(int argc, char* argv[])
{
	qmlRegisterType<gtg::Tile>("GTG", 1, 0, "Tile");
	qmlRegisterType<gtg::Row>("GTG", 1, 0, "Row");
	qmlRegisterType<gtg::Map>("GTG", 1, 0, "Map");

	QGuiApplication app(argc, argv);

	QQuickView view {QUrl::fromLocalFile("maps/demo.qml")};
	view.show();

	return app.exec();
}
