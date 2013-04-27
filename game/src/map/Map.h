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

#ifndef MAP_H
#define MAP_H

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

#include "util/ChildList.h"

namespace gtg
{
	namespace map
	{
		class Tile;
		class Row;

		/*!
		 * \brief The top-level component of a map file.
		 *
		 * This class contains a list of rows, the size of tiles and
		 * an exported method to access a given file.
		 */
		class Map
			: public QQuickItem
		{
			Q_OBJECT

			Q_PROPERTY(QStringList requires READ requires WRITE setRequires)

			Q_PROPERTY(unsigned int tileSize READ tileSize WRITE setTileSize)

			Q_PROPERTY(QQmlListProperty<gtg::map::Row> rows READ rowsQml)
			Q_CLASSINFO("DefaultProperty", "rows")

			private:
				QStringList m_requires;
				bool m_requiresSet;

				unsigned int m_tileSize;
				ChildList<Row> m_rows;

				//! Virtual function inherited from QQuickItem. See Qt documentation.
				/*!
				 * \param node The node to update (see the Qt Scene Graph framework)
				 * \param updatePaintNode
				 * \return The updated node
				 */
				QSGNode* updatePaintNode(QSGNode* node,
						QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

			public:
				explicit Map(QQuickItem* parent = nullptr);
				~Map();

				//! requires getter
				QStringList requires() const;
				//! requires setter
				void setRequires(QStringList requires);

				//! tileSize getter
				unsigned int tileSize() const;
				//! tileSize setter
				void setTileSize(unsigned int tileSize);

				//! Returns the list of child rows
				ChildList<gtg::map::Row> rows() const;
				//! Returns a QQmlListProperty of rows. This is just for QML, you should prefer rows() in C++ code
				QQmlListProperty<gtg::map::Row> rowsQml();

				//! Find the index of a given Row
				/*!
				 * \param object The row to find
				 * \return The index of the row or -1 if it's not found
				 */
				int indexOf(const Row* object) const;

				//! Get a tile at the given map coordinates (x,y)
				/*!
				 * \param x x coordinate (left is x=0)
				 * \param y y coordinate (top is y=0)
				 * \return the tile at given coordinates or nullptr if not found
				 */
				Q_INVOKABLE gtg::map::Tile* tileAt(int x, int y);
		};
	}
}

QML_DECLARE_TYPE(gtg::map::Map)

#endif
