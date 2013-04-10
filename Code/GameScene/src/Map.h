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

#include "helpers/ChildList.h"

namespace gtg
{
	class Tile;
	class Row;

	class Map
	: public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(unsigned int tileSize READ tileSize WRITE setTileSize)

		Q_PROPERTY(QQmlListProperty<gtg::Row> rows READ qmlRows)
		Q_CLASSINFO("DefaultProperty", "rows")

		private:
			unsigned int m_tileSize;
			ChildList<Row> m_rows;

			QSGNode* updatePaintNode(QSGNode* node,
					QQuickItem::UpdatePaintNodeData* updatePaintNodeData) override;

		public:
			Map(QQuickItem* parent = nullptr);
			~Map();

			unsigned int tileSize() const;
			void setTileSize(unsigned int tileSize);

			ChildList<gtg::Row> rows() const;
			QQmlListProperty<gtg::Row> qmlRows();

			int indexOf(const Row* object) const;

			Q_INVOKABLE gtg::Tile* tileAt(int x, int y);
	};
}

QML_DECLARE_TYPE(gtg::Map)

#endif
