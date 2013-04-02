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
					QImage at(uint area) const;

				public:
					CacheEntry() = delete;
					CacheEntry(QString filename);
					~CacheEntry();

					QSGTexture* get(QQuickWindow* w, uint area);
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
