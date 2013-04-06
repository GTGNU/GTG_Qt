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

#ifndef VIEWLIST_H
#define VIEWLIST_H

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

			Tile* m_tile;
			QList<ViewListEntry*> m_entries;

			struct Change {
				enum {
					ADD,
					REMOVE,
					CLEAR
				} action;

				unsigned index;
				ViewListEntry* entry;
			};
			QList<Change> m_changes;

		public:
			ViewList(Tile* tile);
			~ViewList();

			void append(ViewListEntry* view);
			void insert(unsigned index, ViewListEntry* view);

			void remove(ViewListEntry* view);
			void remove(unsigned index);

			int count() const;
			unsigned indexOf(ViewListEntry* entry) const;
			ViewListEntry* at(unsigned index) const;

			void clear();

			// call only from the rendering thread
			bool applyChanges(QSGNode* node);
			void updateNode(QSGNode* node);
	};
}

#endif
