/*
 * Copyright 2013 xcv_
 *
 * This file is part of Grand Theft Gentoo.
 *
 * Foobar is free software: you can redistribute it and/or modify
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

#ifndef VIEWLIST_H
#define VIEWLIST_H

#include <vector> // optimized for <bool>

#include <QtCore/QList>
#include <QtCore/QMultiMap>
#include <QtCore/QObject>

class QSGNode;

namespace gtg
{
	class Tile;
	class ViewListEntry;

	class ViewList
	{
		private:
			enum Action {
				ADD,
				REMOVE,
				CLEAR
			};

			Tile* m_tile;
			QList<ViewListEntry*> m_entries;

			QMultiMap<Action, int> m_changes;

		public:
			ViewList(Tile* tile);
			~ViewList();

			void append(ViewListEntry* view);

			void remove(ViewListEntry* view);
			void remove(int index);

			int count() const;

			ViewListEntry* at(int index) const;

			void clear();

			// call only from the rendering thread
			bool applyChanges(QSGNode* node);
			void updateTextures(QSGNode* node);
	};
}

#endif
