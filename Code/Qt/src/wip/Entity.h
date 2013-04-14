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

#ifndef FLOATINGENTITY_H
#define FLOATINGENTITY_H

#include <QtCore/QList>

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

#include "graphics/LayerStack.h"

namespace gtg
{
	namespace map
	{
		class Map;
		class Tile;
	}

	namespace floating
	{
		class Entity
			: public QQuickItem
		{
			Q_OBJECT

			Q_PROPERTY(
					QQmlListProperty<gtg::gfx::Layer> layers
					READ layersQml)

			Q_PROPERTY(
					QQmlListProperty<gtg::map::Tile> intersectingTiles
					READ intersectingTilesQml)

			Q_PROPERTY(
					QString type
					READ type
					WRITE setType)

			Q_PROPERTY(
					gtg::map::Map* map
					READ map
					WRITE setMap)

			Q_PROPERTY(int x READ x WRITE setX)
			Q_PROPERTY(int y READ y WRITE setY)

			Q_PROPERTY(int mapX READ mapX)
			Q_PROPERTY(int mapX2 READ mapX2)

			Q_PROPERTY(int mapY READ mapY)
			Q_PROPERTY(int mapY2 READ mapY2)

			Q_PROPERTY(unsigned mapWidth READ mapWidth)
			Q_PROPERTY(unsigned mapHeight READ mapHeight)

			Q_CLASSINFO("DefaultProperty", "layers")

			private:
				gfx::LayerStack m_layers;
				QSet<Tile*> m_intersectingTiles;
				Map* m_map;

				void updateIntersectingTiles(int oldOriginValue,
						int oldBottomRightValue, bool isX)

				void updateIntersectingTiles(
						int oldMapCoord, int newMapCoord,
						std::function<Tile*(int)> getTile, bool atOrigin
						QSet<Tile*>& removed, QSet<Tile*>& added);

				//! Virtual function inherited from QQuickItem. See Qt documentation.
				/*!
				 * \param node The node to update (see the Qt Scene Graph framework)
				 * \param updatePaintNode
				 * \return The updated node
				 */
				QSGNode* updatePaintNode(QSGNode* node,
						QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

			public:
				Entity(QQuickItem* parentItem = nullptr);
				~Entity();

				//! Returns a QQmlListProperty of tiles. This is just a QML accessor.
				QQmlListProperty<gtg::gfx::Layer> layersQml();

				QList<Tile*> intersectingTiles() const;
				QQmlListProperty<gtg::map::Tile> intersectingTilesQml();

				gtg::map::Map* map() const;
				void setMap(gtg::map::Map* map);

				int x() const;
				void setX(int x);

				int y() const;
				void setY(int y);

				int mapX() const;
				int mapX2() const;

				int mapY() const;
				int mapY2() const;

				int mapWidth() const;
				int mapHeight() const;

				Q_INVOKABLE bool intersects(gtg::map::Tile* tile) const;

				Q_INVOKABLE void move(int dx, int dy);
				Q_INVOKABLE void move(QPoint d);

			signals:
				void enteredTile(gtg::map::Tile*);
				void leftTile(gtg::map::Tile*);
		};
	}
}

QML_DECLARE_TYPE(gtg::floating::Entity)

#endif
