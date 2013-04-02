#ifndef TILEVIEW_H
#define TILEVIEW_H

#include <QtCore/QHash>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QPair>
#include <QtCore/QString>

#include <QtGui/QImage>

#include <QtQuick/QQuickItem>
#include <QtQuick/QSGSimpleTextureNode>
#include <QtQuick/QSGTexture>

#include "TileDef.h"
#include "TextureCache.h"

namespace gtg
{
	class Player;
	class Tile;

	class TileView
		: public TileDef<TileView>
	{
		Q_OBJECT
		Q_PROPERTY(QString texture READ textureFilename WRITE setTextureFilename NOTIFY textureChanged)
		Q_ENUMS(Area)

		private:
			static TextureCache m_cache;

			bool m_imageInitialized;
			TextureCache::pointer m_image;

		public:
			enum Area : uint {
				TOPLEFT=0, TOP,    TOPRIGHT,
				LEFT,      MIDDLE, RIGHT,
				BOTLEFT,   BOTTOM, BOTRIGHT
			};

			TileView(QObject* parent = nullptr);
			~TileView();

			QString textureFilename() const;
			void setTextureFilename(const QString& textureFilename);

			void updateTextureOf(QSGSimpleTextureNode* node,
					QQuickWindow* window, Area area);

		signals:
			void textureChanged();
	};
}

QML_DECLARE_TYPE(gtg::TileView)

#endif
