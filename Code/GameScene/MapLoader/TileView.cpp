#include "TileView.h"

#include "Tile.h"

#include <QtQuick/QQuickWindow>

gtg::TextureCache gtg::TileView::m_cache{"assets/"};

gtg::TileView::TileView(QObject* parent)
	: TileDef<TileView>(parent)
	, m_imageInitialized(false)
	, m_image()
{
}

gtg::TileView::~TileView()
{
}


QString gtg::TileView::textureFilename() const
{
	return m_imageInitialized? m_image.key() : "";
}

void gtg::TileView::setTextureFilename(const QString& textureFilename)
{
	m_image = m_cache.get(textureFilename);
	m_imageInitialized = true;

	emit textureChanged();
}


void gtg::TileView::updateTextureOf(QSGSimpleTextureNode* node,
		QQuickWindow* window, TileView::Area area)
{
	node->setTexture(m_image.value().get(window, area));
}

