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

#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <array>

#include <QtCore/QHash>
#include <QtCore/QString>

#include <QtGui/QImage>

class QQuickWindow;
class QSGTexture;

namespace gtg
{
	class TextureCache
	{
		private:
			class CacheEntry
			{
				private:
					QImage m_full;
					std::array<QSGTexture*, 9> m_textures;
					QImage at(uint region) const;

				public:
					CacheEntry() = delete;
					CacheEntry(QString filename);
					~CacheEntry();

					QSGTexture* get(QQuickWindow* w, uint region);
			};

			QString m_filePrefix;
			QHash<QString, CacheEntry> m_entries;

		public:
			typedef decltype(m_entries)::iterator pointer;

			TextureCache(QString filePrefix);
			~TextureCache();

			QHash<QString, CacheEntry>::iterator get(QString filename);
	};
}

#endif
