#ifndef TILEBEHAVIOR_H
#define TILEBEHAVIOR_H

#include <QtCore/QObject>

#include <QtQml>

#include "TileDef.h"
#include "NamedObject.h"

namespace gtg
{
	class Player;

	class TileBehavior
		: public TileDef<TileBehavior>
	{
		Q_OBJECT
		Q_PROPERTY(bool trespassable READ isTrespassable WRITE setTrespassable)

		private:
			bool m_trespassable;

			void emitPlayerEnteredArea(Player* player);
			void emitPlayerExitedArea(Player* player);

		public:
			TileBehavior(QObject* parent = nullptr);
			~TileBehavior();

			bool isTrespassable() const;
			void setTrespassable(bool trespassable);

		signals:
			void playerEnteredArea(Player*);
			void playerExitedArea(Player*);

		friend class Player;
	};
}

QML_DECLARE_TYPE(gtg::TileBehavior)

#endif
