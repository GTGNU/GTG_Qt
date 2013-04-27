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

#include "Layer.h"

#include <QtCore/qmath.h>

#include "Texture.h"


using gtg::gfx::Layer;
using gtg::gfx::Texture;


Layer::Layer(QObject* parent)
	: QObject(nullptr)
	, m_texture(nullptr)

	, m_region(1,1)
	, m_rotation(0)
	, m_opacity(100)

	, m_textureChanged(true)
	, m_rotationChanged(false)
	, m_opacityChanged(false)

	, m_textureNode(nullptr)
	, m_transformNode(nullptr)
	, m_opacityNode(nullptr)
{
	connect(this, &Layer::opacityChanged,
			this, &Layer::changed,
			Qt::DirectConnection);
	connect(this, &Layer::rotationChanged,
			this, &Layer::changed,
			Qt::DirectConnection);
	connect(this, &Layer::textureChanged,
			this, &Layer::changed,
			Qt::DirectConnection);
}

Layer::~Layer()
{
}


Texture* Layer::texture() const
{
	return m_texture;
}

void Layer::setTexture(Texture* texture)
{
	if (m_texture) {
		disconnect(m_texture, &Texture::changed,
				this, &Layer::setTextureChanged);
	}

	m_texture = texture;

	connect(m_texture, &Texture::changed,
			this, &Layer::setTextureChanged,
			Qt::DirectConnection);
}


QPoint Layer::region() const
{
	return m_region;
}

void Layer::setRegion(QPoint region)
{
	m_region = region;
	setTextureChanged();
}


unsigned Layer::opacity() const
{
	return m_opacity;
}

void Layer::setOpacity(unsigned opacity)
{
	if (opacity <= 100) {
		m_opacity = opacity;
		setOpacityChanged();
	}
}


int Layer::rotation() const
{
	return m_rotation;
}

void Layer::setRotation(int rotation)
{
	m_rotation = rotation % 360;
	setRotationChanged();
}


QSGNode* Layer::rootNode() const
{
	return m_opacityNode? m_opacityNode
		: m_transformNode? m_transformNode
		: m_textureNode;
}


void Layer::insertTransformNode(QSGNode* parent)
{
	m_transformNode = new QSGTransformNode;

	if (m_opacityNode) {
		m_opacityNode->removeChildNode(m_textureNode);
		m_opacityNode->appendChildNode(m_transformNode);

	} else {
		// This hackery needs to be made for proper
		// reparenting of nodes
		QSGNode* next = m_textureNode->nextSibling();
		parent->removeChildNode(m_textureNode);

		if (!next)
			parent->appendChildNode(m_transformNode);
		else
			parent->insertChildNodeBefore(m_transformNode, next);
	}

	m_transformNode->appendChildNode(m_textureNode);
}

void Layer::insertOpacityNode(QSGNode* parent)
{
	QSGNode* prevRoot = rootNode();
	m_opacityNode = new QSGOpacityNode;

	// This hackery needs to be made for proper
	// reparenting of nodes
	QSGNode* parentNext = prevRoot->nextSibling();
	parent->removeChildNode(prevRoot);

	m_opacityNode->appendChildNode(prevRoot);

	if (!parentNext)
		parent->appendChildNode(m_opacityNode);
	else
		parent->insertChildNodeBefore(m_opacityNode, parentNext);
}


QMatrix4x4 Layer::transformMatrix(int width, int height)
{
	// We need to move the origin of the transformation to the center of the item
	return QTransform()
		.translate(width/2, height/2)
		.rotate(m_rotation)
		.translate(-width/2, -height/2);
}


void Layer::setTextureChanged()
{
	m_textureChanged = true;
	emit textureChanged();
}

void Layer::setRotationChanged()
{
	m_rotationChanged = true;
	emit rotationChanged(m_rotation);
}

void Layer::setOpacityChanged()
{
	m_opacityChanged = true;
	emit opacityChanged(m_opacity);
}


QSGNode* Layer::updateNode(QSGNode* parent, QQuickItem* item)
{
	if (m_textureChanged) {
		m_textureNode = texture()->updateNode(m_textureNode, item, region());
		m_textureChanged = false;
	}

	if (m_rotationChanged) {
		if (!m_transformNode)
			insertTransformNode(parent);

		m_transformNode->setMatrix(transformMatrix(item->width(), item->height()));
		m_rotationChanged = false;
	}

	if (m_opacityChanged) {
		if (!m_opacityNode)
			insertOpacityNode(parent);

		m_opacityNode->setOpacity((qreal)m_opacity / 100.0);
		m_opacityChanged = false;
	}

	return rootNode();
}

