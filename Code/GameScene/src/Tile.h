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

#ifndef TILE_H
#define TILE_H

#include <QtCore/QList>
#include <QtCore/QString>

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

#include "tile/LayerStack.h"

namespace gtg
{
	class Player;
	class Row;
	class Map;

	namespace tile
	{
		class Behavior;
		class Layer;
	}

	/*!
	 * \brief Represents a Tile of the Map.
	 *
	 * This class takes care of the actual representation of a tile in the QML scene.
	 * It is mainly composed by a layer stack and a pointer to a Behavior object.
	 * To draw, it basically delegates to the layer stack object.
	 *
	 * It has no getters or setters for the layer stack, but it has some methods
	 * to manipulate it indirectly.
	 */
	class Tile
		: public QQuickItem
	{
		Q_OBJECT

		Q_PROPERTY(
				QQmlListProperty<gtg::tile::Layer> layers
				READ layersQml)

		Q_PROPERTY(
				gtg::tile::Behavior* behavior
				READ behavior
				WRITE setBehavior
				NOTIFY behaviorChanged)

		Q_PROPERTY(int mapX READ mapX)
		Q_PROPERTY(int mapY READ mapY)

		Q_PROPERTY(gtg::Row* row READ row)
		Q_PROPERTY(gtg::Map* map READ map)

		Q_PROPERTY(unsigned layerCount READ layerCount)

		Q_CLASSINFO("DefaultProperty", "layers")

		private:
			tile::LayerStack m_layers;
			tile::Behavior* m_behavior;

			Player* m_player;
			void setPlayer(Player* player);

			//! Virtual function inherited from QQuickItem. See Qt documentation.
			/*!
			 * \param node The node to update (see the Qt Scene Graph framework)
			 * \param updatePaintNode
			 * \return The updated node
			 */
			QSGNode* updatePaintNode(QSGNode* node,
					QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

		public:
			Tile(QQuickItem* parent = nullptr);
			~Tile();

			//! Returns a QQmlListProperty of tiles. This is just for QML, you should prefer tiles() in C++ code
			QQmlListProperty<gtg::tile::Layer> layersQml();

			//! Returns the attached Behavior object
			gtg::tile::Behavior* behavior() const;
			//! Sets the attached Behavior object
			void setBehavior(gtg::tile::Behavior* behavior);

			//! x coordinate getter (in tiles)
			int mapX() const;
			//! y coordinate getter (in tiles)
			int mapY() const;

			//! Returns the parent row
			gtg::Row* row() const;
			//! Equivalent to row()->map()
			gtg::Map* map() const;

			//! The number of layers in the stack
			unsigned layerCount() const;

			/*!
			 * \brief Search for a layer
			 *
			 * \param layer The layer to look for
			 * \return The index where the layer is
			 */
			Q_INVOKABLE unsigned indexOfLayer(gtg::tile::Layer* layer) const;

			/*!
			 * \brief Prepend a layer
			 *
			 * \param layer The layer to prepend
			 */
			Q_INVOKABLE void unshiftLayer(gtg::tile::Layer* layer);

			/*!
			 * \brief Append a layer
			 *
			 * \param layer The layer to append
			 */
			Q_INVOKABLE void pushLayer(gtg::tile::Layer* layer);

			/*!
			 * \brief Insert a layer
			 *
			 * \param index Where the layer will be inserted
			 * \param layer The layer to append
			 */
			Q_INVOKABLE void addLayer(unsigned index, gtg::tile::Layer* layer);

			/*!
			 * \brief Remove a layer
			 *
			 * \param layer The layer to remove
			 */
			Q_INVOKABLE void removeLayer(gtg::tile::Layer* layer);

			/*!
			 * \brief Remove a layer
			 *
			 * \param index The index of the layer to be removed
			 */
			Q_INVOKABLE void removeLayer(unsigned index);

			/*!
			 * \brief Replace a layer
			 *
			 * \param prev The layer to be replaced
			 * \param layer The new layer
			 */
			Q_INVOKABLE void replaceLayer(
					gtg::tile::Layer* prev,
					gtg::tile::Layer* layer);

			/*!
			 * \brief Replace a layer
			 *
			 * \param index The index of the layer to be replaced
			 * \param layer The new layer
			 */
			Q_INVOKABLE void replaceLayer(unsigned index, gtg::tile::Layer* layer);

			friend class Player;

		signals:
			void behaviorChanged(
					gtg::tile::Behavior* previousBehavior,
					gtg::tile::Behavior* newBehavior);

			void playerEntered(gtg::Player* player);
			void playerExited(gtg::Player* player);
	};
}

QML_DECLARE_TYPE(gtg::Tile)

#endif
