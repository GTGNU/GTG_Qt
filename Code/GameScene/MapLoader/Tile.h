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
