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
				static TextureCache m_cache;

				bool m_initialized;
				TextureCache::iterator m_cacheIterator;

				unsigned m_offset;

			public:
				Texture(QObject* parent = nullptr);
				~Texture();

				QString file() const;
				void setFile(const QString& filename);

				unsigned offset() const;
				void setOffset(unsigned offset);

				QSGNode* updateNode(QSGNode* node, Tile* tile, QPoint region);

			signals:
				void changed();
		};
	}
}

QML_DECLARE_TYPE(gtg::tile::Texture)

#endif
