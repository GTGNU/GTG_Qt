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

#include "ViewListEntry.h"
#include "TileView.h"

#include <QtCore/qmath.h>

gtg::ViewListEntry::ViewListEntry(QObject* parent)
	: QObject(nullptr)
	, m_view(nullptr)

	, m_region(MIDDLE)
	, m_opacity(100)
	, m_rotation(0)

	, m_viewContentChanged(true)
	, m_rotationChanged(true)
	, m_opacityChanged(true)

	, m_viewNode(nullptr)
	, m_transformNode(nullptr)
	, m_opacityNode(nullptr)
{
	qDebug() << "ViewListEntry()";
	connect(this, &ViewListEntry::opacityChanged,
			this, &ViewListEntry::changed);
	connect(this, &ViewListEntry::rotationChanged,
			this, &ViewListEntry::changed);
	connect(this, &ViewListEntry::viewContentChanged,
			this, &ViewListEntry::changed);
}

gtg::ViewListEntry::~ViewListEntry()
{
}


gtg::TileView* gtg::ViewListEntry::view() const
{
	return m_view;
}

void gtg::ViewListEntry::setView(TileView* view)
{
	if (m_view) {
		disconnect(m_view, &TileView::changed,
				this, &ViewListEntry::setViewContentChanged);
	}

	m_view = view;
	connect(m_view, &TileView::changed,
			this, &ViewListEntry::setViewContentChanged);
}


gtg::ViewListEntry::Region gtg::ViewListEntry::region() const
{
	return m_region;
}

void gtg::ViewListEntry::setRegion(ViewListEntry::Region region)
{
	m_region = region;
	setViewContentChanged();
}


unsigned char gtg::ViewListEntry::opacity() const
{
	return m_opacity;
}

void gtg::ViewListEntry::setOpacity(unsigned char opacity)
{
	if (opacity >= 0 && opacity <= 100) {
		m_opacity = opacity;
		setOpacityChanged();
	}
}


short gtg::ViewListEntry::rotation() const
{
	return m_rotation;
}

void gtg::ViewListEntry::setRotation(short rotation)
{
	m_rotation = rotation;
	setRotationChanged();
}


QSGNode* gtg::ViewListEntry::insertTransformNode(QSGNode* node)
{
	m_transformNode = new QSGTransformNode;

	if (m_opacityNode) {
		m_opacityNode->appendChildNode(m_transformNode);
		m_opacityNode->removeChildNode(m_viewNode);
	}

	m_transformNode->appendChildNode(m_viewNode);
	return m_opacityNode?
		static_cast<QSGNode*>(m_opacityNode) :
		static_cast<QSGNode*>(m_transformNode);
}

QSGNode* gtg::ViewListEntry::insertOpacityNode(QSGNode* node)
{
	m_opacityNode = new QSGOpacityNode;
	m_opacityNode->appendChildNode(node);
	return m_opacityNode;
}


QMatrix4x4 gtg::ViewListEntry::transformMatrix()
{
	qreal cos = qCos(m_rotation);
	qreal sin = qSin(m_rotation);
	return {
		cos,  sin, 0, 0,
		-sin, cos, 0, 0,
		0,    0,   0, 0,
		0,    0,   0, 0
	};
}


void gtg::ViewListEntry::setViewContentChanged()
{
	m_viewContentChanged = true;
	emit viewContentChanged();
}

void gtg::ViewListEntry::setRotationChanged()
{
	m_rotationChanged = true;
	emit rotationChanged(m_rotation);
}

void gtg::ViewListEntry::setOpacityChanged()
{
	m_opacityChanged = true;
	emit opacityChanged(m_opacity);
}


QSGNode* gtg::ViewListEntry::updateNode(QSGNode* node, Tile* tile)
{
	if (m_viewContentChanged) {
		m_viewNode = view()->updateNode(m_viewNode, tile, region());
		m_viewContentChanged = false;
	}

	if (m_rotationChanged) {
		if (!m_transformNode)
			node = insertTransformNode(node);

		m_transformNode->setMatrix(transformMatrix());
		m_rotationChanged = false;
	}

	if (m_opacityChanged) {
		if (!m_opacityNode)
			node = insertOpacityNode(node);

		m_opacityNode->setOpacity((qreal)m_opacity / 100.0);
		m_opacityChanged = false;
	}

	return node;
}
