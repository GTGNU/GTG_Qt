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

#include "TileView.h"
#include "Tile.h"

#include <QtQuick/QQuickWindow>

gtg::TextureCache gtg::TileView::m_cache{"assets/"};

gtg::TileView::TileView(QObject* parent)
	: TileDef<TileView>(parent)
	, m_imageInitialized(false)
	, m_image()
{
	connect(this, &TileView::textureChanged,
			this, &TileView::changed,
			Qt::DirectConnection);
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


QSGNode* gtg::TileView::updateNode(QSGNode* node, Tile* tile,
		ViewListEntry::Region region)
{
	QSGSimpleTextureNode* n;

	if (!node) {
		n = new QSGSimpleTextureNode;
		n->setRect(tile->boundingRect());
	} else {
		n = static_cast<QSGSimpleTextureNode*>(node);
	}

	n->setTexture(m_image.value().get(tile->window(), region));
	return n;
}

