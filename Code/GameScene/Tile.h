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

#include "ViewList.h"

namespace gtg
{
	class Player;
	class Row;
	class Map;

	class TileView;
	class TileBehavior;
	class TileType;

	class Tile
		: public QQuickItem
	{
		Q_OBJECT

		Q_PROPERTY(QQmlListProperty<gtg::ViewListEntry> views READ viewsQml)
		Q_PROPERTY(gtg::TileBehavior* behavior READ behavior WRITE setBehavior NOTIFY behaviorChanged)

		Q_PROPERTY(int mapX READ mapX)
		Q_PROPERTY(int mapY READ mapY)

		Q_PROPERTY(gtg::Row* row READ row)
		Q_PROPERTY(gtg::Map* map READ map)

		private:
			int m_updateCount = 0;  // number of updates (just for debugging)

			ViewList m_views;

			TileBehavior* m_behavior;

			Player* m_player;
			void setPlayer(Player* player);

			QSGNode* updatePaintNode(QSGNode* node,
					QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

		public:
			Tile(QQuickItem* parent = nullptr);
			~Tile();

			QQmlListProperty<ViewListEntry> viewsQml();

			gtg::TileBehavior* behavior() const;
			void setBehavior(gtg::TileBehavior* behavior);

			int mapX() const;
			int mapY() const;

			gtg::Row* row() const;
			gtg::Map* map() const;

			Q_INVOKABLE void addView(gtg::ViewListEntry* entry);
			Q_INVOKABLE void addView(unsigned index, gtg::ViewListEntry* entry);

			Q_INVOKABLE void removeView(unsigned index);
			Q_INVOKABLE void removeView(gtg::ViewListEntry* entry);

			Q_INVOKABLE void replaceView(unsigned index,
					gtg::ViewListEntry* entry);
			Q_INVOKABLE void replaceView(gtg::ViewListEntry* old,
					gtg::ViewListEntry* entry);

			Q_INVOKABLE unsigned viewCount() const;

			friend class Player;
			friend class ViewList;

		signals:
			void viewAdded(TileView* newTile);
			void viewRemoved(TileView* removedTile);
			void behaviorChanged(TileBehavior* previousBehavior,
					TileBehavior* newBehavior);

			void playerEntered(Player* player);
			void playerExited(Player* player);
	};
}

QML_DECLARE_TYPE(gtg::Tile)

#endif
