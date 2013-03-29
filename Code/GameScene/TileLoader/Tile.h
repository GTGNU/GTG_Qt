#ifndef TILE_H
#define TILE_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtQuick/QQuickItem>
#include <QtQuick/QSGSimpleTextureNode>
#include <QtQuick/QSGTexture>

namespace gtg
{
	class Player;

	class Tile
		: public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(QString type READ type WRITE setType)
		Q_PROPERTY(QString behavior READ behavior WRITE setBehavior)

		Q_PROPERTY(int mapX READ mapX)
		Q_PROPERTY(int mapY READ mapY)

		Q_PROPERTY(bool trespassable READ isTrespassable WRITE setTrespassable)
		Q_PROPERTY(QString texture READ textureFilename WRITE setTextureFilename)


		private:
			QString m_type;

			int m_mapX;
			int m_mapY;

			bool m_trespassable;
			QString m_textureFilename;

			QSGNode* updatePaintNode(QSGNode* node,
					QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

			Player* m_player;
			void setPlayer(Player* player);

		public:
			Tile(QQuickItem* parent = nullptr);
			~Tile();

			static const QString texturePath;

			QString type() const;
			void setType(const QString& type);

			QString behavior() const { return "lel"; }
			void setBehavior(const QString&) {}

			bool isTrespassable() const;
			void setTrespassable(bool trespassable);

			QString textureFilename() const;
			void setTextureFilename(const QString& textureFilename);

			int mapX() const;
			int mapY() const;

			friend class Player;

		signals:
			void playerEntered(Player*);
			void playerExited(Player*);
	};
}

QML_DECLARE_TYPE(gtg::Tile)

#endif
