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

	class Tile
		: public QQuickItem
	{
		Q_OBJECT

		Q_PROPERTY(
				QQmlListProperty<gtg::tile::Layer> layers
				READ layersQml)

		Q_PROPERTY(gtg::tile::Behavior* behavior
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

			QSGNode* updatePaintNode(QSGNode* node,
					QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

		public:
			Tile(QQuickItem* parent = nullptr);
			~Tile();

			QQmlListProperty<gtg::tile::Layer> layersQml();

			gtg::tile::Behavior* behavior() const;
			void setBehavior(gtg::tile::Behavior* behavior);

			int mapX() const;
			int mapY() const;

			gtg::Row* row() const;
			gtg::Map* map() const;

			unsigned layerCount() const;

			Q_INVOKABLE unsigned indexOfLayer(gtg::tile::Layer* layer) const;

			Q_INVOKABLE void unshiftLayer(gtg::tile::Layer* layer);
			Q_INVOKABLE void pushLayer(gtg::tile::Layer* layer);
			Q_INVOKABLE void addLayer(unsigned index, gtg::tile::Layer* layer);

			Q_INVOKABLE void removeLayer(gtg::tile::Layer* layer);
			Q_INVOKABLE void removeLayer(unsigned index);

			Q_INVOKABLE void replaceLayer(
					gtg::tile::Layer* prev,
					gtg::tile::Layer* layer);

			Q_INVOKABLE void replaceLayer(unsigned index, gtg::tile::Layer* layer);


			friend class Player;

		signals:
			void layerAdded(gtg::tile::Layer* newLayer);
			void layerRemoved(gtg::tile::Layer* removedLayer);

			void behaviorChanged(
					gtg::tile::Behavior* previousBehavior,
					gtg::tile::Behavior* newBehavior);

			void playerEntered(gtg::Player* player);
			void playerExited(gtg::Player* player);
	};
}

QML_DECLARE_TYPE(gtg::Tile)

#endif
