#ifndef VIEWLISTENTRY_H
#define VIEWLISTENTRY_H

#include <QtCore/QObject>

#include "TileView.h"

namespace gtg
{
	class ViewListEntry
		: public QObject
	{
		Q_OBJECT
		Q_PROPERTY(gtg::TileView* view READ view WRITE setView)
		Q_PROPERTY(gtg::TileView::Area area READ area WRITE setArea)

		private:
			TileView* m_view;
			TileView::Area m_area;

		public:
			ViewListEntry(QObject* parent = nullptr);
			~ViewListEntry();

			gtg::TileView* view() const;
			void setView(gtg::TileView* view);

			gtg::TileView::Area area() const;
			void setArea(gtg::TileView::Area area);

		signals:
			void textureChanged();
	};
}

QML_DECLARE_TYPE(gtg::ViewListEntry)

#endif
