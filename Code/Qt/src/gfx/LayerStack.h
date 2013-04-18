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
class QQuickItem;

namespace gtg
{
	namespace gfx
	{
		class Layer;

		class LayerStack
		{
			private:
				QQuickItem* m_item;
				QList<Layer*> m_layers;

				/*! \brief Used to register a change that happened in the stack
				 *
				 * Since everything related to the scene graph is done in a
				 * separate thread but the layer stack can be altered at any
				 * moment, changes must be saved and applied in some updatePaintNode()
				 */
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
				LayerStack(QQuickItem* item);
				~LayerStack();

				//! Append a layer
				void append(Layer* layer);
				//! Insert a layer at the given index
				void insert(unsigned index, Layer* layer);

				//! Remove a layer
				void remove(Layer* layer);
				//! Remove a layer
				void remove(unsigned index);

				//! Access a layer at a given index
				Layer* at(unsigned index) const;
				//! Get the number of layers in the stack
				int count() const;
				//! Find the index of a layer in the stack
				unsigned indexOf(Layer* layer) const;

				//! Remove all layers
				void clear();

				//! WARNING: Call only from some point inside a updatePaintNode() function
				bool applyChanges(QSGNode* node);
				//! WARNING: Call only from some point inside a updatePaintNode() function
				void updateNode(QSGNode* node);
		};
	}
}

#endif
