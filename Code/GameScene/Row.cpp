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

#include "Row.h"
#include "Map.h"
#include "Tile.h"

#include <QtQuick/QQuickWindow>

#include <QtQuick/QSGSimpleRectNode>

QDebug& operator<<(QDebug& dbg, gtg::Row* row)
{
	return dbg
		<< "Row { parentItem:"
			<< QString(row->parentItem()->metaObject()->className())
			+ "(" + QString::number((uintptr_t)row->parentItem(), 16) + ")"

		<< ", tiles:" << row->tiles().size()

		<< ", window:"
			<< QString(row->window()->metaObject()->className())
			+ "(" + QString::number((uintptr_t)row->window(), 16) + ")"

		<< "}";
}


gtg::Row::Row(QQuickItem* parent)
	: QQuickItem(parent)
	, m_tiles(this)
{
	setFlag(QQuickItem::ItemHasContents);
}

gtg::Row::~Row()
{
}


int gtg::Row::x() const
{
	return 0;
}

int gtg::Row::y() const
{
	return mapY() * map()->tileSize();
}

int gtg::Row::width() const
{
	return m_tiles.size() * map()->tileSize();
}

int gtg::Row::height() const
{
	return m_tiles.size() ? m_tiles.at(0)->height() : 0;
}

QRectF gtg::Row::boundingRect() const
{
	return QRect(x(), y(), width(), height());
}


int gtg::Row::mapY() const
{
	return map()->indexOf(this);
}

gtg::Map* gtg::Row::map() const
{
	return qobject_cast<Map*>(parentItem());
}


gtg::ChildList<gtg::Tile> gtg::Row::tiles() const
{
	return m_tiles;
}

QQmlListProperty<gtg::Tile> gtg::Row::qmlTiles()
{
	return m_tiles.toQmlListProperty();
}


int gtg::Row::indexOf(const Tile* object) const
{
	int i = 0;

	for (QQuickItem* tile : m_tiles) {
		if (tile == object)
			return i;
		else
			i++;
	}

	return -1;
}


QSGNode* gtg::Row::updatePaintNode(QSGNode* node,
		QQuickItem::UpdatePaintNodeData* updatePaintNodeData)
{
	qDebug() << "----------------------------------------";
	qDebug() << "Drawing " << this;
	qDebug() << "Children:";

	for (auto child : childItems()) {
		child->update();
		qDebug() << child;
	}

	QSGSimpleRectNode* n = static_cast<QSGSimpleRectNode*>(node);

	if (!n) {
		n = new QSGSimpleRectNode;

		int tileSize = map()->tileSize();
		setX(0);
		setY(mapY() * tileSize);
		setWidth(m_tiles.size() * tileSize);
		setHeight(tileSize);
	}

	qDebug() << "mapY:" << mapY();

	n->setRect(boundingRect());

	return n;
}
