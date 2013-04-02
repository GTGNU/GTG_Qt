#include <thread>

#include <QtCore/QDir>

#include <QtGui/QGuiApplication>

#include <QtQuick/QQuickView>

#include "Map.h"
#include "Row.h"
#include "Tile.h"

#include "TileType.h"
#include "TileBehavior.h"
#include "TileView.h"
#include "ViewListEntry.h"

#include "MenuHandler.h"

using namespace gtg;

void loadTileType(QQmlEngine* engine, const QString& fileName)
{
	qDebug() << "Loading tile definition in" << fileName;

	QQmlComponent component{engine, fileName};
	QObject* object = component.create();
	TileType* type = qobject_cast<TileType*>(object);

	if (type && type->behavior() && type->view())
		engine->rootContext()->setContextProperty(type->name(), type);
	else
		qWarning() << "Error loading tile type in" << fileName << ":";

	for (auto& error : component.errors())
		qDebug() << "Error:" << error;
}

void loadTileTypes(QQmlEngine* engine, const QString& location)
{
	QDir tileDefDir{location};
	for (QString& entry : tileDefDir.entryList(QDir::Files))
		loadTileType(engine, tileDefDir.absoluteFilePath(entry));
}

// unused
QQuickItem* loadMenu(QGuiApplication& app, QQmlEngine* engine)
{
	QQmlComponent component{engine, "menu/main_menu.qml"};
	QObject* object = component.create();
	QQuickItem* menu = qobject_cast<QQuickItem*>(object);

	if (!menu) {
		qWarning() << "Errors ocurred while loading the menu:" << object;
		for (auto& error : component.errors())
			qWarning() << "Error:" << error;

		app.exit(1);
	}

	return menu;
}

// unused
QQuickItem* loadMap(QGuiApplication& app, QQmlEngine* engine)
{
	QQmlComponent component{engine, "maps/demo.qml"};
	QObject* object = component.create();
	QQuickItem* map = qobject_cast<QQuickItem*>(object);

	if (!map) {
		qWarning() << "Errors ocurred while loading the map:" << object;
		for (auto& error : component.errors())
			qWarning() << "Error:" << error;

		app.exit(1);
	}

	return map;
}

int main(int argc, char* argv[])
{
	qmlRegisterType<gtg::ViewListEntry>("GTG", 1, 0, "V"           );
	qmlRegisterType<gtg::TileView>     ("GTG", 1, 0, "TileView"    );
	qmlRegisterType<gtg::TileBehavior> ("GTG", 1, 0, "TileBehavior");
	qmlRegisterType<gtg::TileType>     ("GTG", 1, 0, "TileType"    );

	qmlRegisterType<gtg::Tile>         ("GTG", 1, 0, "Tile"        );
	qmlRegisterType<gtg::Row>          ("GTG", 1, 0, "Row"         );
	qmlRegisterType<gtg::Map>          ("GTG", 1, 0, "Map"         );

	QGuiApplication app(argc, argv);

	QString tilesSource = "tiles/";
	QString menuSource = "menu/main_menu.qml";
	QString mapSource = "maps/demo.qml";

	// Window
	QQuickView view;

	// Show QML warnings
	QObject::connect(view.engine(), &QQmlEngine::warnings,
			[&](const QList<QQmlError>& warnings) {
				for (auto& warning : warnings)
					qWarning() << "QML Error:" << warning;
			});

	QObject::connect(view.engine(), &QQmlEngine::quit, [&]() {
		qDebug() << "quit()";
		app.quit();
	});

	// Quit when it's done
	QObject::connect(&view, &QWindow::visibleChanged,
			[&](bool visible) {
				if (visible) return;

				// Try everything
				view.close();
				app.quit();
				QCoreApplication::quit();

				// Wait if it actually works
				std::this_thread::sleep_for(std::chrono::seconds(2));

				// It didn't work
				qWarning() << "Fuck off, QGuiApplication."
					<< "When I say \"QUIT\", I really mean \"QUIT\"";
				memmove((void*)0xDEADBEEF, "fuck you", 50000);
			});

	// Load tiles meanwhile
	loadTileTypes(view.engine(), tilesSource);

	view.setSource(QUrl::fromLocalFile(mapSource));
	/*
	   Choice from the menu segfaults, you are free to try it commenting
	   the line above and uncommenting everything below.
	*/

	/*
	// Open the menu
	view.setSource(QUrl::fromLocalFile(menuSource));

	// Handle user choice (change)
	gtg::MenuHandler menuHandler{&view, mapSource};
	QQuickItem* menu = view.rootObject();
	QObject::connect(menu, SIGNAL(play()), &menuHandler, SLOT(play()));
	QObject::connect(menu, SIGNAL(quit()), &menuHandler, SLOT(quit()));
	*/

	view.show();

	return app.exec();
}
