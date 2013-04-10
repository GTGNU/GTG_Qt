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

#ifndef TILELAYER_H
#define TILELAYER_H

#include <QtCore/QObject>
#include <QtQuick/QQuickItem>

class QQuickWindow;
class QSGOpacityNode;
class QSGTransformNode;
class QSGNode;

namespace gtg
{
	class Tile;

	namespace tile
	{
		class Texture;

		class Layer
			: public QObject
		{
			Q_OBJECT

			Q_PROPERTY(
					gtg::tile::Texture* texture
					READ texture
					WRITE setTexture)

			Q_PROPERTY(
					QPoint region
					READ region
					WRITE setRegion)

			Q_PROPERTY(
					unsigned opacity
					READ opacity
					WRITE setOpacity
					NOTIFY opacityChanged)

			Q_PROPERTY(
					int rotation
					READ rotation
					WRITE setRotation
					NOTIFY rotationChanged)

			private:
				tile::Texture* m_texture;

				QPoint m_region;
				int m_rotation;
				unsigned m_opacity;

				bool m_textureChanged;
				bool m_rotationChanged;
				bool m_opacityChanged;

				// opacityNode owns transformNode owns textureNode
				// opacityNode and transformNode may be null, so
				// the next non-null is the root of the subgraph
				QSGNode* m_textureNode;
				QSGTransformNode* m_transformNode;
				QSGOpacityNode* m_opacityNode;

				QSGNode* rootNode() const;

				void insertTransformNode(QSGNode* parent);
				void insertOpacityNode(QSGNode* parent);

				QMatrix4x4 transformMatrix(short tileSize);

			protected slots:
				void setTextureChanged();
				void setRotationChanged();
				void setOpacityChanged();

			public:
				Layer(QObject* parent = nullptr);
				~Layer();

				gtg::tile::Texture* texture() const;
				void setTexture(gtg::tile::Texture* texture);

				QPoint region() const;
				void setRegion(QPoint region);

				unsigned opacity() const;
				void setOpacity(unsigned opacity);

				int rotation() const;
				void setRotation(int rotation);

				QSGNode* updateNode(QSGNode* parent, Tile* tile);

			signals:
				void changed();

				void textureChanged();
				void rotationChanged(short rotation);
				void opacityChanged(unsigned opacity);
		};
	}
}

QML_DECLARE_TYPE(gtg::tile::Layer)

#endif
