#include "TileBehavior.h"

gtg::TileBehavior::TileBehavior(QObject* parent)
	: TileDef<TileBehavior>(parent)

	, m_trespassable(false)
{
}

gtg::TileBehavior::~TileBehavior()
{
}


bool gtg::TileBehavior::isTrespassable() const
{
	return m_trespassable;
}

void gtg::TileBehavior::setTrespassable(bool trespassable)
{
	m_trespassable = trespassable;
}


void gtg::TileBehavior::emitPlayerEnteredArea(Player* player)
{
	emit playerEnteredArea(player);
}

void gtg::TileBehavior::emitPlayerExitedArea(Player* player)
{
	emit playerExitedArea(player);
}
