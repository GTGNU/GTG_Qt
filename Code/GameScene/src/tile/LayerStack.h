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

#ifndef TILELAYERSTACK_H
#define TILELAYERSTACK_H

#include <QtCore/QList>
#include <QtCore/QMultiMap>
#include <QtCore/QObject>

class QSGNode;

namespace gtg
{
	class Tile;

	namespace tile
	{
		class Layer;

		class LayerStack
		{
			private:
				Tile* m_tile;
				QList<Layer*> m_layers;

				struct Change {
					enum {
						ADD,
						REMOVE,
						CLEAR
					} action;

					unsigned index;
					Layer* layer;
				};

				QList<Change> m_changes;

			public:
				LayerStack(Tile* tile);
				~LayerStack();

				void append(Layer* layer);
				void insert(unsigned index, Layer* layer);

				void remove(Layer* layer);
				void remove(unsigned index);

				Layer* at(unsigned index) const;
				int count() const;
				unsigned indexOf(Layer* layer) const;

				void clear();

				// call only from the rendering thread
				bool applyChanges(QSGNode* node);
				void updateNode(QSGNode* node);
		};
	}
}

#endif
