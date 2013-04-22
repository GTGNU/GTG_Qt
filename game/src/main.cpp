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

#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>

#include <QtQuick/QQuickView>

#include "util/Registered.h"
#include "util/qmlengine.h"

#include "map/Map.h"
#include "map/Row.h"
#include "map/Tile.h"
#include "map/Class.h"
#include "map/Behavior.h"

#include "gfx/Texture.h"
#include "gfx/Layer.h"

#include "MenuHandler.h"

/*! \brief Loads a tile class from a file
 *
 * \param engine The QML engine where it should be loaded and registered
 * \param fileName The qml file where the Class component is defined
 */
/*void loadTileClass(QQmlEngine* engine, const QString& fileName)
{
	qDebug() << "Loading tile definition in" << fileName;

	QQmlComponent component(engine, fileName);
	QObject* object = component.create();
	map::Class* type = qobject_cast<map::Class*>(object);

	if (type && type->behavior() && type->texture())
		engine->rootContext()->setContextProperty(type->name(), type);
	else
		qWarning() << "Error loading tile class in" << fileName << ":";

	for (auto& error : component.errors())
		qDebug() << "Error:" << error;
}*/

/*! \brief Calls loadTileClass for each qml file in the given directory
 *
 * \param engine The QML engine where classes should be loaded and registered
 * \param location The directory to be inspected
 */
/*void loadTileClasses(QQmlEngine* engine, const QString& location)
{
	engine->rootContext()->setContextProperty("Registry", Registry::global());
	QDir tileDefDir(location);
	for (QString& entry : tileDefDir.entryList(QDir::Files))
		loadTileClass(engine, tileDefDir.absoluteFilePath(entry));
}*/

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);

	QString menuSource = "menu/main_menu.qml";
	QString mapSource = "assets/maps/demo.qml";

	// Window
	QSharedPointer<QQmlEngine> engine = gtg::qmlengine::init(1,5);
	QQuickView view(engine.data(), nullptr);

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

	// Load tile classes
	//loadTileClasses(view.engine(), tilesSource);

	// Open the menu
	view.setSource(QUrl::fromLocalFile(menuSource));

	// Handle user choice (change)
	gtg::MenuHandler menuHandler(view, mapSource);
	menuHandler.setMenu(view.rootObject());

	view.show();

	return app.exec();
}
