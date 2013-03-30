#ifndef TILEVIEW_H
#define TILEVIEW_H

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtGui/QImage>

#include <QtQuick/QQuickItem>
#include <QtQuick/QSGSimpleTextureNode>
#include <QtQuick/QSGTexture>

#include "NamedObject.h"
#include "TileDef.h"

namespace gtg
{
	class Player;

	class TileView
		: public TileDef<TileView>
	{
		Q_OBJECT
		Q_PROPERTY(QString texture READ textureFilename WRITE setTextureFilename NOTIFY textureChanged)

		Q_PROPERTY(QQuickItem* misc READ misc WRITE setMisc NOTIFY miscChanged) // allow using stuff like Timers

		private:
			QString m_textureFilename;

			QImage m_textureImage;

			QSGTexture* m_texture;
			bool m_textureUpdated;

			void updateTexture(QQuickWindow* window);
			void update(QQuickWindow* window);

			QQuickItem* m_misc;

			static QSet<TileView*> m_toUpdate;

		public:
			static const QString texturePath;

			static void forceUpdate();

			TileView(QObject* parent = nullptr);
			~TileView();

			QImage textureImage() const;
			QString textureFilename() const;
			void setTextureFilename(const QString& textureFilename);

			QQuickItem* misc() const;
			void setMisc(QQuickItem* item);

			void updateTextureOf(QQuickItem* target, QSGSimpleTextureNode* n);

		signals:
			void textureChanged(QString);
			void miscChanged(QQuickItem*);
	};
}

QML_DECLARE_TYPE(gtg::TileView)

#endif
