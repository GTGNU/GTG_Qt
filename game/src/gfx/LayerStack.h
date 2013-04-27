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

#include <QtQuick/QQuickItem>

class QSGNode;
class QQuickItem;

namespace gtg
{
	namespace gfx
	{
		class Layer;

		class LayerStack;

		class LayerStack
			: public QObject
		{
			Q_OBJECT

			Q_PROPERTY(unsigned length READ count)

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
				//! Required by QML_REGISTER_TYPE, do not use
				explicit LayerStack(QObject* parent = nullptr);

				//! Theoretically the only constructor
				explicit LayerStack(QQuickItem* item, QObject* parent = nullptr);
				~LayerStack();


				//! The number of layers
				unsigned count() const;

				//! Get the specified element of the list
				Q_INVOKABLE gtg::gfx::Layer* at(unsigned index) const;

				/*!
				 * \brief Search for a layer
				 *
				 * \param layer The layer to look for
				 * \return The index where the layer is
				 */
				Q_INVOKABLE unsigned indexOf(gtg::gfx::Layer* layer) const;


				//! Alias for push, needed by QmlListAdapter
				void append(gtg::gfx::Layer* layer);

				/*!
				 * \brief Prepend a layer
				 *
				 * \param layer The layer to prepend
				 */
				Q_INVOKABLE void unshift(gtg::gfx::Layer* layer);

				/*!
				 * \brief Append a layer
				 *
				 * \param layer The layer to append
				 */
				Q_INVOKABLE void push(gtg::gfx::Layer* layer);

				/*!
				 * \brief Insert a layer
				 *
				 * \param index Where the layer will be inserted
				 * \param layer The layer to append
				 */
				Q_INVOKABLE void insert(unsigned index, gtg::gfx::Layer* layer);


				/*!
				 * \brief Remove a layer
				 *
				 * \param layer The layer to remove
				 */
				Q_INVOKABLE void remove(gtg::gfx::Layer* layer);

				/*!
				 * \brief Remove a layer
				 *
				 * \param index The index of the layer to be removed
				 */
				Q_INVOKABLE void remove(unsigned index);


				//! Remove all layers from the list
				Q_INVOKABLE void clear();


				/*!
				 * \brief Replace a layer
				 *
				 * \param prev The layer to be replaced
				 * \param layer The new layer
				 */
				Q_INVOKABLE void replace(
						gtg::gfx::Layer* prev,
						gtg::gfx::Layer* layer);

				/*!
				 * \brief Replace a layer
				 *
				 * \param index The index of the layer to be replaced
				 * \param layer The new layer
				 */
				Q_INVOKABLE void replace(unsigned index, gtg::gfx::Layer* layer);


				//! WARNING: Call only from some point inside a updatePaintNode() function
				bool applyChanges(QSGNode* node);
				//! WARNING: Call only from some point inside a updatePaintNode() function
				void updateNode(QSGNode* node);

			signals:
				void layerAdded(unsigned index, Layer* layer);
				void layerRemoved(unsigned index, Layer* layer);
		};
	}
}

QML_DECLARE_TYPE(gtg::gfx::LayerStack)

#endif
