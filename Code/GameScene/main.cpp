/*
 * Copyright 2013 xcv_
 *
 * This file is part of Grand Theft Gentoo.
 *
 * Grand Theft Gentoo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3.
 *
 * Grand Theft Gentoo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Grand Theft Gentoo.  If not, see <http://www.gnu.org/licenses/>.
 */

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

	// Quit when Qt.quit() is called
	QObject::connect(view.engine(), &QQmlEngine::quit, [&]() {
		qDebug() << "quit()";
		app.quit();
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
