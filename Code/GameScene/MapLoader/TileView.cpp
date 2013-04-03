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

