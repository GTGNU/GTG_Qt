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

#include "TileView.h"

gtg::TextureCache::CacheEntry::CacheEntry(QString path)
	: m_full(path)
	, m_textures{{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}}
{
}

gtg::TextureCache::CacheEntry::~CacheEntry()
{
}

QImage gtg::TextureCache::CacheEntry::at(uint region) const
{
	uint tileSize = m_full.width() / 3;

	return m_full.copy(
		tileSize * (region % 3),
		tileSize * (region / 3),
		tileSize,
		tileSize);
}

QSGTexture* gtg::TextureCache::CacheEntry::get(QQuickWindow* w, uint region)
{
	if (!m_textures[region])
		m_textures[region] = w->createTextureFromImage(at(region));

	return m_textures[region];
}



gtg::TextureCache::TextureCache(QString filePrefix)
	: m_filePrefix(filePrefix)
{
}

gtg::TextureCache::~TextureCache()
{
}

QHash<QString, gtg::TextureCache::CacheEntry>::iterator
gtg::TextureCache::get(QString filename)
{
	auto pointer = m_entries.find(filename);

	if (pointer == m_entries.end())
		pointer = m_entries.insert(filename, CacheEntry(m_filePrefix + filename));

	return pointer;
}

