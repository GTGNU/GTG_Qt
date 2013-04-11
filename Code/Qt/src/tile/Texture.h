/*
 * Copyright 2013 xcv_
 *
 * This file is part of Grand Theft Gentoo.
 *
 * Foobar is free software: you can redistribute it and/or modify
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

#ifndef TEXTURE_H
#define TEXTURE_H

#include <QtCore/QHash>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QPair>
#include <QtCore/QString>

#include <QtGui/QImage>

#include <QtQuick/QQuickItem>
#include <QtQuick/QSGSimpleTextureNode>
#include <QtQuick/QSGTexture>

#include "helpers/Registered.h"
#include "TextureCache.h"

namespace gtg
{
	class Player;
	class Tile;

	namespace tile
	{
		/*! \brief Encapsulates the drawn texture for layers
		 *
		 * This class is the one that takes care of updating
		 * texture nodes. It also allows for the use of basic
		 * texture atlases through an offset property.
		 *
		 * Each texture is three rows tall, where it contains
		 * top, middle and bottom sprites for the tile.
		 */
		class Texture
			: public Registered<Texture>
		{
			Q_OBJECT

			Q_PROPERTY(
					QString file
					READ file
					WRITE setFile)

			Q_PROPERTY(
					unsigned offset
					READ offset
					WRITE setOffset)

			private:
				//! All textures are cached in the static cache object
				static TextureCache m_cache;

				//! We need to know wether the iterator is valid or not
				bool m_initialized;

				//! See TextureCache
				TextureCache::iterator m_cacheIterator;

				//! The offset of the atlas
				unsigned m_offset;

			public:
				Texture(QObject* parent = nullptr);
				~Texture();

				//! Get the file name of the texture
				QString file() const;
				//! Load (if not in the cache) a different file)
				void setFile(const QString& filename);

				//! Get the offset of the current texture in the atlas
				unsigned offset() const;
				//! Set the offset of the current texture in the atlas
				void setOffset(unsigned offset);

				/*! \brief Update the given node
				 *
				 * This is the function that takes actual care of drawing
				 * the texture (or that interacts with the scene graph)
				 *
				 * \param node The node to be updated
				 * \param tile The tile that contains the node
				 * \param region The region (topleft, middle, bottom...) to be extracted
				 * \return The updated node
				 */
				QSGNode* updateNode(QSGNode* node, Tile* tile, QPoint region);

			signals:
				void changed();
		};
	}
}

QML_DECLARE_TYPE(gtg::tile::Texture)

#endif
