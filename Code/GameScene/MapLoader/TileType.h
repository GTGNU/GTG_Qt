#ifndef TILETYPE_H
#define TILETYPE_H

#include <QtCore/QObject>

#include <QtQml>

#include "TileDef.h"
#include "NamedObject.h"

namespace gtg
{
	class TileView;
	class TileBehavior;

	class TileType
		: public TileDef<TileType>
	{
		Q_OBJECT
		Q_PROPERTY(gtg::TileView* view READ view WRITE setView)
		Q_PROPERTY(gtg::TileBehavior* behavior READ behavior WRITE setBehavior)

		private:
			TileView* m_view;
			TileBehavior* m_behavior;

		public:
			TileType(QObject* parent = nullptr);
			~TileType();

			gtg::TileView* view() const;
			void setView(gtg::TileView* view);

			gtg::TileBehavior* behavior() const;
			void setBehavior(gtg::TileBehavior* behavior);
	};
}

QML_DECLARE_TYPE(gtg::TileType)

#endif
