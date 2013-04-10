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

#include "TextureCache.h"

#include <QtQuick/QQuickWindow>
#include <QtQuick/QSGTexture>


using gtg::TextureCache;


TextureCache::CacheEntry::CacheEntry(QString path, unsigned textureColumns)
	: m_textureColumns(textureColumns)
	, m_full(path)
	, m_textures()
{
}

TextureCache::CacheEntry::~CacheEntry()
{
}

unsigned TextureCache::CacheEntry::index(QPoint region) const
{
	return region.x() * m_textureColumns + region.y();
}

QImage TextureCache::CacheEntry::at(QPoint region) const
{
	uint tileSize = m_full.width() / m_textureColumns;

	return m_full.copy(
		tileSize * region.x(),
		tileSize * region.y(),
		tileSize,
		tileSize);
}

QSGTexture* TextureCache::CacheEntry::get(QQuickWindow* w, QPoint region)
{
	unsigned i = index(region);
	auto it = m_textures.find(i);

	if (it == m_textures.end())
		it = m_textures.insert(i,
			QSharedPointer<QSGTexture>(w->createTextureFromImage(at(region))));

	return it->data();
}



TextureCache::TextureCache(QString filePrefix)
	: m_filePrefix(filePrefix)
{
}

TextureCache::~TextureCache()
{
}

TextureCache::iterator TextureCache::get(QString filename, unsigned textureColumns)
{
	auto pointer = m_entries.find(filename);

	if (pointer == m_entries.end()) {
		pointer = m_entries.insert(filename,
				CacheEntry(m_filePrefix + filename, textureColumns));
	}

	return pointer;
}
