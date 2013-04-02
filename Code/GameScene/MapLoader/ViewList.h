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
