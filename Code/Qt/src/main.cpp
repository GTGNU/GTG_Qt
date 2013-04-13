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

#include "map/Map.h"
#include "map/Row.h"
#include "map/Tile.h"
#include "map/Class.h"
#include "map/Behavior.h"

#include "graphics/Texture.h"
#include "graphics/Layer.h"

#include "MenuHandler.h"

using namespace gtg;

/*! \brief Loads a tile class from a file
 *
 * \param engine The QML engine where it should be loaded and registered
 * \param fileName The qml file where the Class component is defined
 */
void loadTileClass(QQmlEngine* engine, const QString& fileName)
{
	qDebug() << "Loading tile definition in" << fileName;

	QQmlComponent component{engine, fileName};
	QObject* object = component.create();
	map::Class* type = qobject_cast<map::Class*>(object);

	if (type && type->behavior() && type->texture())
		engine->rootContext()->setContextProperty(type->name(), type);
	else
		qWarning() << "Error loading tile class in" << fileName << ":";

	for (auto& error : component.errors())
		qDebug() << "Error:" << error;
}

/*! \brief Calls loadTileClass for each qml file in the given directory
 *
 * \param engine The QML engine where classes should be loaded and registered
 * \param location The directory to be inspected
 */
void loadTileClasses(QQmlEngine* engine, const QString& location)
{
	QDir tileDefDir{location};
	for (QString& entry : tileDefDir.entryList(QDir::Files))
		loadTileClass(engine, tileDefDir.absoluteFilePath(entry));
}

int main(int argc, char* argv[])
{
	// export the gtg.tile package
	qmlRegisterType<gfx::Texture> ("gtg.gfx", 1, 5, "Texture"   );
	qmlRegisterType<gfx::Layer>   ("gtg.gfx", 1, 5, "Layer"   );

	qmlRegisterType<map::Behavior>("gtg.map", 1, 5, "Behavior");
	qmlRegisterType<map::Class>   ("gtg.map", 1, 5, "Class"   );

	// export the gtg.map package
	qmlRegisterType<map::Tile>("gtg.map", 1, 5, "Tile");
	qmlRegisterType<map::Row> ("gtg.map", 1, 5, "Row" );
	qmlRegisterType<map::Map> ("gtg.map", 1, 5, "Map" );

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

	// Load tile classes
	loadTileClasses(view.engine(), tilesSource);

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
