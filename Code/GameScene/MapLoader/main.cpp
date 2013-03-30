#include <QtCore/QDir>

#include <QtGui/QGuiApplication>

#include <QtQuick/QQuickView>

#include "Map.h"
#include "Row.h"
#include "Tile.h"

#include "TileType.h"
#include "TileBehavior.h"
#include "TileView.h"

#include "MenuHandler.h"

using namespace gtg;

void loadTileType(QQmlEngine* engine, const QString& fileName)
{
	qDebug() << "Loading tile definition at" << fileName;

	QQmlComponent component{engine, fileName};
	component.create();
/*
	TileType* type = qobject_cast<TileType*>(object);
	if (type)
		return TileType::registerDef(type);

	TileBehavior* behavior = qobject_cast<TileBehavior*>(object);
	if (behavior)
		return TileBehavior::registerDef(behavior);

	TileView* view = qobject_cast<TileView*>(object);
	if (view)
		return TileView::registerDef(view);
*/
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
	qmlRegisterType<gtg::TileView>    ("GTG", 1, 0, "TileView"    );
	qmlRegisterType<gtg::TileBehavior>("GTG", 1, 0, "TileBehavior");
	qmlRegisterType<gtg::TileType>    ("GTG", 1, 0, "TileType"    );

	qmlRegisterType<gtg::Tile>        ("GTG", 1, 0, "Tile"        );
	qmlRegisterType<gtg::Row>         ("GTG", 1, 0, "Row"         );
	qmlRegisterType<gtg::Map>         ("GTG", 1, 0, "Map"         );

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

	// Load tiles meanwhile
	loadTileTypes(view.engine(), tilesSource);

	// Open the menu
	view.setSource(QUrl::fromLocalFile(mapSource));

	// Refresh tiles
	QObject::connect(&view, &QQuickView::beforeSynchronizing, TileView::forceUpdate);

	// Handle user choice (not working yet)
	/*gtg::MenuHandler menuHandler{&view, mapSource};
	QQuickItem* menu = view.rootObject();
	QObject::connect(menu, SIGNAL(play()), &menuHandler, SLOT(play()));
	QObject::connect(menu, SIGNAL(quit()), &menuHandler, SLOT(quit()));*/

	view.show();

	return app.exec();
}
