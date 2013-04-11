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

#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <QtCore/QObject>

class QQuickView;

namespace gtg
{
	/*! \brief Handlers the user choice in the main menu
	 */
	class MenuHandler
			: public QObject {
		Q_OBJECT

		private:
			QQuickView* m_view;
			QString m_mapSource;

		public:
			MenuHandler(QQuickView* view,
					QString mapSource,
					QObject* parent = nullptr);

		public slots:
			void play();
			void quit();
	};
}

#endif
