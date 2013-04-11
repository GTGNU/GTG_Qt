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

#include "MenuHandler.h"

#include <QtCore/QDebug>
#include <QtCore/QUrl>

#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickWindow>

gtg::MenuHandler::MenuHandler(QQuickView* view,
		QString mapSource, QObject* parent)
	: QObject(parent)
	, m_view(view)
	, m_mapSource(mapSource)
{
}

void gtg::MenuHandler::play()
{
	// Load the map
	m_view->setSource(QUrl::fromLocalFile(m_mapSource));
}

void gtg::MenuHandler::quit()
{
	m_view->close();
}


