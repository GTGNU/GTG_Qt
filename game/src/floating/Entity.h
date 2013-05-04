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
#include "util/TiledRect.h"

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

			Q_PROPERTY(
					QList<QObject*> containerTiles
					READ containerTiles)

			Q_PROPERTY(QString type READ type)

			Q_PROPERTY(QTimer* timer READ timer)

			Q_CLASSINFO("DefaultProperty", "layersQml")

			private:
				gfx::LayerStack m_layers;

				QString m_type;
				map::Map* m_map;

				TiledRect m_tiledRect;
				QList<QObject*> m_containerTiles;

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

				QString type() const;

				gtg::map::Map* map() const;
				void setMap(gtg::map::Map* map);

				TiledRect tiledRect() const;

				QList<QObject*> containerTiles() const;

				Q_INVOKABLE bool intersects(const QQuickItem* other) const;

			signals:
				void enteredTile(gtg::map::Tile*);
				void leftTile(gtg::map::Tile*);

				void act(int delta);

			protected slots:
				void updateContainerTiles();
		};
	}
}

QML_DECLARE_TYPE(gtg::floating::Entity)

#endif
