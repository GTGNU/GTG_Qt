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

#ifndef VIEWLISTENTRY_H
#define VIEWLISTENTRY_H

#include <QtCore/QObject>
#include <QtQuick/QQuickItem>

class QQuickWindow;
class QSGOpacityNode;
class QSGTransformNode;
class QSGNode;

namespace gtg
{
	class Tile;
	class TileView;

	class ViewListEntry
		: public QObject
	{
		Q_OBJECT
		Q_PROPERTY(gtg::TileView* view READ view WRITE setView)
		Q_PROPERTY(Region region READ region WRITE setRegion)

		Q_PROPERTY(unsigned char opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
		Q_PROPERTY(short rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
		Q_ENUMS(Region)

		public:
			enum Region : uint {
				TOPLEFT=0, TOP,    TOPRIGHT,
				LEFT,      MIDDLE, RIGHT,
				BOTLEFT,   BOTTOM, BOTRIGHT
			};

		private:
			TileView* m_view;

			Region m_region;
			unsigned char m_opacity;
			short m_rotation;

			bool m_viewContentChanged;
			bool m_rotationChanged;
			bool m_opacityChanged;

			// opacityNode owns transformNode owns viewNode
			// opacityNode and transformNode may be null, so
			// the next non-null is the root of the subgraph
			QSGNode* m_viewNode;
			QSGTransformNode* m_transformNode;
			QSGOpacityNode* m_opacityNode;

			QSGNode* insertTransformNode(QSGNode* node);
			QSGNode* insertOpacityNode(QSGNode* node);

			QMatrix4x4 transformMatrix();

		protected slots:
			void setViewContentChanged();
			void setRotationChanged();
			void setOpacityChanged();

		public:
			ViewListEntry(QObject* parent = nullptr);
			~ViewListEntry();

			gtg::TileView* view() const;
			void setView(gtg::TileView* view);

			gtg::ViewListEntry::Region region() const;
			void setRegion(gtg::ViewListEntry::Region region);

			unsigned char opacity() const;
			void setOpacity(unsigned char opacity);

			short rotation() const;
			void setRotation(short rotation);

			QSGNode* updateNode(QSGNode* node, Tile* tile);

		signals:
			void changed();

			void viewContentChanged();
			void rotationChanged(short rotation);
			void opacityChanged(unsigned char opacity);
	};
}

QML_DECLARE_TYPE(gtg::ViewListEntry)

#endif
