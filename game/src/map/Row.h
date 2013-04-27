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

#ifndef ROW_H
#define ROW_H

#include <QtCore/QRectF>

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

#include "util/ChildList.h"

namespace gtg
{
	namespace map
	{
		class Tile;
		class Map;

		/*!
		 * \brief This class is almost a wrapper for a list of tiles
		 */
		class Row
			: public QQuickItem
		{
			Q_OBJECT

			Q_PROPERTY(int mapY READ mapY)
			Q_PROPERTY(gtg::map::Map* map READ map)

			Q_PROPERTY(QQmlListProperty<gtg::map::Tile> tiles READ tilesQml)
			Q_CLASSINFO("DefaultProperty", "tiles")

			private:
				int m_mapY;
				ChildList<Tile> m_tiles;

				//! Virtual function inherited from QQuickItem. See Qt documentation.
				/*!
				 * \param node The node to update (see the Qt Scene Graph framework)
				 * \param updatePaintNode
				 * \return The updated node
				 */
				QSGNode* updatePaintNode(QSGNode* node,
						QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

			public:
				explicit Row(QQuickItem* parent = nullptr);
				~Row();

				//! x coordinate getter (in pixels)
				int x() const;
				//! y coordinate getter (in pixels)
				int y() const;
				//! y coordinate getter (in pixels)
				int width() const;
				//! width getter (in pixels)
				int height() const;
				//! height getter (in pixels)
				QRectF boundingRect() const;

				//! y coordinate getter (in tiles)
				int mapY() const;
				//! Returns the parent map
				gtg::map::Map* map() const;

				//! Returns the list of child tiles
				ChildList<gtg::map::Tile> tiles() const;
				//! Returns a QQmlListProperty of tiles. This is just for QML, you should prefer tiles() in C++ code
				QQmlListProperty<gtg::map::Tile> tilesQml();

				//! Find the index of a given Tile
				/*!
				 * \param object The tile to find
				 * \return The index of the tile or -1 if it's not found
				 */
				int indexOf(const Tile* object) const;

				friend class Map;
		};
	}
}

QML_DECLARE_TYPE(gtg::map::Row)

#endif
