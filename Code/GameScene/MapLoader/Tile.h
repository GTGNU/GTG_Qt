#ifndef TILE_H
#define TILE_H

#include <QtCore/QString>

#include <QtQuick/QQuickItem>

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

		Q_PROPERTY(QString type READ typeName WRITE setTypeName)

		Q_PROPERTY(gtg::TileView* view READ view)
		Q_PROPERTY(QString viewName READ viewName WRITE setViewName)

		Q_PROPERTY(gtg::TileBehavior* behavior READ behavior)
		Q_PROPERTY(QString behaviorName READ behaviorName WRITE setBehaviorName)

		Q_PROPERTY(int mapX READ mapX)
		Q_PROPERTY(int mapY READ mapY)

		Q_PROPERTY(gtg::Row* row READ row)
		Q_PROPERTY(gtg::Map* map READ map)

		private:
			TileView* m_view;
			TileBehavior* m_behavior;

			Player* m_player;
			void setPlayer(Player* player);

			QSGNode* updatePaintNode(QSGNode* node,
					QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

		public:
			Tile(QQuickItem* parent = nullptr);
			~Tile();

			//gtg::TileType* type() const;
			QString typeName() const;
			void setTypeName(const QString& typeName);

			gtg::TileView* view() const;
			QString viewName() const;
			void setViewName(const QString& viewName);

			gtg::TileBehavior* behavior() const;
			QString behaviorName() const;
			void setBehaviorName(const QString& behaviorName);

			int mapX() const;
			int mapY() const;

			gtg::Row* row() const;
			gtg::Map* map() const;

			friend class Player;

		signals:
			void viewChanged(TileView*, TileView*);
			void behaviorChanged(TileBehavior*, TileBehavior*);

			void playerEntered(Player*);
			void playerExited(Player*);
	};
}

QML_DECLARE_TYPE(gtg::Tile)

#endif
