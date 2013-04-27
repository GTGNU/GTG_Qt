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

#ifndef TILE_H
#define TILE_H

#include <QtCore/QList>
#include <QtCore/QString>

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

#include "gfx/LayerStack.h"

namespace gtg
{
	class FloatingEntity;

	namespace gfx
	{
		class Layer;
	}

	namespace map
	{
		class Row;
		class Map;
		class Behavior;

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
					QQmlListProperty<gtg::gfx::Layer> layerList
					READ layerQmlList)

			Q_PROPERTY(
					gtg::gfx::LayerStack* layers
					READ layers)

			Q_PROPERTY(
					gtg::map::Behavior* behavior
					READ behavior
					WRITE setBehavior
					NOTIFY behaviorChanged)

			Q_PROPERTY(int mapX READ mapX)
			Q_PROPERTY(int mapY READ mapY)

			Q_PROPERTY(gtg::map::Row* row READ row)
			Q_PROPERTY(gtg::map::Map* map READ map)

			Q_CLASSINFO("DefaultProperty", "layerList")

			private:
				gfx::LayerStack m_layers;
				Behavior* m_behavior;

				//! Virtual function inherited from QQuickItem. See Qt documentation.
				/*!
				 * \param node The node to update (see the Qt Scene Graph framework)
				 * \param updatePaintNode
				 * \return The updated node
				 */
				QSGNode* updatePaintNode(QSGNode* node,
						QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

			public:
				explicit Tile(QQuickItem* parent = nullptr);
				~Tile();

				//! Access to the layer stack
				const gtg::gfx::LayerStack* layers() const;
				gtg::gfx::LayerStack* layers();

				//! Returns a QQmlListProperty of tiles. This is just a QML accessor.
				QQmlListProperty<gtg::gfx::Layer> layerQmlList();

				//! Returns the attached Behavior object
				gtg::map::Behavior* behavior() const;
				//! Sets the attached Behavior object
				void setBehavior(gtg::map::Behavior* behavior);

				//! x coordinate getter (in tiles)
				int mapX() const;
				//! y coordinate getter (in tiles)
				int mapY() const;

				//! Returns the parent row
				gtg::map::Row* row() const;
				//! Equivalent to row()->map()
				gtg::map::Map* map() const;

			signals:
				void behaviorChanged(
						gtg::map::Behavior* previousBehavior,
						gtg::map::Behavior* newBehavior);
		};
	}
}

QML_DECLARE_TYPE(gtg::map::Tile)

#endif
