#ifndef TILE_H
#define TILE_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtQuick/QQuickItem>
#include <QtQuick/QSGTexture>

namespace gtg
{
	class Player;

	class Tile
		: public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(QString type READ type WRITE setType)
		Q_PROPERTY(bool trespassable READ isTrespassable WRITE setTrespassable)
		Q_PROPERTY(QString texture READ textureFilename WRITE setTextureFilename)

		private:
			QString m_type;
			bool m_trespassable;
			QString m_textureFilename;
			Player* m_player;

			QSGTexture* m_texture;
			void loadTexture();
			void setPlayer(Player* player);

		public:
			Tile(QQuickItem* parent = nullptr);
			~Tile();

			static const QString texturePath;

			QString type() const;
			void setType(const QString& type);

			bool isTrespassable() const;
			void setTrespassable(bool trespassable);

			QString textureFilename() const;
			void setTextureFilename(const QString& textureFilename);

			friend class Player;

		signals:
			void playerEntered(Player*);
			void playerExited(Player*);
	};

}

QML_DECLARE_TYPE(gtg::Tile)

#endif
