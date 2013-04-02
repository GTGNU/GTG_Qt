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

QImage gtg::TextureCache::CacheEntry::at(uint area) const
{
	uint tileSize = m_full.width() / 3;

	return m_full.copy(
		tileSize * (area % 3),
		tileSize * (area / 3),
		tileSize,
		tileSize);
}

QSGTexture* gtg::TextureCache::CacheEntry::get(QQuickWindow* w, uint area)
{
	if (!m_textures[area])
		m_textures[area] = w->createTextureFromImage(at(area));

	return m_textures[area];
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

