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

#ifndef FLOATINGENTITY_H
#define FLOATINGENTITY_H

#include <QtCore/QList>

#include <QtQml/QQmlListProperty>

#include <QtQuick/QQuickItem>

#include "gfx/LayerStack.h"

#include "util/Registered.h"

namespace gtg
{
	namespace map
	{
		class Map;
		class Tile;
	}

	namespace floating
	{
		class Entity
			: public QQuickItem
			, public Registered
		{
			Q_OBJECT

			Q_PROPERTY(
					gtg::gfx::LayerStack* layers
					READ layers)

			Q_PROPERTY(
					QQmlListProperty<gtg::gfx::Layer> layersQml
					READ layersQml)

			Q_PROPERTY(
					gtg::map::Map* map
					READ map
					WRITE setMap)

			Q_PROPERTY(QString type READ type)

			Q_PROPERTY(QTimer* timer READ timer)

			Q_PROPERTY(int tiledX READ tiledX)
			Q_PROPERTY(int tiledX2 READ tiledX2)

			Q_PROPERTY(int tiledY READ tiledY)
			Q_PROPERTY(int tiledY2 READ tiledY2)

			Q_PROPERTY(unsigned tiledWidth READ tiledWidth)
			Q_PROPERTY(unsigned tiledHeight READ tiledHeight)

			Q_CLASSINFO("DefaultProperty", "layerQml")

			private:
				gfx::LayerStack m_layers;

				QString m_type;
				map::Map* m_map;

				int m_timerInterval;

				//! Virtual function inherited from QQuickItem. See Qt documentation.
				/*!
				 * \param node The node to update (see the Qt Scene Graph framework)
				 * \param updatePaintNode
				 * \return The updated node
				 */
				QSGNode* updatePaintNode(QSGNode* node,
						QQuickItem::UpdatePaintNodeData* updatePaintNodeData);

			public:
				Entity(QString type, QQuickItem* parentItem = nullptr);
				virtual ~Entity();

				const gtg::gfx::LayerStack* layers() const;
				gtg::gfx::LayerStack* layers();

				//! Returns a QQmlListProperty of tiles. This is just a QML accessor.
				QQmlListProperty<gtg::gfx::Layer> layersQml();

				//! Return the global timer
				QTimer* timer() const;

				virtual QString type() const = 0;

				gtg::map::Map* map() const;
				void setMap(gtg::map::Map* map);

				int tiledX() const;
				int tiledX2() const;

				int tiledY() const;
				int tiledY2() const;

				int tiledWidth() const;
				int tiledHeight() const;

				Q_INVOKABLE bool intersects(gtg::floating::Entity* other) const;
				Q_INVOKABLE bool intersectsTile(int x, int y) const;

			signals:
				void enteredTile(gtg::map::Tile*);
				void leftTile(gtg::map::Tile*);

				void act(int delta);
		};
	}
}

QML_DECLARE_TYPE(gtg::floating::Entity)

#endif
