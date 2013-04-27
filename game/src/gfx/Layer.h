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

	namespace gfx
	{
		class Texture;

		/*! \brief A layer displayed in an entity
		 *
		 * This class is the one that interfaces between a texture
		 * and an entity with a region and several transformations.
		 */
		class Layer
			: public QObject
		{
			Q_OBJECT

			Q_PROPERTY(
					gtg::gfx::Texture* texture
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
				Texture* m_texture;

				QPoint m_region;
				int m_rotation;
				unsigned m_opacity;

				//! Keep track of what actually needs to be updated
				bool m_textureChanged;
				//! Keep track of what actually needs to be updated
				bool m_rotationChanged;
				//! Keep track of what actually needs to be updated
				bool m_opacityChanged;

				//! The innermost node
				QSGNode* m_textureNode;
				//! May be the parent of the textureNode
				QSGTransformNode* m_transformNode;
				//! May be the parent of the textureNode or the transformNode if it exists
				QSGOpacityNode* m_opacityNode;

				//! Returns the parent node
				/*! textureNode is always present.
				 *
				 * If some transformation (such as rotation) is
				 * set, then the transformNode is created and the
				 * textureNode is added as a child to it.
				 *
				 * If the opacity is changed, then the opacityNode
				 * is created and the previous rootNode is added
				 * to it as a child.
				 *
				 * This way, opacityNode will always be the root if it exists,
				 * transformNode will always be the parent of textureNode,
				 * and textureNode will always be in the last level where all
				 * modifications will be reflected.
				 */
				QSGNode* rootNode() const;

				//! Initialize and insert the transformNode
				void insertTransformNode(QSGNode* parent);
				//! Initialize and insert the opacityNode
				void insertOpacityNode(QSGNode* parent);

				//! Calculate the transformation matrix for the transformNode
				QMatrix4x4 transformMatrix(int width, int height);

			protected slots:
				void setTextureChanged();
				void setRotationChanged();
				void setOpacityChanged();

			public:
				explicit Layer(QObject* parent = nullptr);
				~Layer();

				//! Get a pointer to the texture that takes care of updating textureNode
				gtg::gfx::Texture* texture() const;
				//! Set the texture.
				void setTexture(gtg::gfx::Texture* texture);

				//! Return the region of the texture that is displayed in the layer (default is 1,1 == middle)
				QPoint region() const;
				//! Set the region of the texture that should be displayed in the layer.
				void setRegion(QPoint region);

				//! Get the opacity (%)
				unsigned opacity() const;
				//! Set the opacity (%)
				void setOpacity(unsigned opacity);

				//! Get the rotation (degrees)
				int rotation() const;
				//! Set the rotation (degrees)
				void setRotation(int rotation);

				//! WARNING: Call only from some point inside a updatePaintNode() function
				/*! Update the node according to what has changed since the last call
				 */
				QSGNode* updateNode(QSGNode* parent, QQuickItem* item);

			signals:
				void changed();

				void textureChanged();
				void rotationChanged(short rotation);
				void opacityChanged(unsigned opacity);
		};
	}
}

QML_DECLARE_TYPE(gtg::gfx::Layer)

#endif
