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

#include <QtQuick/QQuickItem>

#include "graphics/LayerStack.h"

namespace gtg
{
	namespace map
	{
		class Map;
		class Tile;
	}

	class FloatingEntity
		: public QQuickItem
	{
		Q_OBJECT

		Q_PROPERTY(
				QQmlListProperty<gtg::Tile> intersectingTiles
				READ intersectingTilesQml)

		Q_PROPERTY(
				QString type
				READ type
				WRITE setType)

		Q_PROPERTY(
				gtg::Map* map
				READ map
				WRITE setMap)

		Q_PROPERTY(int mapX READ mapX)
		Q_PROPERTY(int mapX2 READ mapX2)
		Q_PROPERTY(int mapY READ mapY)
		Q_PROPERTY(int mapY2 READ mapY2)
		Q_PROPERTY(unsigned mapWidth READ mapWidth)
		Q_PROPERTY(unsigned mapHeight READ mapHeight)

		private:
			Map* m_map;

			//! Virtual function inherited from QQuickItem. See Qt documentation.
			/*!
			 * \param node The node to update (see the Qt Scene Graph framework)
			 * \param updatePaintNode
			 * \return The updated node
			 */
			QSGNode* updatePaintNode(QSGNode* node,
					QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

		public:
			FloatingEntity(QQuickItem* parentItem = nullptr);
			~FloatingEntity();

			QList<Tile*> intersectingTiles() const;
			QQmlListProperty<gtg::Tile> intersectingTilesQml();

			gtg::Map* map() const;
			void setMap(gtg::Map* map);

			int mapX() const;
			int mapX2() const;
			int mapY() const;
			int mapY2() const;
			int mapWidth() const;
			int mapHeight() const;

			Q_INVOKABLE bool intersects(gtg::Tile* tile) const;

			Q_INVOKABLE void move(int dx, int dy);
			Q_INVOKABLE void move(QPoint d);
	};
}

#endif
