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

#include "Texture.h"

#include <QtQuick/QQuickWindow>

#include "Tile.h"


using gtg::tile::Texture;

using gtg::TextureCache;


TextureCache Texture::m_cache("assets/");

Texture::Texture(QObject* parent)
	: Registered<Texture>(parent)
	, m_initialized(false)
	, m_cacheIterator()
	, m_columns(DEFAULT_COLUMNS)
{
	connect(this, &Texture::textureChanged,
			this, &Texture::changed,
			Qt::DirectConnection);
}

Texture::~Texture()
{
}


QString Texture::file() const
{
	return m_initialized? m_cacheIterator.key() : "";
}

void Texture::setFile(const QString& filename)
{
	m_cacheIterator = m_cache.get(filename, m_columns);
	m_initialized = true;

	emit textureChanged();
}


unsigned Texture::columns() const
{
	return m_columns;
}

void Texture::setColumns(unsigned int columns)
{
	m_columns = columns;
}


QSGNode* Texture::updateNode(QSGNode* node, Tile* tile, QPoint region)
{
	QSGSimpleTextureNode* n;

	if (!node) {
		n = new QSGSimpleTextureNode;
		n->setRect(tile->boundingRect());
	} else {
		n = static_cast<QSGSimpleTextureNode*>(node);
	}

	n->setTexture( m_cacheIterator.value().get(tile->window(), region) );
	return n;
}

