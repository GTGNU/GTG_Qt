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


using gtg::gfx::TextureCache;


TextureCache::CacheEntry::CacheEntry(QString path)
	: m_full(path)
	, m_textures()
{
}

TextureCache::CacheEntry::~CacheEntry()
{
}

QImage TextureCache::CacheEntry::at(QPoint region) const
{
	// The file is always three rows tall (top/middle/bottom)
	unsigned spriteSize = m_full.height() / 3;

	return m_full.copy(
		spriteSize * region.x(),
		spriteSize * region.y(),
		spriteSize,
		spriteSize);
}

QSGTexture* TextureCache::CacheEntry::get(QQuickWindow* w, QPoint region)
{
	unsigned i = region.x() * 3 + region.y();
	auto it = m_textures.find(i);

	if (it == m_textures.end()) {
		it = m_textures.insert(i,
			QSharedPointer<QSGTexture>(w->createTextureFromImage(at(region))));
	}

	return it->data();
}



TextureCache::TextureCache(QString filePrefix)
	: m_filePrefix(filePrefix)
{
}

TextureCache::~TextureCache()
{
}

TextureCache::iterator TextureCache::get(QString filename)
{
	auto iter = m_entries.find(filename);

	if (iter == m_entries.end()) {
		iter = m_entries.insert(filename, CacheEntry(m_filePrefix + filename));
	}

	return iter;
}
