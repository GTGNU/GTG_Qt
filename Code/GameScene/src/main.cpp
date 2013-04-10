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

#include "tile/Class.h"
#include "tile/Behavior.h"
#include "tile/Texture.h"
#include "tile/Layer.h"

#include "MenuHandler.h"

using namespace gtg;

void loadTileClass(QQmlEngine* engine, const QString& fileName)
{
	qDebug() << "Loading tile definition in" << fileName;

	QQmlComponent component{engine, fileName};
	QObject* object = component.create();
	tile::Class* type = qobject_cast<tile::Class*>(object);

	if (type && type->behavior() && type->texture())
		engine->rootContext()->setContextProperty(type->name(), type);
	else
		qWarning() << "Error loading tile class in" << fileName << ":";

	for (auto& error : component.errors())
		qDebug() << "Error:" << error;
}

void loadTileClasses(QQmlEngine* engine, const QString& location)
{
	QDir tileDefDir{location};
	for (QString& entry : tileDefDir.entryList(QDir::Files))
		loadTileClass(engine, tileDefDir.absoluteFilePath(entry));
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
	qmlRegisterType<tile::Texture> ("gtg.tile", 1, 4, "Texture"   );
	qmlRegisterType<tile::Behavior>("gtg.tile", 1, 4, "Behavior");
	qmlRegisterType<tile::Class>   ("gtg.tile", 1, 4, "Class"   );
	qmlRegisterType<tile::Layer>   ("gtg.tile", 1, 4, "Layer"   );

	qmlRegisterType<Tile>("gtg.map", 1, 4, "Tile");
	qmlRegisterType<Row> ("gtg.map", 1, 4, "Row" );
	qmlRegisterType<Map> ("gtg.map", 1, 4, "Map" );

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
	loadTileClasses(view.engine(), tilesSource);

	//view.setSource(QUrl::fromLocalFile(mapSource));
	/*
	   Choice from the menu segfaults, you are free to try it commenting
	   the line above and uncommenting everything below.
	*/


	// Open the menu
	view.setSource(QUrl::fromLocalFile(menuSource));

	// Handle user choice (change)
	gtg::MenuHandler menuHandler{&view, mapSource};
	QQuickItem* menu = view.rootObject();
	QObject::connect(menu, SIGNAL(play()), &menuHandler, SLOT(play()), Qt::QueuedConnection);
	QObject::connect(menu, SIGNAL(quit()), &menuHandler, SLOT(quit()), Qt::QueuedConnection);


	view.show();

	return app.exec();
}
