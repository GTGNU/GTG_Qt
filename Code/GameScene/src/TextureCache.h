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

#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <QtCore/QHash>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QVector>

#include <QtGui/QImage>

class QQuickWindow;
class QSGTexture;

namespace gtg
{
	/*! \brief Caches textures and regions of them
	 *
	 * Load and caches textures based on their file name and for each file,
	 * region copies are turned into cached QSGTextures.
	 */
	class TextureCache
	{
		private:
			/*! \brief Encapsulates the cache entry for a file
			 *
			 * Contains cached QSGTexture for regions of a given file.
			 */
			class CacheEntry
			{
				private:
					QImage m_full;
					QMap<unsigned, QSharedPointer<QSGTexture>> m_textures;

					QImage at(QPoint region) const;

				public:
					CacheEntry() = delete;
					CacheEntry(QString path);
					~CacheEntry();

					/*! \brief Makes a cached QSGTexture out of a full image and a given region
					 *
					 * \param w The QQuickWindow that contains the scene. It's needed to generate the texture
					 * \param region (x,y) point that represents where the region starts.
					 * \return A QSGTexture of that region of the image
					 */
					QSGTexture* get(QQuickWindow* w, QPoint region);
			};

			QString m_filePrefix;
			QHash<QString, CacheEntry> m_entries;

		public:
			//! This typedef a convenient way to keep track of your texture
			typedef decltype(m_entries)::iterator iterator;

			TextureCache(QString filePrefix);
			~TextureCache();

			//! Returns an iterator to the requested cache entry. If the file is not in the map, it's loaded.
			QHash<QString, CacheEntry>::iterator get(QString filename);
	};
}

#endif
